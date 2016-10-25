all:tDeque

tDeque: tDeque_main.o tDeque.h
	g++ tDeque_main.o -o tDeque
	
tDeque_main.o: tDeque_main.cpp
	g++ -c tDeque_main.cpp
	
clean:
	rm *o tDeque