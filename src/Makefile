IDIR = ../include
CC = nvcc
CFLAGS = -I$(IDIR)
OMPFLAGS=-Xcompiler -fopenmp

ODIR = obj
LDIR = ../lib

_DEPS = mergesort.h mergesort_sequential.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o mergesort_sequential.o mergesort_openmp.o mergesort_openmp_opt.o mergesort_cuda.o mergesort_cuda_opt.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_SAMPLEGEN_OBJ = samplegen.o
SAMPLEGEN_OBJ = $(patsubst %,$(ODIR)/%,$(_SAMPLEGEN_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(OMPFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(OMPFLAGS)

samplegen: $(SAMPLEGEN_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~