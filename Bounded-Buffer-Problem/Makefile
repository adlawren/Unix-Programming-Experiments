SDIR=src
IDIR=inc
CC=gcc
CFLAGS=-pthread -Wall -DMEMWATCH -DMW_STDIO -I$(IDIR)

ODIR=obj

_DEPS = deque.h deque_test.h list.h utilities.h assemblers.h packers.h tests.h factory.h
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ = deque.o deque_test.o list.o utilities.o assemblers.o packers.o tests.o factory.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Factory: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(SDIR)/*~ core $(IDIR)/*~
