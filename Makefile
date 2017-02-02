
#Indicates the compiler to be used
CC = g++

#Signifies compiler options
CFLAGS = -Wall -g
LFLAGS = -std=c++11


#File extentions .cpp, .o
SUFFIXES  = .cpp  .o
.SUFFIXES = $(SUFFIXES)	.

#Name of the program
PROG = fibHeapRun

# Object files .o necessary to build the main program
OBJS = fibonacciHeap.o hashTable.o

all: $(PROG)

#Compilation and link
$(PROG): $(OBJS) 
	$(CC)  $(CFLAGS) -o $(PROG) main.cpp $(OBJS) $(LFLAGS)
	
%.o: %.cpp
	$(CC)  $(CFLAGS) -c $< -o $@ $(LFLAGS) 
	
	
clean:
	rm -f $(PROG)
	rm -f *.o