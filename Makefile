output: shell.c
	g++ -Wall shell.c -o output

clean:
	rm *.o output