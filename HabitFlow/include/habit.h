#ifndef HABIT_H
#define HABIT_H

#define MAX_HABIT_NAME 100

typedef struct {
    int id;
    char name[MAX_HABIT_NAME];
    int current_streak;
    int longest_streak;
    int total_completions;
} Habit;

typedef struct {
    int habit_id;
    char date[11]; // YYYY-MM-DD
    int completed; // 1 = done, 0 = not done
} HabitLog;

// Function prototypes
void add_habit(const char *name);
void list_habits();
void delete_habit(int id);
void edit_habit(int id, const char *new_name);

#endif
