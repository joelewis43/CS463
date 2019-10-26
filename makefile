output: main.o GameControllerServer.o GameControllerClient.o Player.o serverSocket.o clientSocket.o
	g++ -g -std=c++0x main.o GameControllerServer.o GameControllerClient.o Player.o serverSocket.o clientSocket.o -o main

main.o: main.cpp
	g++ -c -g -std=c++0x main.cpp

GameControllerServer.o: GameControllerServer.cpp GameControllerServer.h
	g++ -c -g -std=c++0x GameControllerServer.cpp

GameControllerClient.o: GameControllerClient.cpp GameControllerClient.h
	g++ -c -g -std=c++0x GameControllerClient.cpp

Player.o: Player.cpp Player.h
	g++ -c -g -std=c++0x Player.cpp

serverSocket.o: serverSocket.cpp serverSocket.h
	g++ -c -g -std=c++0x serverSocket.cpp

clientSocket.o: clientSocket.cpp clientSocket.h
	g++ -c -g -std=c++0x clientSocket.cpp

val:
	valgrind --tool=memcheck --leak_check=yes --show-reachable=yes --track-fds=yes ./main

clean:
	rm *.o main