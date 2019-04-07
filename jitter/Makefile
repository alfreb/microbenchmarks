CXX=clang++-6.0
FLAGS=-std=c++11 -O2

all: main main-asm main-endless

main: main.o exp1.o
	${CXX} ${FLAGS} main.o exp1.o -o $@

main-asm: main.o exp2.o
	${CXX} ${FLAGS} main.o exp2.o -o $@

main-endless: main-endless.o exp-endless.o
	${CXX} ${FLAGS} main-endless.o exp-endless.o -o $@

%.o : %.cpp
	${CXX} ${FLAGS} -c $< -o $@

clean:
	rm -f *.o main main-asm main-endless
