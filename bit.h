/*
- We can think of a library as a collection of books.
Each book is a function that can be read by anyone who has access to the library.
Static libraries help keep programs clean and concise for humans but they do have some
drawbacks, which we will touch on later.

- How they work:
Static libraries, also called “archives”, are just collections of object files that
contain functions. All the functions within the library are organized and indexed with 
a symbol and address, kind of like a table of contents, which makes it easier to find
what you’re looking for.
Static libraries are joined to the main module of a program during the linking stage
of compilation before creating the executable file. After a successful link of a static
library to the main module of a program, the executable file will contain both the main
program and the library.

- How to create them:
Static libraries are created using some type of archiving software, such as ar. 
ar takes one or more object files (that end in .o), zips them up, and generates an 
archive file (ends in .a) — This is our “static library”.
- Before using ar, we must first have some object files to give to it. 
Perhaps we’ve written some functions in C that we want to include in our library. 
We can use the -c option with the GNU compiler (gcc) to stop the compiling process 
after the assembling stage, translating our files from .c to .o.

$ gcc -c bitString.c checkEndianness.c crc.c gettersAndSetters.c
$ ar -rc libst.a bitString.o checkEndianness.o crc.o gettersAndSetters.o
$ gcc main.c -L. -lst -o main

- Let’s break that down:
	-L says “look in directory for library files”
	.(the dot after ‘L’) represents the current working directory
	-l says “link with this library file”
	st is the name of our library. Note that we omitted the “lib” prefix and “.a” 
	extension. The linker attaches these parts back to the name of the library to 
	create a name of a file to look for.
	-o main says “name the executable file main

*/

/*
USING CMake:
	$ cmake -S . -B build/
	$ cd build
	$ make

*/

#include "helpers.h"

/* bitString.c */

uint8_t *ft_16bit2string(uint16_t);
uint8_t *ft_32bit2string(uint32_t);
uint8_t *ft_64bit2string(uint64_t);

/* checkEndianness.c */

void checkEndianness(void);

/* crc.c */

void crc_gen(uint8_t *, int, uint8_t **, uint8_t);

/* gettersAndSetters.c */

uint8_t ft_getbit(uint8_t *, int );
void ft_setbit(uint8_t *, int, uint8_t);
void ft_togglebit(uint8_t *, int);
void ft_cpybit(uint8_t *, uint8_t, uint8_t *, uint8_t, int);

