CC = gcc
CFLAGS = 
DEPS = game.h grid.h util.h search.h hashtable.h fringenode.h gamemodel.h stack.h queue.h
OBJ = main.o game.o grid.o util.o search.o hashtable.o fringenode.o gamemodel.o stack.o queue.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

exe/main: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
