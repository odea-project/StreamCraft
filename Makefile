CXX = g++

CXXFLAGS = -std=c++17

CXXFLAGS += -g

CXXFLAGS += -Wall

CXXFLAGS += -fopenmp

CXXFLAGS += -Isrc

CXXFLAGS += -I$(CURDIR)/external/zlib-1.3.1

CXXFLAGS += -I$(CURDIR)/external/zlib-1.3.1/build

LDFLAGS = -L$(CURDIR)/external/zlib-1.3.1/build

LDLIBS = -lzlibstatic

SOURCES = main.cpp

OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = main.exe

all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q src\*.o
	del /Q *.o
	del /Q main.exe

run: clean all
	./$(EXECUTABLE)

runonly:
	./$(EXECUTABLE)


#clean:
#	rm -f $(OBJECTS) $(EXECUTABLE)
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
#$(LDFLAGS)
