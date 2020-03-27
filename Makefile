OBJS=game.o ship.o matrix.o list.o point.o menu.o main.o bitmap.o
PROGRAM=./main
CFLAGS=-g

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $(OBJS)
clean:
	rm -f $(PROGRAM) $(OBJS)
