CXX = g++
CXXFLAGS = -std=c++11 -Ithird-party/pugixml-1.14/src

SOURCES = $(wildcard src/*.cpp) third-party/pugixml-1.14/src/pugixml.cpp
OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = testme

all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
