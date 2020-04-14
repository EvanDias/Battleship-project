OBJS=gamev2.o shipv2.o matrix.o list.o menu.o bitmap.o main.o
PROGRAM=./main
CFLAGS=-g

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $(OBJS)
clean:
	rm -f $(PROGRAM) $(OBJS)
