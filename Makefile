game: main.o matrix.o
	g++ -g -std=c++0x main.o matrix.o -o game
main.o: main.cpp
	g++ -c -g -std=c++0x main.cpp
matrix.o: lib/matrix.cpp lib/matrix.h lib/object.h lib/character.h lib/comet.h
	g++ -c -g -std=c++0x lib/matrix.cpp
clean:
	rm *.o game