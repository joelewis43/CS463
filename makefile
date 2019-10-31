output: main.o GameControllerServer.o Player.o serverSocket.o clientSocket.o GameControllerClient.o
	g++ -g -std=c++0x main.o GameControllerServer.o GameControllerClient.o Player.o serverSocket.o clientSocket.o -o main -lncurses

main.o: main.cpp
	g++ -c -g -std=c++0x main.cpp

GameControllerServer.o: headers/GameControllerServer.h lib/GameControllerServer.cpp
	g++ -c -g -std=c++0x lib/GameControllerServer.cpp

GameControllerClient.o: headers/GameControllerClient.h lib/GameControllerClient.cpp
	g++ -c -g -std=c++0x lib/GameControllerClient.cpp -lncurses

Player.o: headers/Player.h lib/Player.cpp
	g++ -c -g -std=c++0x lib/Player.cpp

serverSocket.o: headers/serverSocket.h lib/serverSocket.cpp
	g++ -c -g -std=c++0x lib/serverSocket.cpp

clientSocket.o: headers/clientSocket.h lib/clientSocket.cpp
	g++ -c -g -std=c++0x lib/clientSocket.cpp

val:
	valgrind --tool=memcheck --leak_check=yes --show-reachable=yes --track-fds=yes ./main

clean:
	rm *.o main
