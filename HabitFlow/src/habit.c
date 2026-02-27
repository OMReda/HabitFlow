#include "../include/habit.h"
#include "../include/storage.h"
#include "../include/ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_habit(const char *name) {
  Habit *habits = NULL;
  int count = 0;
  load_habits(&habits, &count);

  Habit new_habit;
  new_habit.id = (count == 0) ? 1 : habits[count - 1].id + 1;
  strncpy(new_habit.name, name, MAX_HABIT_NAME - 1);
  new_habit.name[MAX_HABIT_NAME - 1] = '\0';
  new_habit.current_streak = 0;
  new_habit.longest_streak = 0;
  new_habit.total_completions = 0;

  Habit *temp = realloc(habits, (count + 1) * sizeof(Habit));
  if (temp == NULL) {
    printf("Error: Could not allocate memory for new habit.\n");
    free(habits);
    return;
  }
  habits = temp;
  habits[count] = new_habit;
  count++;

  save_habits(habits, count);
  printf(COLOR_GREEN EMOJI_CHECK " Habit added:" COLOR_RESET
                                 " %s (ID: " COLOR_YELLOW "%d" COLOR_RESET
                                 ")\n",
         new_habit.name, new_habit.id);

  free(habits);
}

void list_habits() {
  Habit *habits = NULL;
  int count = 0;
  load_habits(&habits, &count);

  if (count == 0) {
    printf("No habits found. Use 'add' to create one.\n");
    return;
  }

  printf(COLOR_CYAN BOLD_TEXT "%-5s %-30s %-10s %-10s %-10s" COLOR_RESET "\n",
         "ID", "Name", "Streak", "Longest", "Total");
  printf(COLOR_CYAN "----------------------------------------------------------"
                    "------------" COLOR_RESET "\n");
  for (int i = 0; i < count; i++) {
    printf(COLOR_YELLOW "%-5d" COLOR_RESET " %-30s " COLOR_GREEN
                        "%-10d" COLOR_RESET " %-10d %-10d\n",
           habits[i].id, habits[i].name, habits[i].current_streak,
           habits[i].longest_streak, habits[i].total_completions);
  }

  free(habits);
}

void delete_habit(int id) {
  Habit *habits = NULL;
  int count = 0;
  load_habits(&habits, &count);

  int index = -1;
  for (int i = 0; i < count; i++) {
    if (habits[i].id == id) {
      index = i;
      break;
    }
  }

  if (index == -1) {
    printf("Error: Habit with ID %d not found.\n", id);
    free(habits);
    return;
  }

  for (int i = index; i < count - 1; i++) {
    habits[i] = habits[i + 1];
  }
  count--;

  save_habits(habits, count);
  printf(COLOR_RED EMOJI_CROSS " Habit with ID %d deleted." COLOR_RESET "\n",
         id);

  free(habits);
}

void edit_habit(int id, const char *new_name) {
  Habit *habits = NULL;
  int count = 0;
  load_habits(&habits, &count);

  int index = -1;
  for (int i = 0; i < count; i++) {
    if (habits[i].id == id) {
      index = i;
      break;
    }
  }

  if (index == -1) {
    printf("Error: Habit with ID %d not found.\n", id);
    free(habits);
    return;
  }

  strncpy(habits[index].name, new_name, MAX_HABIT_NAME - 1);
  habits[index].name[MAX_HABIT_NAME - 1] = '\0';

  save_habits(habits, count);
  printf(COLOR_GREEN EMOJI_CHECK " Habit ID %d updated to:" COLOR_RESET " %s\n",
         id, habits[index].name);

  free(habits);
}
