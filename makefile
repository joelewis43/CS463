output: main.o GameController.o Player.o
	g++ -g -std=c++0x main.o GameController.o Player.o -o main

main.o: main.cpp
	g++ -c -g -std=c++0x main.cpp

GameController.o: GameController.cpp GameController.h
	g++ -c -g -std=c++0x GameController.cpp

Player.o: Player.cpp Player.h
	g++ -c -g -std=c++0x Player.cpp

val:
	valgrind --tool=memcheck --leak_check=yes --show-reachable=yes --track-fds=yes ./main

clean:
	rm *.o main