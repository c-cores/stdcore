SOURCES		:=  $(wildcard *.cpp)
TESTS := $(SOURCES:.cpp=.test)

all: $(TESTS) test

test: $(TESTS)
	 $(foreach var,$(TESTS),./$(var);)

%.test: %.cpp 
	$(CXX) -I../../googletest/include -I../ -L../ -L../../googletest -pthread $< -lstdcore -lgtest ../../googletest/src/gtest_main.cc -o $@

clean:
	rm -f *.test
