CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -Isrc

ZLIBDIR = external/mstoolkit/src/zlib-1.2.11
CXXFLAGS += -I$(ZLIBDIR)
# LDFLAGS = -L$(ZLIBDIR)
# LDLIBS = -lz

CXXFLAGS += -DGCC
CXXFLAGS += -D_FILE_OFFSET_BITS=64

MSTOOLKITDIR = external/mstoolkit
MSTOOLKITDIRINCLUDE = $(MSTOOLKITDIR)/include
CXXFLAGS += -I$(MSTOOLKITDIRINCLUDE)

MSTOOLKITLIB = $(MSTOOLKITDIR)/libmstoolkit.a
LDLIBS += $(MSTOOLKITLIB)

SOURCES = $(wildcard src/*.cpp) main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

CXXFLAGS += -fopenmp

EXECUTABLE = main

# $(LDFLAGS)

all: $(OBJECTS)
	$(CXX) $(CXXFLAGS)  $(OBJECTS) -o $(EXECUTABLE) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

run: clean all
	./$(EXECUTABLE)

runonly:
	./$(EXECUTABLE)
