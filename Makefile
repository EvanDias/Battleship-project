OBJS=bitmap.o game.o list.o matrix.o menu.o randomShips.o ship.o initGame.o main.o
PROGRAM=./main
CFLAGS=-g 

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $(OBJS)
clean:
	rm -f $(PROGRAM) $(OBJS)
