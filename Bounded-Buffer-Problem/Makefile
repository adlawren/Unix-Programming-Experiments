SDIR=src
IDIR=inc
CC=gcc
CFLAGS=-pthread -Wall -DMEMWATCH -DMW_STDIO -I$(IDIR)

ODIR=obj

_DEPS = product.h utilities.h deque.h deque_test.h list.h list_test.h assemblers.h packers.h factory.h
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ = utilities.o deque.o deque_test.o list.o list_test.o assemblers.o packers.o factory.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Factory: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(SDIR)/*~ core $(IDIR)/*~
