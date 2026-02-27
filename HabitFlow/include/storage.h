#ifndef STORAGE_H
#define STORAGE_H

#include "habit.h"

// Constants
#define HABITS_FILE "data/habits.dat"
#define LOGS_FILE "data/logs.dat"

// Function prototypes
int load_habits(Habit **habits, int *count);
int save_habits(Habit *habits, int count);
int load_logs(HabitLog **logs, int *count);
int save_logs(HabitLog *logs, int count);

#endif
