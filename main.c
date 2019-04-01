#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "boggle.c"

int main(void)
{
  int M = 4; // board size
  int option = 0; // menu selection
  int settingsOption = 0; // settings selection
  int difficulty = 1;

  // -------- READ DICTIONARY INTO TRIE ---------

  struct Trie* dictionaryTree = initializeNode();
  FILE *fp = fopen("dictionary.txt", "r");
  char currentWord[50];

  while(fscanf(fp, "%s", currentWord) != EOF)
    insertWord(dictionaryTree, currentWord, 0);

  fclose(fp);

  // -------- FINISHED READING DICTIONARY --------

  while(1)
  {
    srandom((unsigned int)time(NULL)); // sets new random() seed everytime the user returns to the menu

    char* board; // points to board
    int *visited = (int *)malloc(M * M * sizeof(int)); // create 2D array of int given size M to keep track of letters visited

    int player = 0;

    printf("\n - - - - - - - - - -");
    printf("\n| WELCOME TO BOGGLE |\n");
    printf(" - - - - - - - - - -\n\n");

    /*

    -------------- SELECT MODE --------------
	    If the user fails to enter a valid option or doesn't
	    select "7 - EXIT GAME", the loop executes again.

    */

    printf("1 - PLAY\n");
    printf("2 - STATS\n");
    printf("3 - SETTINGS\n");
    printf("4 - EXIT GAME\n");
    while(option < 1 || option > 5)
    {
      printf("\nENTER OPTION #: ");
      option = readInt(stdin);
    }

    switch(option)
    {
      // PLAY AGAINST COMPUTER
      case 1:
        while(player < 1 || player > 4)
        {
          printf("\nWHO IS THE PLAYER? PLAYER # (1, 2, 3, 4, or 5): ");
          player = readInt(stdin); // read in # of current player
        }

        againstComputerMode(dictionaryTree, board, visited, M, difficulty, player);

        break;

      // STATS
      case 2:
        printStats();
        break;

      // SETTINGS
      case 3:
        settingsOption = 0;
        while(settingsOption < 1 || settingsOption > 2)
        {
          printf("\n\nSETTINGS\n\n");
          printf("1 - BOARD SIZE\n");
          printf("2 - DIFFICULTY\n\n");
          printf("\nENTER OPTION: ");
          settingsOption = readInt(stdin);
        }

        if(settingsOption == 1)
          M = setBoardSize();

        if(settingsOption == 2)
          difficulty = setDifficulty();

        break;

      // EXIT GAME
      case 4:
        exit(1);
        break;

      // DEFAULT (This case should never execute because of the while loop that reads in the user's option.)
      default:
        break;
    }
    option = 0; // resets selection
    settingsOption = 0; // resets selection

    free(visited);
  }

  freeTrie(dictionaryTree);
  return 0;
}
