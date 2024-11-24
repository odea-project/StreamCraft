# This Makefile is written for MSYS2/MINGW64 or Linux.
# If you are using other OS, you may need to modify the Makefile.

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

SOURCES = $(wildcard src/*.cpp)

SOURCES += main.cpp

OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = main.exe

SOURCES_TESTS = test.cpp

OBJECTS_TESTS = $(SOURCES_TESTS:.cpp=.o)

EXECUTABLE_TESTS = test.exe

all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(LDLIBS)

test: $(OBJECTS_TESTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS_TESTS) -o $(EXECUTABLE_TESTS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o
	rm -f *.o
	rm -f main.exe

cleantest:
	rm -f src/*.o
	rm -f *.o
	rm -f test.exe

run: clean all
	./$(EXECUTABLE)

runtest: clean test
	./$(EXECUTABLE_TESTS)

runonly:
	./$(EXECUTABLE)
