CC = gcc
CFLAGS = -g
DEPS = game.h grid.h util.h search.h hashtable.h fringe.h gamemodel.h
OBJ = basic_ai.o game.o grid.o util.o search.o hashtable.o fringe.o gamemodel.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

basicmake: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
