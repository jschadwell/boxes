CXX=g++
RM=rm -f
#CPPFLAGS=-g $(shell root-config --cflags)
CXXFLAGS=-g -std=c++17
#LDFLAGS=-g $(shell root-config --ldflags)
LDFLAGS=-g -lboost_filesystem -L/usr/local/boost_1_73_0/stage/lib -Wl,-rpath,/usr/local/boost_1_73_0/stage/lib
#LDLIBS=$(shell root-config --libs)

SRCS=boxes.cpp BoxConfigParser.cpp Box.cpp DebugPrintVisitor.cpp ReorganizeBoxVisitor.cpp PrettyPrintVisitor.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: boxes

boxes: $(OBJS)
	$(CXX) $(LDFLAGS) -o nest $(OBJS)

boxes.o : boxes.cpp BoxConfigParser.h DebugPrintVisitor.h ReorganizeBoxVisitor.h PrettyPrintVisitor.h Box.h

BoxConfigParser.o : BoxConfigParser.cpp BoxConfigParser.h Box.h

Box.o : Box.cpp Box.h

DebugPrintVisitor.o : DebugPrintVisitor.cpp DebugPrintVisitor.h AbstractBoxVisitor.h Box.h

ReorganizeBoxVisitor.o : ReorganizeBoxVisitor.cpp ReorganizeBoxVisitor.h AbstractBoxVisitor.h Box.h

PrettyPrintVisitor.o : PrettyPrintVisitor.cpp PrettyPrintVisitor.h AbstractBoxVisitor.h Box.h

clean :
	$(RM) $(OBJS)

distclean : clean
	$(RM) nest