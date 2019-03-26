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
  int numRounds = 0;
  int countRounds = 0;

  printf("Welcome to Boggle. If you haven't yet, read the document attached to _____.\n\n");

  /*

  -------------- SELECT MODE --------------
  If the user fails to enter an integer equal
  to either 1, 2, or 3, prompt the user again.

  */

  while(mode < 1 || mode > 3)
  {
  printf("Which mode would you like to play?\n");
  printf("1 - Single Player\n2 - Multi Player\n3 - Vs the Computer\n"); // Change wording of "Vs the Computer"
  printf("Select the number beside your desired mode: ");
  mode = readInt(stdin);
  }

  /*

  -------- SELECT NUMBER OF PLAYERS ---------
  If the user selects multiplayer mode, prompt
  the user to enter the number of players.

  */

  if(mode == 1)
  {
    numPlayers = 1;
  }

  if(mode == 2)
  {
    while(numPlayers < 2 || numPlayers > 8)
    {
      printf("\nHow many people are playing? Multiplayer must have a minimum of 2 players but no more than 8 players.\n");
      printf("Enter the number of players: ");
      numPlayers = readInt(stdin);
    }
  }

  if(mode == 3)
  {
    numPlayers = 2;
  }

  /*

  ------------- SELECT NUMBER OF ROUNDS -------------

  */

  printf("\nHow many rounds would you like to play?\n");
  printf("Enter the number of desired rounds: ");
  numRounds = readInt(stdin);

  /*

  ----------- SELECT BOARD DIMENSIONS ----------
  Just a note: The board size can only be set
  once and cannot be changed from round to round.

  */

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

  while(countRounds < numRounds)
  {
    char** board = createBoard(M, N);
    
    countRounds++;
  }

  return 0;
}
