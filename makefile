output: main.o GameControllerServer.o GameControllerClient.o Player.o ClientConnection.o
	g++ -g -std=c++0x main.o GameControllerServer.o GameControllerClient.o Player.o ClientConnection.o -o main

main.o: main.cpp
	g++ -c -g -std=c++0x main.cpp

GameControllerServer.o: GameControllerServer.cpp GameControllerServer.h
	g++ -c -g -std=c++0x GameControllerServer.cpp

GameControllerClient.o: GameControllerClient.cpp GameControllerClient.h
	g++ -c -g -std=c++0x GameControllerClient.cpp

Player.o: Player.cpp Player.h
	g++ -c -g -std=c++0x Player.cpp

ClientConnection.o: ClientConnection.cpp ClientConnection.h
	g++ -c -g -std=c++0x ClientConnection.cpp

val:
	valgrind --tool=memcheck --leak_check=yes --show-reachable=yes --track-fds=yes ./main

clean:
	rm *.o main