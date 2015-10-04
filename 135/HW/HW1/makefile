CC = g++
CXXFLAGS = -Wall -g
LDFLAGS = -Wall -g
#LDLIBS = 
#SRCDIR = src
#BUILDDIR = build
TARGET = program
SRCEXT = cc

SOURCES := $(shell find -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst %,%,$(SOURCES:.$(SRCEXT)=.o))

#C++ 14 Libraries  OR C++11
#CXXFLAGS += -std=c++14
#LDLIBS += -std=c++14
CXXFLAGS += -std=c++11
LDLIBS += -std=c++11

#INC = -I include

#Uncomment for threading
#CXXFLAGS += -pthread
#LDLIBS += -pthread

#Uncomment for Deployment Optimization Compilation
#CXXFLAGS += -O3
#LDLIBS += -O3

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ $(INC) -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) 
	$(CC) -c $(CXXFLAGS) $(INC) $< -o $@

clean :
	rm *.o
	rm program
	rm test
