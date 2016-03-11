CXXFLAGS	=  -O2 -g -Wall -fmessage-length=0
SOURCES		:=  $(shell find core -name '*.cpp')
OBJECTS		:=  $(SOURCES:%.cpp=%.o)
INC_PATHS	=
LIB_PATHS	=
LDFLAGS		=
TARGET		= libstdcore.a

all: $(TARGET)

$(TARGET): $(OBJECTS)
	ar rvs $(TARGET) $(OBJECTS)

%.o: core/%.cpp 
	$(CXX) ${INC_PATHS} $(CXXFLAGS) $(LDFLAGS) -c -o $@ $<
	
clean:
	rm -f $(OBJECTS) $(TARGET)
