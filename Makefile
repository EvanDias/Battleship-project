quad: 
	gcc -D QUADTREE -o main *.c

matrix: 
	gcc -D MATRIX -o main *.c

clean:
	rm -f ./main
