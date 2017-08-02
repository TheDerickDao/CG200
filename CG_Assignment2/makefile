CC = gcc
CFLAGS = -lGL -lGLU -lglut
OBJ = Assignment2.o

UnderTheSea: $(OBJ)
	$(CC) $(OBJ) -o UnderTheSea $(CFLAGS)

Assignment2.o: Assignment2.c
	$(CC) -c Assignment2.c

clean:
	rm -f app $(OBJ)
