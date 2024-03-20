main: main.o
	g++ -o main main.o

clean:
	rm -f main main.o
