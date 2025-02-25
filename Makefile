ifeq ($(OS),Windows_NT)
    RM = del
    PATH_SEP = \\
else
    RM = rm -f
    PATH_SEP = /
endif

CXX = g++
CXXFLAGS = -Wall -g 
TARGET = .$(PATH_SEP)bin$(PATH_SEP)test
SRCDIR = .$(PATH_SEP)src
OBJS = sokoban.o Level.o Game.o 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

sokoban.o: $(SRCDIR)$(PATH_SEP)sokoban.cpp $(SRCDIR)$(PATH_SEP)sokoban.hpp $(SRCDIR)$(PATH_SEP)Level.hpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)$(PATH_SEP)sokoban.cpp 

Level.o: $(SRCDIR)$(PATH_SEP)Level.cpp $(SRCDIR)$(PATH_SEP)Level.hpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)$(PATH_SEP)Level.cpp 

Game.o: $(SRCDIR)$(PATH_SEP)Game.cpp $(SRCDIR)$(PATH_SEP)Game.hpp $(SRCDIR)$(PATH_SEP)Level.hpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)$(PATH_SEP)Game.cpp 

clean:
	$(RM) $(OBJS)
