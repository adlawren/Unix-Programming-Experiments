IDIR =../inc
CC=gcc
CFLAGS=-Wall -DMEMWATCH -DMW_STDIO -I$(IDIR)

ODIR=obj

_DEPS = list.h utilities.h mergesort.h tests.h main.h
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ = list.o utilities.o mergesort.o tests.o main.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mergesort: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
