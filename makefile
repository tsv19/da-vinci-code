flags = -Wall 
objects = encriptar.o decriptar.o


all: $(objects)
	g++ $(flags) -o encriptar encriptar.o
	g++ $(flags) -o decriptar decriptar.o


encriptar.o: encriptar.cpp
	g++ -c encriptar.cpp $(flags)


decriptar.o: decriptar.cpp
	g++ -c decriptar.cpp $(flags)


clean:
	rm -r *.o encriptar decriptar