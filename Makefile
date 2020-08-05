CXX=g++
RM=rm -f
#CPPFLAGS=-g $(shell root-config --cflags)
CPPFLAGS=-I/usr/local/boost_1_73_0
#LDFLAGS=-g $(shell root-config --ldflags)
LDFLAGS=
#LDLIBS=$(shell root-config --libs)

SRCS=nest.cpp box.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: nest

nest: $(OBJS)
	$(CXX) $(LDFLAGS) -o nest $(OBJS)

main.o : main.cpp box.h

box.o : box.cpp box.h

clean :
	$(RM) $(OBJS)

distclean : clean
	$(RM) nest