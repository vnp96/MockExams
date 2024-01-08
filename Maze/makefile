exec: main.o maze.o
	g++ main.o maze.o -o exec

main.o: main.cpp
	g++ -c main.cpp -o main.o

maze.o: maze.cpp
	g++ -c maze.cpp -o maze.o

clean:
	rm -f *.o
	rm -f exec
