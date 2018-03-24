all: Lexique

Lexique: o/Lexique.o o/arbreLexical.o
	gcc $^ -o $@
	@echo Compilation finie.

clean:
	rm -f Lexique o/Lexique.o o/arbreLexical.o

o/%.o: c/%.c
	gcc -o $@ -c -Wall -ansi $<