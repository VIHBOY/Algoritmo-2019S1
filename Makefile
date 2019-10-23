CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = bin/artpoints
SRC = $(addprefix src/, Graph.cpp)

all : $(SRC)
		$(CXX) $(SRC) $(CXXFLAGS) -o $(TARGET)