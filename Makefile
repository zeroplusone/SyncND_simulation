all: main.o Parameter.o
	g++ -o SyncND.out main.o Parameter.o

main.o: main.cpp
	g++ -c main.cpp

Parameter.p: Parameter.cpp
	g++ -c Parameter.cpp

clean:
	rm *.o