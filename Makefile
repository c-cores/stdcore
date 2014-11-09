CXXFLAGS	 =  -O2 -g -Wall -fmessage-length=0
SOURCES	    :=  $(shell find * -name '*.cpp')
OBJECTS	    :=  $(SOURCES:%.cpp=%.o)
LDFLAGS		 =  
TARGET		 =  libcore.a

all: $(TARGET)

$(TARGET): $(OBJECTS)
	ar rvs $(TARGET) $(OBJECTS)

%.o: src/%.cpp 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c -o $@ $<
	
clean:
	rm -f $(OBJECTS) $(TARGET)
