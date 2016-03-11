CXXFLAGS	=  -O2 -g -Wall -fmessage-length=0
SOURCES		:=  $(shell find stdcore -name '*.cpp')
OBJECTS		:=  $(SOURCES:%.cpp=%.o)
TARGET		= libstdcore.a

all: $(TARGET)

$(TARGET): $(OBJECTS)
	ar rvs $(TARGET) $(OBJECTS)

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
clean:
	rm -f $(OBJECTS) $(TARGET)
