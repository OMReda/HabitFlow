#include "../include/habit.h"
#include "../include/stats.h"
#include "../include/ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

void enable_ansi_colors() {
#ifdef _WIN32
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  if (hOut == INVALID_HANDLE_VALUE)
    return;
  DWORD dwMode = 0;
  if (!GetConsoleMode(hOut, &dwMode))
    return;
  dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  SetConsoleMode(hOut, dwMode);
  SetConsoleOutputCP(CP_UTF8);
#endif
}

void print_usage() {
  printf(COLOR_CYAN BOLD_TEXT "HabitFlow - Habit Tracker" COLOR_RESET "\n");
  printf("Usage:\n");
  printf("  " COLOR_GREEN "habitflow add \"Habit Name\"" COLOR_RESET "\n");
  printf("  " COLOR_GREEN "habitflow list" COLOR_RESET "\n");
  printf("  " COLOR_GREEN "habitflow edit <id> \"New Name\"" COLOR_RESET "\n");
  printf("  " COLOR_YELLOW "habitflow check <id>" COLOR_RESET "\n");
  printf("  " COLOR_YELLOW "habitflow stats <id>" COLOR_RESET "\n");
  printf("  " COLOR_MAGENTA "habitflow dashboard" COLOR_RESET "\n");
  printf("  " COLOR_BLUE "habitflow export [filename]" COLOR_RESET "\n");
  printf("  " COLOR_RED "habitflow delete <id>" COLOR_RESET "\n");
}

void run_interactive_mode() {
  char input[256];
  printf(COLOR_CYAN BOLD_TEXT "\n");
  printf("  _    _       _     _ _ ______ _               \n");
  printf(" | |  | |     | |   (_) |  ____| |              \n");
  printf(" | |__| | __ _| |__  _| | |__  | | _____      __\n");
  printf(" |  __  |/ _` | '_ \\| | |  __| | |/ _ \\ \\ /\\ / /\n");
  printf(" | |  | | (_| | |_) | | | |    | | (_) \\ V  V / \n");
  printf(" |_|  |_|\\__,_|_.__/|_|_|_|    |_|\\___/ \\_/\\_/  \n");
  printf("\n" COLOR_RESET);
  printf("Welcome to " COLOR_CYAN BOLD_TEXT
         "HabitFlow Interactive Mode!" COLOR_RESET "\n\n");

  while (1) {
    printf(COLOR_MAGENTA BOLD_TEXT
           "========================================" COLOR_RESET "\n");
    printf(COLOR_CYAN BOLD_TEXT
           "               MAIN MENU                " COLOR_RESET "\n");
    printf(COLOR_MAGENTA BOLD_TEXT
           "========================================" COLOR_RESET "\n\n");

    printf("  " COLOR_GREEN "[1]" COLOR_RESET " Dashboard        " COLOR_YELLOW
           "[5]" COLOR_RESET " View Statistics\n");
    printf("  " COLOR_GREEN "[2]" COLOR_RESET " List Habits      " COLOR_CYAN
           "[6]" COLOR_RESET " Edit Habit\n");
    printf("  " COLOR_GREEN "[3]" COLOR_RESET " Add Habit        " COLOR_MAGENTA
           "[7]" COLOR_RESET " Delete Habit\n");
    printf("  " COLOR_GREEN "[4]" COLOR_RESET " Check-In Habit   " COLOR_BLUE
           "[8]" COLOR_RESET " Export to CSV\n\n");
    printf("  " COLOR_RED "[0]" COLOR_RESET " Exit\n\n");
    printf(COLOR_MAGENTA " " EMOJI_DASH " Select an option: " COLOR_RESET);

    if (!fgets(input, sizeof(input), stdin)) {
      break;
    }

    input[strcspn(input, "\n")] = 0;
    if (strlen(input) == 0)
      continue;

    int choice = atoi(input);

    if (strcmp(input, "0") == 0) {
      break;
    } else if (choice == 1) {
      show_dashboard();
    } else if (choice == 2) {
      list_habits();
    } else if (choice == 3) {
      printf(COLOR_CYAN "Enter habit name: " COLOR_RESET);
      if (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = 0;
        if (strlen(input) > 0)
          add_habit(input);
      }
    } else if (choice == 4) {
      printf(COLOR_CYAN "Enter habit ID to check-in: " COLOR_RESET);
      if (fgets(input, sizeof(input), stdin)) {
        int id = atoi(input);
        if (id > 0)
          check_in(id);
      }
    } else if (choice == 5) {
      printf(COLOR_CYAN "Enter habit ID for stats: " COLOR_RESET);
      if (fgets(input, sizeof(input), stdin)) {
        int id = atoi(input);
        if (id > 0)
          show_stats(id);
      }
    } else if (choice == 6) {
      printf(COLOR_CYAN "Enter habit ID to edit: " COLOR_RESET);
      char id_str[256];
      if (fgets(id_str, sizeof(id_str), stdin)) {
        int id = atoi(id_str);
        if (id > 0) {
          printf(COLOR_CYAN "Enter new name: " COLOR_RESET);
          if (fgets(input, sizeof(input), stdin)) {
            input[strcspn(input, "\n")] = 0;
            if (strlen(input) > 0)
              edit_habit(id, input);
          }
        }
      }
    } else if (choice == 7) {
      printf(COLOR_RED "Enter habit ID to delete: " COLOR_RESET);
      if (fgets(input, sizeof(input), stdin)) {
        int id = atoi(input);
        if (id > 0)
          delete_habit(id);
      }
    } else if (choice == 8) {
      export_csv("export.csv");
    } else {
      printf(COLOR_RED "Invalid choice. Please try again." COLOR_RESET "\n");
    }

    printf("\n" COLOR_CYAN BOLD_TEXT
           "Press Enter to return to the main menu..." COLOR_RESET);
    if (!fgets(input, sizeof(input), stdin))
      break;

    // Clear screen for the next iteration
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
  }
}

int main(int argc, char *argv[]) {
  enable_ansi_colors();

  if (argc < 2) {
    run_interactive_mode();
    return 0;
  }

  if (strcmp(argv[1], "add") == 0) {
    if (argc < 3) {
      printf("Error: Missing habit name.\n");
      return 1;
    }
    add_habit(argv[2]);
  } else if (strcmp(argv[1], "list") == 0) {
    list_habits();
  } else if (strcmp(argv[1], "edit") == 0) {
    if (argc < 4) {
      printf("Usage: habitflow edit <id> \"New Name\"\n");
      return 1;
    }
    edit_habit(atoi(argv[2]), argv[3]);
  } else if (strcmp(argv[1], "delete") == 0) {
    if (argc < 3) {
      printf("Usage: habitflow delete <id>\n");
      return 1;
    }
    delete_habit(atoi(argv[2]));
  } else if (strcmp(argv[1], "check") == 0) {
    if (argc < 3) {
      printf("Usage: habitflow check <id>\n");
      return 1;
    }
    check_in(atoi(argv[2]));
  } else if (strcmp(argv[1], "stats") == 0) {
    if (argc < 3) {
      printf("Usage: habitflow stats <id>\n");
      return 1;
    }
    show_stats(atoi(argv[2]));
  } else if (strcmp(argv[1], "dashboard") == 0) {
    show_dashboard();
  } else if (strcmp(argv[1], "export") == 0) {
    const char *file = (argc >= 3) ? argv[2] : "export.csv";
    export_csv(file);
  } else {
    printf("Unknown command: %s\n", argv[1]);
    print_usage();
    return 1;
  }

  return 0;
}
