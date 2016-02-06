Name: Andrew Lawrence
Student ID: 1295565
Unix ID: adlawren
Lecture Section: EB1
Instructor: Evandro De Souza
Lab Section: EH01

The project is formatted according to the following directory structure:

- inc/
- obj/
- src/

The inc/ directory contains the following header files:

- list.h
  Contains the definition of an integer linked list, along with supporting functions.
- main.h
  Contains the high-level application code; the entry point of the program.
- mergesort.h
  Conatins the definition of the merge sort implementation.
- tests.h
  Contains the definition of a function used to implement unit tests for the merge sort implementation, along with the definition of a function containing several implementations of test cases.
- utilities.h
  Contains various supporting functions used by the application.

The src/ directory contains the following source files, which contain the defintions of the functions described above respectively:

- list.c
- main.c
- mergesort.c
- tests.c
- utilities.c

The obj/ directory contains object files produced by the compiler.

The project may be built by issuing the following commands:

>make clean
>make
