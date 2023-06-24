ifeq ($(CCNAME), clang)
CC = clang
CFLAGS = -Weverything -pthread -lrt
else
CC = gcc
CFLAGS = -Wall -Wextra -pthread -lrt
endif
TARGET = CUT
SOURCES = main.c global.c reader.c analyzer.c printer.c watchdog.c .logger.c
OBJS = main.o global.o reader.o analyzer.o printer.o watchdog.o logger.o
HEADERS = reader.h analyzer.h printer.h global.h watchdog.h logger.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) -c main.c

global.o: global.c $(HEADERS)
	$(CC) $(CFLAGS) -c global.c

reader.o: reader.c $(HEADERS)
	$(CC) $(CFLAGS) -c reader.c

analyzer.o: analyzer.c $(HEADERS)
	$(CC) $(CFLAGS) -c analyzer.c

printer.o: printer.c $(HEADERS)
	$(CC) $(CFLAGS) -c printer.c

watchdog.o: watchdog.c $(HEADERS)
	$(CC) $(CFLAGS) -c watchdog.c

logger.o: logger.c $(HEADERS)
	$(CC) $(CFLAGS) -c logger.c

clean:
	rm -f $(OBJS) $(TARGET) log.txt