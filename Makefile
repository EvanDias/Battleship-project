quad: quadtreev2.c geral.c bitmap.c board.c cell.c game.c initGame.c list.c menu.c point.c randomShips.c ship.c main.c
	gcc -D QUADTREE -o main *.c

matrix: 
	gcc -D MATRIX -o main *.c

clean:
	rm -f ./main