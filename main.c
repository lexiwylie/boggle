#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "boggle.c"

int main(void)
{
  int M = 0;
  int N = 0;
  int mode = 0;
  int numPlayers = 0;

  /*
  Modes:
  1 - Single Player
  2 - Multi Player
  3 - vs Computer
  */

  printf("Welcome to Boggle. If you haven't yet, read the document attached to _____.\n\n");
  printf("Select...")

  printf("\nThe board size can be M x N where M and N are both integers greater than or equal to 4.\n\n");

  while(M < 4)
  {
    printf("Enter your desired M, where M is a integer greater than or equal to 4: ");
    M = readInt(stdin);
  }

  while(N < 4)
  {
    printf("Enter your desired N, where N is a integer greater than or equal to 4: ");
    N = readInt(stdin);
  }

    printf("\nThe board size will be %d x %d with the board containing %d total cubes.\n", M, N, M*N);
    char** board = createBoard(M, N);

  return 0;
}
