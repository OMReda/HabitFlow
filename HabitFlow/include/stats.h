#ifndef STATS_H
#define STATS_H

#include "habit.h"

// Function prototypes
void check_in(int habit_id);
void update_streaks(int habit_id);
void show_stats(int habit_id);
void print_progress_bar(int completed, int total);
void export_csv(const char *filename);
void show_dashboard();

#endif
