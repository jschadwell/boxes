CXX=g++
RM=rm -f
#CPPFLAGS=-g $(shell root-config --cflags)
CXXFLAGS=-g -std=c++17
#LDFLAGS=-g $(shell root-config --ldflags)
LDFLAGS=-g -lboost_filesystem -L/usr/local/boost_1_73_0/stage/lib -Wl,-rpath,/usr/local/boost_1_73_0/stage/lib
#LDLIBS=$(shell root-config --libs)

SRCS=nest.cpp BoxConfigParser.cpp Box.cpp DebugPrintVisitor.cpp ReorganizeBoxVisitor.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: nest

nest: $(OBJS)
	$(CXX) $(LDFLAGS) -o nest $(OBJS)

nest.o : nest.cpp BoxConfigParser.h DebugPrintVisitor.h ReorganizeBoxVisitor.h

BoxConfigParser.o : BoxConfigParser.cpp BoxConfigParser.h

Box.o : Box.cpp Box.h

DebugPrintVisitor.o : DebugPrintVisitor.cpp DebugPrintVisitor.h AbstractBoxVisitor.h

ReorganizeBoxVisitor.o : ReorganizeBoxVisitor.cpp ReorganizeBoxVisitor.h AbstractBoxVisitor.h

clean :
	$(RM) $(OBJS)

distclean : clean
	$(RM) nest