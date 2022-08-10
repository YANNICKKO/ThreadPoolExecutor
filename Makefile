build:
	gcc -std=c99 -o tema2 functiiCoada-L.c functiiStiva-L.c functions.c print_functions.c tema2.c

run:
	./tema2	

clean:
	rm -f *.o tema2
