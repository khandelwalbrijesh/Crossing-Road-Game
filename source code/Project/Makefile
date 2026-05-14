CXX ?= c++
CXXFLAGS = -std=c++17 -Wall -Wno-unused-variable

SRCS = main.cpp Console.cpp Map.cpp GamePlay.cpp Bird.cpp Bus.cpp Car.cpp \
       Dog.cpp Enemy.cpp Lane.cpp Level.cpp Player.cpp Position.cpp Road.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = CrossingRoad

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
