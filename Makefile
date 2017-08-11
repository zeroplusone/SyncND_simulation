CC = g++
CFLAGS = -std=c++11
OBJS = Node.o Group.o Parameter.o main.o 
PROG = SyncND.out

all: $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Parameter.o: Parameter.cpp
	$(CC) $(CFLAGS) -c Parameter.cpp

Node.o: Node.cpp
	$(CC) $(CFLAGS) -c Node.cpp

Group.o: Group.cpp
	$(CC) $(CFLAGS) -c Group.cpp

clean:
	rm *.o