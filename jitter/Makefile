FLAGS=-std=c++11

all: exp1 main exp-endless main-endless
	${CXX} ${FLAGS} main.o exp1.o -o main
	${CXX} ${FLAGS} main-endless.o exp-endless.o -o main-endless

main: 
	${CXX} ${FLAGS} -c main.cpp 

exp1: 
	${CXX} ${FLAGS} -c exp1.cpp 

main-endless:
	${CXX} ${FLAGS} -c main-endless.cpp 

exp-endless:
	${CXX} ${FLAGS} -c exp-endless.cpp
