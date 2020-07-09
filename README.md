# Battleship-project 

A project for university's subject Lab Programming(https://github.com/EvanDias/Battleship-project/blob/master/LabProgrammingProject.pdf). The goal is to do a game, BattleShip.
In this project, the data structure for the game board can be chosen. The structure can be a matrix or a quadtree. The project is modular because it allows to have functional modules.
Point c and d are not done.


## Compile and Run 

Compile choosing the data structure
Matrix 
```bash
make matrix
```
QuadTree
``bash
make quad
```
Run 
```bash
 ./main
```

Clean files .o 
```bash
make clean
```

##Files 
---src---
-bitmap.c: functions related to the struct bitmap, such as its initialization and changing the value of cells.
-board.c: contains several functions that serve for the graphical demonstration of each player's boards in the terminal.
-cell.c: several functions with the purpose of manipulating cells, being possible to modify all the values ​​attributed to it.
-ship.c: functions related to the definition of the ship, such as its creation, the calculation of the geometric transformations (rotations and translations) that it can undergo and the elimination of a ship.
-list.c: list implementation functions, such as creating and adding the node and adding nodes to the head of the list.
-matrix.c: functions related to the game board, such as its initialization, the insertion of elements in the matrix, their elimination.
-initGame.c: game start functions, such as creating users, calculating the number of boats that will be used by each player during the game. We also find the function that allows you to define who starts the game.
-game.c: functions related to the game, such as the shooting performed by the players (which will update the value and shot variables of the matrix cell and the value saved in the bitmap cell). With each shot, it checks whether the cell is a pointer for a ship or not, if so, it is determined whether that shot sinks the ship. A function has been implemented in which players can choose whether to define and position their ships manually, randomly or both.
-geral.c: the MATRIX and QUADTREE types and their respective these functions.
-randomShips.c: functions for creating points for translation, rotation and insertion in the game board, using the already existing function random () of language C. In these functions, after creation, ships undergo geometric changes with the value returned by random and also ships are inserted.
-menu.c: implemented the iteration between the terminal and the user, demonstrating iterative menus by choosing numbers, making it possible to start a game, view the rules and exit the game.
-quadtree.c: implementation of the quadtree data structure with all the functions necessary for its operation.
-point.c: contains functions to initialize, access, modify or remove a point.
-main.c: main function of the game.
---compile---
-make

##Input
As input initially, you must choose to start the game or see the rules of the game. If you choose to start the game, you are faced with the size of the board, which must be between 20 and 40. Then each player chooses his boats in turn. To see who starts the game, it is the one who chooses the largest number. Each chooses where to place their boats, depending on whether they want to random or choose for themselves.

##Observations 
A explicação de toda a elaboração do projeto está explicado no ficheiro: 
```bash
BatalhaNaval - Relatório.pdf(https://github.com/EvanDias/Battleship-project/blob/master/BatalhaNaval%20-%20Relat%C3%B3rio.pdf)
```
