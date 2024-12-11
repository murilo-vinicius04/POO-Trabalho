CXX = g++
CXXFLAGS = -std=c++11 -Wall

TARGET = quiz_game
SRCS = main.cpp Quiz.cpp Jogador.cpp
HDRS = Quiz.h Pergunta.h Jogador.h Usuario.h

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run