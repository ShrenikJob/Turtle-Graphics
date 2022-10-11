CC = gcc
CFLAGS = -Wall -pedantic -ansi -g 
OBJ1 = Turtle.o effects.o linkedList.o
OBJ2 = TurtleS.o effects.o linkedList.o
EXEC1 = TurtleGraphics
EXEC2 = TurtleGraphicsSimple


$(EXEC1) : $(OBJ1)
	$(CC) $(CFLAGS) $(OBJ1) -o $(EXEC1) -lm

$(EXEC2) : $(OBJ2)
	$(CC) $(CGLAGS) $(OBJ2) -o $(EXEC2) -lm
 
TurtleS.o : Turtle.h effects.h linkedList.h struct.h 
	$(CC) -c Turtle.c $(CFLAGS) -D SimpleGraphics -o TurtleS.o

Turtle.o : Turtle.h effects.h linkedList.h struct.h
	$(CC) -c Turtle.c $(CFLAGS)

effects.o : effects.h Turtle.h
	$(CC) -c effects.c $(CFLAGS)

linkedList.o : linkedList.h Turtle.h struct.h
	$(CC) -c linkedList.c $(CFLAGS)

clean:
	rm -f $(EXEC1) $(EXEC2) $(OBJ1) $(OBJ2)	 
