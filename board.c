#include "initGame.h"

void printBoard(User *usr, int boardSize) {

    printf("\n");
    printf("  A ");

    char c1 = 'B';

   // void *structure = getStructure(usr);

    for(int i=1; i < boardSize; i++) {
        printf("%c ", c1);
        c1++;
        if(c1 == '[') c1 = 'a';
    }
    printf("\n");
    c1 = 'A';
    for(int i = 0; i < boardSize; i++) {
        printf("%c ", c1);
        c1++;
        if(c1 == '[') c1 = 'a';
        
        for(int j = 0; j < boardSize; j++) {
            Point *a = newPoint(i,j);
            void *aux = searchPoint(usr -> dataStructs, a);
            if(aux != NULL) {
                Cell *cell = (Cell*)aux; 
                printf("%c ", CELLVALUE(cell));                            
            }
            else {
                printf(". ");
            }
            free(a);
        }

    printf("\n");
    }

}

// Print letters around the game matrix
void letters(int size) {
    char c;

    printf("  A ");
    while(size != 0) {
        for(c = 'B'; c <= 'Z'; ++c) {
            if(size == 0) break;
            printf("%c ", c);
            size--;
        }

        if(size == 0) break;

        for(c = 'a'; c <= 'z'; ++c) {
            if(size == 0) break;
            printf("%c ", c);
            size--;
        }
    }
}


/*
 * User interface
 * Print current player matrix on left side
 * Print enemy matrix on right side
*/
void printBothBoard(User *start, User *other, int sizeBoard) {
    printf("\n");
    char c1 = 'A';
    int size = sizeBoard -1;
    letters(size);
    for(int i=0; i<10; i++) {
        printf(" ");
    }


    letters(size);
    printf("\n");

    for(int i=0; i < sizeBoard; i++) {

            printf("%c ", c1);
            if(c1 == '[') c1 = 'a';
            for(int j = 0; j < sizeBoard; j++) {
                Point *a = newPoint(i,j);
                void *aux = searchPoint(start -> dataStructs, a);
                if(aux != NULL) {
                    Cell *cell = (Cell*)aux; 
                    printf("%c ", CELLVALUE(cell));
                }

                else {
                    printf(". ");

                }
            
                free(a);
                
            }

            for(int z=0; z<10; z++) {
                printf(" ");
            }

            printf("%c ", c1);
            for(int j = 0; j < sizeBoard; j++) {
                Point *a = newPoint(i,j);
                void *aux = searchPoint(other -> dataStructs, a);
                 if(aux != NULL) {
                    Cell *cell = (Cell*)aux; 
                    if(CELLVALUE(cell) == 'x') printf(". ");   
                    else printf("%c ", CELLVALUE(cell));   

                 }
               else {
                    printf(". ");

                }
            
                free(a);
            }

            c1 += 1;
            printf("\n");
        }
    }



// To know if the position chosen by the user is uppercase or lowercase
int charToIntUpper(char chInput) {

    int inc = 0;

    char ch = 'A';

    while(true) {

        if(ch == chInput)
            return inc;

        ch++;
        inc++;
    }

    return inc;
}


// convert Character to int. Ex: (a b c d e ...) -> (0 1 2 3 4 ...)
int charToIntLower(char chInput) {

    int inc = 26;

    char ch = 'a';

    while(true) {

        if(ch == chInput)
            return inc;

        ch++;
        inc++;
    }

    return inc;
}

int choiceChar(char c) {
    int x;

    if(c >= 'A' && c <= 'Z')
        x = charToIntUpper(c);
    else
        x = charToIntLower(c);

    return x;
}
