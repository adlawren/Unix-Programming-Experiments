SDIR=src
IDIR=inc
CC=gcc
CFLAGS=-pthread -Wall -DMEMWATCH -DMW_STDIO -I$(IDIR)

ODIR=obj

_DEPS = dynamic_string_array.h dynamic_string_array_test.h display_file_info.h display_dir.h main.h
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ = dynamic_string_array.o dynamic_string_array_test.o display_file_info.o display_dir.o main.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lsRalF: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(SDIR)/*~ core $(IDIR)/*~
