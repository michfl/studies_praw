IDIR = ../include
CC = gcc
CFLAGS = -I$(IDIR)

ODIR = obj
LDIR = ../lib

_DEPS = benchmark.h mergesort.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o benchmark.o mergesort_plain.o mergesort_openmp.o mergesort_cuda.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_SAMPLEGEN_OBJ = samplegen.o
SAMPLEGEN_OBJ = $(patsubst %,$(ODIR)/%,$(_SAMPLEGEN_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

samplegen: $(SAMPLEGEN_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~