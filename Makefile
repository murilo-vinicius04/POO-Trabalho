
CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = 

# Nome do executável
TARGET = quiz_game

# Arquivos fonte
SRCS = main.cpp Quiz.cpp

# Arquivos objeto
OBJS = $(SRCS:.cpp=.o)

# Regra padrão para compilar o projeto
all: $(TARGET)

# Regra para compilar o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Regra para compilar os arquivos objeto
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar os arquivos compilados
clean:
	rm -f $(TARGET) $(OBJS)

# Regra para rodar o jogo
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run