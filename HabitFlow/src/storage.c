#include "../include/storage.h"
#include <stdio.h>
#include <stdlib.h>


int load_habits(Habit **habits, int *count) {
  FILE *file = fopen(HABITS_FILE, "rb");
  if (file == NULL) {
    *habits = NULL;
    *count = 0;
    return 0;
  }

  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  fseek(file, 0, SEEK_SET);

  *count = size / sizeof(Habit);
  if (*count == 0) {
    *habits = NULL;
    fclose(file);
    return 0;
  }

  *habits = malloc(size);
  if (*habits == NULL) {
    fclose(file);
    return -1;
  }

  fread(*habits, sizeof(Habit), *count, file);
  fclose(file);
  return 0;
}

int save_habits(Habit *habits, int count) {
  FILE *file = fopen(HABITS_FILE, "wb");
  if (file == NULL) {
    return -1;
  }

  if (count > 0 && habits != NULL) {
    fwrite(habits, sizeof(Habit), count, file);
  }

  fclose(file);
  return 0;
}

int load_logs(HabitLog **logs, int *count) {
  FILE *file = fopen(LOGS_FILE, "rb");
  if (file == NULL) {
    *logs = NULL;
    *count = 0;
    return 0;
  }

  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  fseek(file, 0, SEEK_SET);

  *count = size / sizeof(HabitLog);
  if (*count == 0) {
    *logs = NULL;
    fclose(file);
    return 0;
  }

  *logs = malloc(size);
  if (*logs == NULL) {
    fclose(file);
    return -1;
  }

  fread(*logs, sizeof(HabitLog), *count, file);
  fclose(file);
  return 0;
}

int save_logs(HabitLog *logs, int count) {
  FILE *file = fopen(LOGS_FILE, "wb");
  if (file == NULL) {
    return -1;
  }

  if (count > 0 && logs != NULL) {
    fwrite(logs, sizeof(HabitLog), count, file);
  }

  fclose(file);
  return 0;
}
