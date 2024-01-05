CXX = g++
CXXFLAGS = -std=c++11

ZLIBDIR = external/mstoolkit/src/zlib-1.2.11
CXXFLAGS += -Wall -I$(ZLIBDIR)
LDFLAGS = -L$(ZLIBDIR)
LDLIBS = -lz

# CXXFLAGS += -DGCC
# CXXFLAGS += -D_FILE_OFFSET_BITS=64

# MSTOOLKITDIR = external/mstoolkit
# MSTOOLKITDIRINCLUDE = external/mstoolkit/include

SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = main

# SHAREDZLIB = $(ZLIBDIR)/libz.a

all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
