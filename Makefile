CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -Isrc

ZLIBDIR = C:/Users/apoli/Documents/github/StreamCraft/external/zlib-1.3.1
CXXFLAGS += -I$(ZLIBDIR)
CXXFLAGS += -I$(ZLIBDIR)/build
LDFLAGS = -L$(ZLIBDIR)/build
LDLIBS = -lzlibstatic

#ZLIBDIR = C:/Users/apoli/Documents/github/StreamCraft/external/zlib-1.3.1
#ZLIBBUILDDIR = $(ZLIBDIR)/build
#CXXFLAGS += -I$(ZLIBDIR)
#LDFLAGS = -L$(ZLIBBUILDDIR)
#LDLIBS = -lzlibstatic

#CXXFLAGS += -DGCC
#CXXFLAGS += -D_FILE_OFFSET_BITS=64

#MSTOOLKITDIR = external/mstoolkit
#MSTOOLKITDIRINCLUDE = $(MSTOOLKITDIR)/include
#CXXFLAGS += -I$(MSTOOLKITDIRINCLUDE)

#MSTOOLKITLIB = $(MSTOOLKITDIR)/libmstoolkit.a
#LDLIBS += $(MSTOOLKITLIB)

#SOURCES = external/qAlgorithms/src/qalgorithms_matrix.cpp
#SOURCES += external/qAlgorithms/src/qalgorithms_utils.cpp
#SOURCES += external/qAlgorithms/src/qalgorithms.cpp
#CXXFLAGS += -Iexternal/qAlgorithms/src
#CXXFLAGS += -Iexternal/qAlgorithms/include

#SOURCES = $(wildcard src/*.cpp) main.cpp
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

CXXFLAGS += -fopenmp

EXECUTABLE = main.exe

all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

#clean:
#	rm -f $(OBJECTS) $(EXECUTABLE)

clean:
	del /Q src\*.o
	del /Q *.o
	del /Q main.exe

run: clean all
	./$(EXECUTABLE)

runonly:
	./$(EXECUTABLE)
