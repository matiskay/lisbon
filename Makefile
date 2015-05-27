LDFLAGS=-lncurses

all:
	 gcc -c graph.c
	 gcc -c main.c
	 gcc -o main graph.o main.o

test_graph: clean
	 gcc -c graph.c
	 gcc -c test_graph.c
	 gcc -o test_graph graph.o test_graph.o
	 ./test_graph

test:	 test_graph

clean:
	 rm *.out || exit 0

run:
	 gcc -c graph.c
	 gcc -c main.c
	 gcc -o main graph.o main.o
	 ./main
