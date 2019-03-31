#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void printRules()
{
	printf("\n\nPRINT RULES HERE\n\n");
}

int setDifficulty()
{
  int difficulty = 0;
  printf("\n\nDIFFICULTY\n\n");
  printf("1 - EASY\n");
  printf("2 - MEDIUM\n");
  printf("3 - HARD\n\n");

  printf("Which difficulty would you like?: ");
  difficulty = readInt(stdin);
  return difficulty;
}

int setBoardSize()
{
  int M = 0;
  printf("\n\nBOARD SIZE\n\n");
  printf("\nThe board size can be M x M where M is an integer greater than or equal to 4.\n");

  while(M < 4)
  {
    printf("Enter your desired M, where M is a integer greater than or equal to 4: ");
    M = readInt(stdin);
  }

  printf("\nThe board size will be %d x %d with the board containing %d total cubes.\n\n", M, M, M*M);
  return M;
}
