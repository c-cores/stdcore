CXXFLAGS	=  -g -fprofile-arcs -ftest-coverage -O2 -Wall -fmessage-length=0 -I. 
SOURCES		:=  $(wildcard core/*.cpp)
TESTS       := $(wildcard test/*.cpp)
OBJECTS		:=  $(SOURCES:%.cpp=%.o)
TEST_OBJECTS   := $(TESTS:.cpp=.o)
DEPS        := $(OBJECTS:.o=.d)
TEST_DEPS   := $(TEST_OBJECTS:.o=.d)
GTEST       := ../googletest
GTEST_I     := -I$(GTEST)/include -I.
GTEST_L     := -L$(GTEST) -L.
TARGET		= libstdcore.a
TEST_TARGET = test_stdcore

-include $(DEPS)
-include $(TEST_DEPS)

all: lib check

lib: $(TARGET)

test: lib $(TEST_TARGET)

check: test
	./$(TEST_TARGET)

$(TARGET): $(OBJECTS)
	ar rvs $(TARGET) $(OBJECTS)

core/%.o: core/%.cpp 
	$(CXX) $(CXXFLAGS) -MM -MF $(patsubst %.o,%.d,$@) -MT $@ -c $<
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(TEST_TARGET): $(TEST_OBJECTS) test/gtest_main.o
	$(CXX) $(CXXFLAGS) $(GTEST_L) $(TEST_OBJECTS) test/gtest_main.o -pthread -lstdcore -lgtest -o $(TEST_TARGET)

test/%.o: test/%.cpp
	$(CXX) $(CXXFLAGS) $(GTEST_I) -MM -MF $(patsubst %.o,%.d,$@) -MT $@ -c $<
	$(CXX) $(CXXFLAGS) $(GTEST_I) $< -c -o $@
	
test/gtest_main.o: $(GTEST)/src/gtest_main.cc
	$(CXX) $(CXXFLAGS) $(GTEST_I) $< -c -o $@

clean:
	rm -f core/*.o test/*.o
	rm -f core/*.d test/*.d
	rm -f core/*.gcda test/*.gcda
	rm -f core/*.gcno test/*.gcno
	rm -f $(TARGET) $(TEST_TARGET)