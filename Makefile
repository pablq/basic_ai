CC = gcc
CFLAGS = 
ODIR = obj
DEPS = game.h grid.h util.h search.h hashtable.h fringenode.h gamemodel.h stack.h queue.h
_OBJ = main.o game.o grid.o util.o search.o hashtable.o fringenode.o gamemodel.o stack.o queue.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

basic_ai: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
