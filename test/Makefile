SOURCES	:= $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o)
GTEST := ../../googletest
INCLUDE_PATH := -I$(GTEST)/include -I../
LIBRARY_PATH := -L$(GTEST) -L../

all: test_stdcore

test: test_stdcore
	./test_stdcore

test_stdcore: $(OBJECTS) gtest_main.o
	$(CXX) $(LIBRARY_PATH) $(OBJECTS) gtest_main.o -pthread -lstdcore -lgtest -o test_stdcore
	
%.o: %.cpp 
	$(CXX) $(INCLUDE_PATH) $< -c -g -o $@
	
gtest_main.o: $(GTEST)/src/gtest_main.cc
	$(CXX) $(INCLUDE_PATH) $< -c -g -o $@
	
clean:
	rm -f *.test
