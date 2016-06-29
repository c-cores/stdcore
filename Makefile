CXXFLAGS	=  -O2 -g -Wall -fmessage-length=0 -I.
SOURCES		:=  $(shell find core -name '*.cpp')
OBJECTS		:=  $(SOURCES:%.cpp=%.o)
TARGET		= libstdcore.a

all: $(TARGET) test

test:

$(TARGET): $(OBJECTS)
	ar rvs $(TARGET) $(OBJECTS)

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
clean:
	rm -f core/*.o $(TARGET)