CXX=g++
RM=rm -f

SRCS=main.cpp box.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: nest

nest: $(OBJS)
	$(CXX) -o nest $(OBJS)

main.o : main.cpp box.h

box.o : box.cpp box.h

clean :
	$(RM) $(OBJS)

distclean : clean
	$(RM) nest