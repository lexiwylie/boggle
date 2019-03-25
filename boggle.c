#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "scanner.c"

char** createBoard(int M, int N) // allocates memory for big boggle and fills the board with cubes
{
  char *cube0[] = {"A", "A", "A", "F", "R", "S"};
  char *cube1[] = {"A", "A", "E", "E", "E", "E"};
  char *cube2[] = {"A", "A", "F", "I", "R", "S"};
  char *cube3[] = {"A", "Qu", "E", "N", "N", "N"};
  char *cube4[] = {"A", "E", "E", "E", "E", "M"};
  char *cube5[] = {"A", "E", "E", "G", "M", "U"};
  char *cube6[] = {"A", "E", "G", "M", "N", "N"};
  char *cube7[] = {"A", "F", "I", "R", "S", "Y"};
  char *cube8[] = {"B", "B", "J", "K", "X", "Z"};
  char *cube9[] = {"C", "C", "E", "N", "S", "T"};
  char *cube10[] = {"C", "E", "I", "I", "T", "T"};
  char *cube11[] = {"C", "E", "I", "L", "P", "T"};
  char *cube12[] = {"C", "E", "I", "P", "S", "T"};
  char *cube13[] = {"D", "D", "H", "N", "O", "T"};
  char *cube14[] = {"D", "H", "H", "L", "O", "R"};
  char *cube15[] = {"D", "H", "L", "N", "O", "R"};
  char *cube16[] = {"D", "H", "L", "N", "O", "R"};
  char *cube17[] = {"E", "I", "I", "L", "T", "T"};
  char *cube18[] = {"E", "M", "T", "T", "T", "O"};
  char *cube19[] = {"E", "N", "S", "S", "S", "U"};
  char *cube20[] = {"F", "I", "P", "R", "S", "Y"};
  char *cube21[] = {"G", "O", "R", "R", "V", "W"};
  char *cube22[] = {"I", "P", "R", "R", "Y", "Y"};
  char *cube23[] = {"N", "O", "O", "T", "U", "W"};
  char *cube24[] = {"O", "O", "O", "T", "T", "Qu"};

  char **cubes[] = {
                     cube0, cube1, cube2, cube3, cube4, cube5,
                     cube6, cube7, cube8, cube9, cube10, cube11,
                     cube12, cube13, cube14, cube15, cube16, cube17,
                     cube18, cube19, cube20, cube21, cube22, cube23,
                     cube24
                    };

  int i = 0;
  int j = 0;

  char** board = malloc(M * N * sizeof(char*));

  for(i = 0; i < M; i++)
  {
    for(j = 0; j < N; j++)
    {
      *(board + i*N + j) = cubes[j][i]; // REMOVE [i][j] and make random! rand() % len
    }
  }

  printf("\n");
  for(i = 0; i < M; i++)
  {
    for(j = 0; j < N; j++)
    {
      printf("%s ", *(board + i*N + j));
    }
    printf("\n");
  }
  printf("\n");

  /*for(i = 0; i < M; i++)
  {
    free(board[i]);
  }
  free(board); */

  return board;
}
