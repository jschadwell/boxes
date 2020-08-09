CXX=g++
RM=rm -f
#CPPFLAGS=-g $(shell root-config --cflags)
CPPFLAGS=-I/usr/local/boost_1_73_0
CXXFLAGS=-std=c++14
#LDFLAGS=-g $(shell root-config --ldflags)
LDFLAGS=-lboost_filesystem -L/usr/local/boost_1_73_0/stage/lib -Wl,-rpath,/usr/local/boost_1_73_0/stage/lib
#LDLIBS=$(shell root-config --libs)

SRCS=nest.cpp BoxRepository.cpp Box.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: nest

nest: $(OBJS)
	$(CXX) $(LDFLAGS) -o nest $(OBJS)

nest.o : nest.cpp BoxRepository.h Box.h

BoxRepository.o : BoxRepository.cpp BoxRepository.h Box.h

Box.o : Box.cpp Box.h

clean :
	$(RM) $(OBJS)

distclean : clean
	$(RM) nest