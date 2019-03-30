CC = gcc
CFLAGS = -Wall -Wextra
OBJ = date.o file.o list.o main.o todo.o tui.o

todo: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

date.o: date.c
file.o: file.c
list.o: list.c todo.h
list.o: list.c todo.h
main.o: main.c todo.h tui.h
todo.o: todo.c date.h file.h list.h todo.h
tui.o: tui.c file.h todo.h

.PHONY: clean
clean:
	rm todo $(OBJ)
