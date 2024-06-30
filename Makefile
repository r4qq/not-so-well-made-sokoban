CXX = g++
CXXFLAGS = -Wall -g 
TARGET = .\bin\test
OBJS = sokoban.o Level.o Game.o 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

sokoban.o: .\src\sokoban.cpp .\src\sokoban.hpp .\src\Level.hpp
	$(CXX) $(CXXFLAGS) -c .\src\sokoban.cpp 

Level.o: .\src\Level.cpp .\src\Level.hpp
	$(CXX) $(CXXFLAGS) -c .\src\Level.cpp 

Game.o: .\src\Game.cpp .\src\Game.hpp .\src\Level.hpp 
	$(CXX) $(CXXFLAGS) -c .\src\Game.cpp 

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean