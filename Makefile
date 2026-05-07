CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
TARGET = ticketsystem

all: $(TARGET)

$(TARGET): ticketsystem.c ticketsystem.h
	$(CC) $(CFLAGS) ticketsystem.c -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean