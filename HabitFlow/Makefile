CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src/main.c src/habit.c src/storage.c
OBJ = $(SRC:.c=.o)
TARGET = habitflow

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)
