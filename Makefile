output: shell.c
	gcc -Wall shell.c -o output

clean:
	rm *.o output