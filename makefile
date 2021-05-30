CFLAGS = `pkg-config --cflags gtk+-3.0` -O0 -Wall -Wextra -I src/include
LIBS = `pkg-config --libs gtk+-3.0` -export-dynamic
SRC = src/cpp/Main.cpp src/cpp/tictactoe/Board.cpp src/cpp/tictactoe/Bot.cpp src/cpp/Window1.cpp src/cpp/findpath.cpp src/cpp/tictactoe/VictoryChecker.cpp src/cpp/tictactoe/botstrategies/RandomMoveStrategy.cpp src/cpp/tictactoe/botstrategies/MinimaxStrategy.cpp src/cpp/tictactoe/Move.cpp
OBJ = $(SRC:.cpp = .o)
CC = g++

build/bin/Main: $(OBJ)
	$(CC) $(CFLAGS) -o build/bin/Main $(OBJ) $(LIBS)
	cp -r src/Style/* build/Style/
clean:
	rm -f obj/core obj/*.o core

