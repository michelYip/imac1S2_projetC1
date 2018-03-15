all: Lexique

Lexique: Lexique.o arbreLexical.o
	gcc $^ -o $@
	@echo Compilation finie.

clean:
	rm -f Lexique Lexique.o arbreLexical.o

%.o: %.c
	gcc -c -Wall -ansi $<