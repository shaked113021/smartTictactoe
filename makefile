CFLAGS = `pkg-config --cflags gtk+-3.0` -O0 -Wall -Wextra
LIBS = `pkg-config --libs gtk+-3.0` -export-dynamic
SRC = src/Main.cpp src/Board.cpp src/Bot.cpp src/Window1.cpp src/findpath.cpp src/VictoryChecker.cpp
OBJ = $(SRC:.cpp = .o)
CC = g++

build/bin/Main: $(OBJ)
	$(CC) $(CFLAGS) -o build/bin/Main $(OBJ) $(LIBS)
	cp -r src/Style/* build/Style/
clean:
	rm -f obj/core obj/*.o core

