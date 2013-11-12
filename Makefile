CXXFLAGS=-g -std=c++0x -O3 -DNDEBUG -Wall -pedantic
CPPFLAGS=-I. -Ilib   
LDFLAGS=-g 

SRCS= topo-builder.cpp builder.cpp script.cpp

OBJS=$(subst .cpp,.o,$(SRCS))

all: topo-builder

topo-builder: $(OBJS)
	    $(CXX) $(LDFLAGS) -o topo-builder $(OBJS) $(LDLIBS)

clean:
	    $(RM) $(OBJS) topo-builder 

dist-clean: clean
	    $(RM) *~ *.o
