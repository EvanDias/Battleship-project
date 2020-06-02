#include "geral.h"


typedef struct user_ User;

#define USERNAME(U) (U -> username)
#define SETUSERNAME(U,n) (U -> username = n)
#define USERLIST(U) (U -> shipList)
#define SETUSERLIST(U, l) (U -> shipList = l)
#define USERSTRUCTURE(U) (U -> dataStructs)
#define SETUSERSTRUCTURE(U,s) (U -> dataStructs = s)

struct user_ {

  char *username;
  List *shipList;

  void *dataStructs;
};

User *initUser(char *username, int sizeBoard);
int chooseBoardSize();
User *whoStartGame(User *usr1, User *usr2);
void printUsers(User *start, User *other,int boardSize);
//void freeUser(User *usr);
