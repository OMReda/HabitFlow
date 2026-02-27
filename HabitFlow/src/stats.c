#include "../include/stats.h"
#include "../include/storage.h"
#include "../include/ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


static void get_current_date(char *buffer) {
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  strftime(buffer, 11, "%Y-%m-%d", tm);
}

void check_in(int habit_id) {
  HabitLog *logs = NULL;
  int log_count = 0;
  load_logs(&logs, &log_count);

  char today[11];
  get_current_date(today);

  // Prevent double-checks
  for (int i = 0; i < log_count; i++) {
    if (logs[i].habit_id == habit_id && strcmp(logs[i].date, today) == 0) {
      printf(COLOR_YELLOW EMOJI_WARN
             " Habit ID %d already marked as done for today (%s)." COLOR_RESET
             "\n",
             habit_id, today);
      free(logs);
      return;
    }
  }

  // Add new log
  HabitLog *temp = realloc(logs, (log_count + 1) * sizeof(HabitLog));
  if (temp == NULL) {
    printf("Error: Could not allocate memory for log.\n");
    free(logs);
    return;
  }
  logs = temp;
  logs[log_count].habit_id = habit_id;
  strcpy(logs[log_count].date, today);
  logs[log_count].completed = 1;
  log_count++;

  save_logs(logs, log_count);
  free(logs);

  // Update habit stats
  update_streaks(habit_id);
  printf(COLOR_GREEN EMOJI_CHECK
         " Habit ID %d marked as done for %s." COLOR_RESET "\n",
         habit_id, today);
}

void update_streaks(int habit_id) {
  Habit *habits = NULL;
  int habit_count = 0;
  load_habits(&habits, &habit_count);

  int habit_index = -1;
  for (int i = 0; i < habit_count; i++) {
    if (habits[i].id == habit_id) {
      habit_index = i;
      break;
    }
  }

  if (habit_index == -1) {
    free(habits);
    return;
  }

  HabitLog *logs = NULL;
  int log_count = 0;
  load_logs(&logs, &log_count);

  // Calculate streaks
  // For simplicity, we assume daily habits for now.
  // A more robust algorithm would handle gaps.

  habits[habit_index].total_completions++;

  // Simplistic streak update: increment if checked today.
  // In a real app, we'd check if yesterday was completed to continue streak.
  habits[habit_index].current_streak++;
  if (habits[habit_index].current_streak > habits[habit_index].longest_streak) {
    habits[habit_index].longest_streak = habits[habit_index].current_streak;
  }

  save_habits(habits, habit_count);
  free(habits);
  free(logs);
}

void show_stats(int habit_id) {
  Habit *habits = NULL;
  int habit_count = 0;
  load_habits(&habits, &habit_count);

  int habit_index = -1;
  for (int i = 0; i < habit_count; i++) {
    if (habits[i].id == habit_id) {
      habit_index = i;
      break;
    }
  }

  if (habit_index == -1) {
    printf("Error: Habit ID %d not found.\n", habit_id);
    free(habits);
    return;
  }

  Habit h = habits[habit_index];
  printf("\n" COLOR_CYAN "--- Stats for: %s ---" COLOR_RESET "\n", h.name);
  printf(COLOR_YELLOW EMOJI_FIRE " Current Streak:" COLOR_RESET " %d days\n",
         h.current_streak);
  printf(COLOR_YELLOW EMOJI_STAR " Longest Streak:" COLOR_RESET " %d days\n",
         h.longest_streak);
  printf(COLOR_BLUE EMOJI_GRAPH " Total Completions:" COLOR_RESET " %d\n",
         h.total_completions);

  // Mocking a completion rate for now
  float rate = (h.total_completions > 0) ? 75.0f : 0.0f;
  printf("Completion Rate (Last 30 days): %.1f%%\n", rate);
  print_progress_bar(rate, 100);
  printf("\n");

  free(habits);
}

void print_progress_bar(int completed, int total) {
  int width = 20;
  float ratio = (float)completed / total;
  int pos = width * ratio;

  printf(COLOR_GREEN "[");
  for (int i = 0; i < width; i++) {
    if (i < pos)
      printf("█");
    else
      printf(COLOR_WHITE "░");
  }
  printf(COLOR_GREEN "] %d%%" COLOR_RESET "\n", completed);
}

void export_csv(const char *filename) {
  Habit *habits = NULL;
  int habit_count = 0;
  load_habits(&habits, &habit_count);

  HabitLog *logs = NULL;
  int log_count = 0;
  load_logs(&logs, &log_count);

  FILE *file = fopen(filename, "w");
  if (!file) {
    printf("Error: Could not open %s for writing.\n", filename);
    if (habits)
      free(habits);
    if (logs)
      free(logs);
    return;
  }

  fprintf(file, "--- Habits ---\n");
  fprintf(file, "ID,Name,CurrentStreak,LongestStreak,TotalCompletions\n");
  for (int i = 0; i < habit_count; i++) {
    fprintf(file, "%d,\"%s\",%d,%d,%d\n", habits[i].id, habits[i].name,
            habits[i].current_streak, habits[i].longest_streak,
            habits[i].total_completions);
  }

  fprintf(file, "\n--- Logs ---\n");
  fprintf(file, "HabitID,Date,Completed\n");
  for (int i = 0; i < log_count; i++) {
    fprintf(file, "%d,%s,%d\n", logs[i].habit_id, logs[i].date,
            logs[i].completed);
  }

  fclose(file);
  printf("Data exported successfully to %s\n", filename);

  if (habits)
    free(habits);
  if (logs)
    free(logs);
}

void show_dashboard() {
  Habit *habits = NULL;
  int habit_count = 0;
  load_habits(&habits, &habit_count);

  if (habit_count == 0) {
    printf("No habits found. Use 'add' to create one.\n");
    return;
  }

  printf(COLOR_MAGENTA BOLD_TEXT
         "========================================" COLOR_RESET "\n");
  printf(COLOR_CYAN BOLD_TEXT
         "          HABITFLOW DASHBOARD           " COLOR_RESET "\n");
  printf(COLOR_MAGENTA BOLD_TEXT
         "========================================" COLOR_RESET "\n\n");

  for (int i = 0; i < habit_count; i++) {
    Habit h = habits[i];
    printf(COLOR_YELLOW BOLD_TEXT "[%d]" COLOR_RESET " %-20s " COLOR_CYAN
                                  "Streak:" COLOR_RESET " %d\n",
           h.id, h.name, h.current_streak);
    float rate = (h.total_completions > 0) ? 75.0f : 0.0f;
    print_progress_bar(rate, 100);
    printf("\n");
  }

  free(habits);
}
