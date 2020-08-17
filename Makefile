CXX=g++
RM=rm -f
#CPPFLAGS=-g $(shell root-config --cflags)
CPPFLAGS=-I/usr/local/boost_1_73_0
CXXFLAGS=-std=c++14
#LDFLAGS=-g $(shell root-config --ldflags)
LDFLAGS=-lboost_filesystem -L/usr/local/boost_1_73_0/stage/lib -Wl,-rpath,/usr/local/boost_1_73_0/stage/lib
#LDLIBS=$(shell root-config --libs)

SRCS=nest.cpp BoxConfigWrapper.cpp BoxConfigurator.cpp BoxConfiguration.cpp BoxRepository.cpp Box.cpp pugixml.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: nest

nest: $(OBJS)
	$(CXX) $(LDFLAGS) -o nest $(OBJS)

nest.o : nest.cpp BoxConfigWrapper.h BoxConfigurator.h BoxConfiguration.h BoxRepository.h

BoxConfigWrapper.o : BoxConfigWrapper.cpp BoxConfigWrapper.h

BoxConfigurator.o : BoxConfigurator.cpp BoxConfigurator.h BoxConfiguration.h

BoxConfiguration.o : BoxConfiguration.cpp BoxConfiguration.h

BoxRepository.o : BoxRepository.cpp BoxRepository.h Box.h

Box.o : Box.cpp Box.h

# Third-party XML library
pugixml.o : pugixml.cpp pugixml.hpp pugiconfig.hpp

clean :
	$(RM) $(OBJS)

distclean : clean
	$(RM) nest