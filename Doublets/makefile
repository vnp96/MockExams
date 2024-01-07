exec: main.o doublets.o dictionary.h
	g++ main.o doublets.o -o exec

main.o: main.cpp
	g++ -c main.cpp -o main.o

doublets.o: doublets.cpp
	g++ -c doublets.cpp -o doublets.o

clean:
	rm -f *.o
	rm -f exec
	rm -f chain.txt
