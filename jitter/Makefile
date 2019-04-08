CXX=clang++-6.0
FLAGS=-std=c++17 -stdlib=libc++ -L/usr/lib/llvm-7/lib  -I/usr/lib/llvm-7/include/c++/v1/ -O2

all: main main-asm main-endless main-identical

main: main.o exp1.o
	${CXX} ${FLAGS} main.o exp1.o -o $@

main-asm: main.o exp2.o
	${CXX} ${FLAGS} main.o exp2.o -o $@

# Requires symlink / copy of the includeos exp.o to includeos_exp.o
main-identical: main.o
	${CXX} ${FLAGS} main.o includeos_exp.o -o $@

main-endless: main-endless.o exp-endless.o
	${CXX} ${FLAGS} main-endless.o exp-endless.o -o $@

%.o : %.cpp
	${CXX} ${FLAGS} -c $< -o $@

clean:
	rm -f *.o main main-asm main-endless
