CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = atm

$(TARGET): atm.o
	$(CC) $(CFLAGS) -o $(TARGET) atm.o

atm.o: atm.c atm.h
	$(CC) $(CFLAGS) -c atm.c

clean:
	rm -f $(TARGET) *.o $(DATA_FILE)

.PHONY: clean
