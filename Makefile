# ==============================================================
# Makefile — system_monitor
# Description : Build system for the Linux system monitor tool
# ==============================================================

CC      = gcc
CFLAGS  = -Wall -Wextra -Wpedantic -std=c11 -I./include
SRC     = src/main.c src/cpu_monitor.c src/memory_monitor.c src/logger.c
TARGET  = system_monitor

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) logs/monitor.log

run: all
	./$(TARGET)
