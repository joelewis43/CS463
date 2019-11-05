all: client server


client: client.o GameControllerClient.o Player.o clientSocket.o
	g++ -g -std=c++0x client.o GameControllerClient.o Player.o clientSocket.o -o client -lncurses

client.o: client.cpp
	g++ -c -g -std=c++0x client.cpp


server: server.o GameControllerServer.o Player.o serverSocket.o
	g++ -g -std=c++0x server.o GameControllerServer.o Player.o serverSocket.o -o server -lncurses

server.o: server.cpp
	g++ -c -g -std=c++0x server.cpp


GameControllerServer.o: lib/GameControllerServer.cpp headers/GameControllerServer.h
	g++ -c -g -std=c++0x lib/GameControllerServer.cpp

GameControllerClient.o: lib/GameControllerClient.cpp headers/GameControllerClient.h
	g++ -c -g -std=c++0x lib/GameControllerClient.cpp


Player.o: lib/Player.cpp headers/Player.h
	g++ -c -g -std=c++0x lib/Player.cpp


serverSocket.o: lib/serverSocket.cpp headers/serverSocket.h
	g++ -c -g -std=c++0x lib/serverSocket.cpp

clientSocket.o: lib/clientSocket.cpp headers/clientSocket.h
	g++ -c -g -std=c++0x lib/clientSocket.cpp


gameboard.o: matrix.o city.o environment.o random.o window.o
	ld -r matrix.o city.o environment.o random.o window.o -o gameboard.o

city.o: headers/city.h lib/city.cpp
	g++ -c -g -std=c++0x lib/city.cpp

environment.o: headers/environment.h lib/environment.cpp
	g++ -c -g -std=c++0x lib/environment.cpp

matrix.o: lib/matrix.cpp headers/matrix.h headers/object.h headers/character.h headers/comet.h
	g++ -c -g -std=c++0x lib/matrix.cpp

random.o: headers/random.h lib/random.cpp
	g++ -c -g -std=c++0x lib/random.cpp

window.o: headers/window.h lib/window.cpp
	g++ -c -g -std=c++0x lib/window.cpp


val:
	valgrind --tool=memcheck --leak_check=yes --show-reachable=yes --track-fds=yes ./main

clean:
	rm *.o server client