FLAGS=-std=c++11

all: main main-endless

main: main.o exp1.o 
	${CXX} ${FLAGS} main.o exp1.o -o main

main-endless: main-endless.o exp-endless.o
	${CXX} ${FLAGS} main-endless.o exp-endless.o -o main-endless

main.o: 
	${CXX} ${FLAGS} -c main.cpp 

exp1.o: 
	${CXX} ${FLAGS} -c exp1.cpp 

main-endless.o:
	${CXX} ${FLAGS} -c main-endless.cpp 

exp-endless.o:
	${CXX} ${FLAGS} -c exp-endless.cpp

clean:
	rm -f *.o main main-endless
