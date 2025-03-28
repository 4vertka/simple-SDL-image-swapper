TARGET = game
SRC = main.cpp engine.cpp

all:
	g++ $(SRC) -o $(TARGET) -lSDL2

clean:
	rn -r $(TARGET)
