CFLAGS = `pkg-config --cflags gtk+-3.0` -Og -g -Wall -Wextra
LIBS = `pkg-config --libs gtk+-3.0` -export-dynamic
SRC = src/Main.cpp src/Board.cpp src/Bot.cpp src/Window1.cpp
OBJ = $(SRC:.cpp = .o)
CC = g++

bin/Main: $(OBJ)
	$(CC) $(CFLAGS) -o Main $(OBJ) $(LIBS)
clean:
	rm -f obj/core obj/*.o core
