CC = gcc
CFLAGS = -g
DEPS = game.h grid.h util.h search.h hashtable.h fringenode.h gamemodel.h stack.h
OBJ = basic_ai.o game.o grid.o util.o search.o hashtable.o fringenode.o gamemodel.o stack.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

basicmake: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
