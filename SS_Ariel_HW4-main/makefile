CC=gcc
OBJECTS_MAIN=main.o 
FLAGS= -Wall -g
EXE=graph

#target commands
all: $(EXE)
$(EXE): $(OBJECTS_MAIN) 
	$(CC) $(OBJECTS_MAIN) -o $(EXE)
main.o: main.c 
	$(CC) $(FLAGS) -c main.c 
	$(CC) $(FLAGS) -c brute.c 
.PHONY: clean all
clean:
	rm -f *.o *.a *.so $(EXE)