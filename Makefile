nest: main.o box.o
	g++ -o nest main.o box.o

main.o : main.cpp box.h
	g++ -c main.cpp

box.o : box.cpp box.h
	g++ -c box.cpp

clean :
	rm main.o box.o

distclean : clean
	rm nest