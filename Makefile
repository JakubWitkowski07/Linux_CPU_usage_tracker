CC = clang
CFLAGS = -Wall -Wextra -pthread

CC2 = clang
CFLAGS2 = -Weverything -pthread

TARGET = CUT

OBJS = main.o global.o reader.o analyzer.o printer.o
HEADERS = reader.h analyzer.h printer.h global.h

gcc: $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

clang: $(OBJS)
	$(CC2) $(CFLAGS2) -o $(TARGET) $(OBJS)

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

clean:
	rm -f $(OBJS) $(TARGET)