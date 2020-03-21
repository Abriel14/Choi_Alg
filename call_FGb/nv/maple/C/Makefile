CFLAGS := -m64 -g
CC:=gcc $(CFLAGS)
CPP:=g++ $(CFLAGS)
LIBDIR := x64

main:main.o Z2_polynoms.o ch_funct.o
	$(CPP) -o $@ main.o Z2_polynoms.o ch_funct.o -L$(LIBDIR) -lfgb -lfgbexp -lgb -lgbexp -lminpoly -lminpolyvgf -L$(GMP_STATIC_DIR) -lgmp -lm -fopenmp

main.static:main.o Z2_polynoms.o ch_funct.o
	$(CPP) -static -o $@ main.o Z2_polynoms.o ch_funct.o -L$(LIBDIR) -lfgb -lfgbexp -lgb -lgbexp -lminpoly -lminpolyvgf -L$(GMP_STATIC_DIR) -lgmp -lm -fopenmp

main.o:main.cpp
	$(CC) -I ../../protocol -I ../../int -c $<

Z2_polynoms.o:Z2_polynoms.cpp Z2_polynoms.hpp 
	$(CC) -I ../../protocol -I ../../int -c $<

ch_funct.o:ch_funct.cpp ch_funct.hpp
	$(CC) -I ../../protocol -I ../../int -c $<

clean:
	-rm main main.o Z2_polynoms.o ch_funct.o

veryclean:
	-rm main main.o Z2_polynoms.o ch_funct.o *~

test:main
	@echo "======================================================================"
	./main
	@echo "======================================================================"

