CXX = g++
CXXFLAGS = -std=c++11 -Wall

TARGET = quiz_game
SRCS = main.cpp Quiz.cpp Jogador.cpp

all: $(TARGET)

$(TARGET):
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run