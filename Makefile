OBJS=bitmap.o gamev2.o list.o matrix.o menu.o randomShips.o shipv2.o main.o
PROGRAM=./main
CFLAGS=-g

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $(OBJS)
clean:
	rm -f $(PROGRAM) $(OBJS)
