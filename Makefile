CC=clang
CFLAGS = -Weverything

CC2=gcc
C2FLAGS = -Wall -Wextra

clang:
	$(CC) $(CFLAGS) main.c global.c reader.c analyzer.c printer.c -o clangcompilation

gcc:
	$(CC2) $(C2FLAGS) main.c global.c reader.c analyzer.c printer.c -o gcccompilation

clean:
	rm -rf *.o gcccompilation clangcompilation