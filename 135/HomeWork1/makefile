CC = g++
CXXFLAGS = -Wall -g
LDFLAGS = -Wall -g
TARGET = program
SRCEXT = cc
SOURCES = $(shell find -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst %,%,$(SOURCES:.$(SRCEXT)=.o))
CXXFLAGS += -std=c++0x
LDLIBS += -std=c++0x

#Uncomment These three lines for production
CXXFLAGS += -DPRODUCTION
#CXXFLAGS += -O3
#LDLIBS += -O3

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ $(INC) -o $@

clean :
	rm *.o
	rm program
