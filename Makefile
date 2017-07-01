CC=g++
CFLAGS=-c -Wall -std=c++11 -ggdb -I.
LDFLAGS=
COMMON_SOURCES = Node.cpp
SOURCES=main.cpp LinkedBag.cpp
SOURCES_R=mainR.cpp LinkedBagRecursive.cpp
OBJECTS=$(COMMON_SOURCES:.cpp=.o) $(SOURCES:.cpp=.o)
OBJECTS_R=$(COMMON_SOURCES:.cpp=.o) $(SOURCES_R:.cpp=.o)
TARGET=output outputR
TESTS=LinkedBag_Test.h
TESTSSOURCES=LinkedBag_Test.h LinkedBag.h

all: $(TARGET)

FLAGS   = -Iinclude
	
depend: .depend

# file already removed with make clean
# rm -f ./.depend

.depend: $(SOURCES)
	$(CC) $(CFLAGS) -MM $^ > ./.depend;

include .depend
    
output: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

outputR: $(OBJECTS_R) 
	$(CC) $(LDFLAGS) $(OBJECTS_R) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f $(TARGET) *.a *.o *~
	
# Adjust file path way	
CXXLOCATION = /Users/dillondragomir/Desktop/LinkedBagCpp-master/cxxtest-4.3
CXXTESTGEN = $(CXXLOCATION)/bin/cxxtestgen

test: 
	$(CXXTESTGEN) --error-printer -o runner.cpp $(TESTS)
	$(CC) -I. -ggdb -Wall -I$(CXXLOCATION)/ -o runner runner.cpp
	./runner

