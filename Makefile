CC := gcc
TARGET := snake
SRC := src/main.c src/point.c src/movement.c src/snake.c src/game.c
OBJ := $(SRC:.c=.o)

CFLAGS := -std=c99 -pedantic -Wall -Wextra -Werror -Wvla -Iinclude
LDFLAGS := -lncurses

# Rules
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Debug build
debug: CFLAGS += -g3 -fsanitize=address
debug: LDFLAGS += -fsanitize=address -static-libasan
debug: clean $(TARGET)

# Clean
clean:
	$(RM) $(OBJ) $(TARGET)

.PHONY: all clean debug
