# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
OPTFLAGS = -O3

all	: tree
	@echo -n ""

# optimized version
tree			: tree_opt.o file_opt.o main_opt.o 
				$(CC) $(OPTFLAGS) tree_opt.o file_opt.o main_opt.o -o tree
main_opt.o 	   	: src/main.cpp src/file.h src/tree.h
				$(CC) $(CFLAGS) $< -o $@
file_opt.o		: src/file.cpp src/file.h src/tree.h
				$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@
tree_opt.o		: src/tree.cpp src/tree.h src/file.cpp
				$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@



# clean all the .o and executable files
clean:
		rm -rf *.o tree