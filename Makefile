game: main.o matrix.o city.o environment.o random.o output.o
	g++ -g -std=c++0x main.o matrix.o city.o environment.o random.o output.o -o game -lncurses
main.o: main.cpp
	g++ -c -g -std=c++0x main.cpp
city.o: lib/city.h lib/city.cpp random.o
	g++ -c -g -std=c++0x random.o lib/city.cpp
environment.o: lib/environment.h lib/environment.cpp
	g++ -c -g -std=c++0x lib/environment.cpp -lncurses
matrix.o: lib/matrix.cpp lib/matrix.h lib/object.h lib/character.h lib/comet.h
	g++ -c -g -std=c++0x lib/matrix.cpp
random.o: lib/random.h lib/random.cpp
	g++ -c -g -std=c++0x lib/random.cpp
output.o: src/output.h src/output.cpp
	g++ -c -g -std=c++0x src/output.cpp -lncurses
clean:
	rm *.o game