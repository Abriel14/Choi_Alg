CFLAGS := -m64 -g
CFLAGS := -m64 
CC:=gcc $(CFLAGS)
CPP:=g++ $(CFLAGS)
LIBDIR := x64

# ----------------------------------------------------------------------
#
# Use FGb as a library: demo files
#
# ----------------------------------------------------------------------


# --------------------------------------------------

main:main.o Z2_polynoms.o ch_funct.o
	$(CPP)  -o $@ main.o -L$(LIBDIR) -lfgb -lfgbexp -lgb -lgbexp -lminpoly -lminpolyvgf -lgmp -lm -fopenmp

main.static:main.o
	$(CPP) -static -o $@ main.o -L$(LIBDIR) -lfgb -lfgbexp -lgb -lgbexp -lminpoly -lminpolyvgf -L$(GMP_STATIC_DIR) -lgmp -lm -fopenmp

main.o:main.cpp
	$(CC) -I ../../protocol -I ../../int  -c $<
Z2_polynoms.o:Z2_polynoms.cpp
	$(CPP) -I Z2_polynoms.hpp  -cpp $<
ch_funct.o:ch_funct.cpp
	$(CPP) -I ch_funct.hpp  -cpp $<

clean:
	-rm main main.o Z2_polynoms.o ch_funct.o

veryclean:
	-rm main main.o Z2_polynoms.o ch_funct.o *~

test:main
	@echo "======================================================================"
	./main
	@echo "======================================================================"

