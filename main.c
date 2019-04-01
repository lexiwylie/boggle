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

  // -------- READ DICTIONARY INTO TRIE --------

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

    printf("\n\nWELCOME TO BOGGLE\n\n");

    /*

    -------------- SELECT MODE --------------
	    If the user fails to enter a valid option or doesn't
	    select "7 - EXIT GAME", the loop executes again.

    */

    printf("1 - PRACTICE\n");
    printf("2 - PLAY AGAINST COMPUTER\n");
    printf("3 - STATS\n");
    printf("4 - SETTINGS\n");
    printf("5 - EXIT GAME\n");
    while(option < 1 || option > 5)
    {
      printf("ENTER OPTION: ");
      option = readInt(stdin);
    }

    switch(option)
    {
      // PRACTICE (SINGLE PLAYER)
	    case 1:
        practiceMode(dictionaryTree, board, visited, M);
	      break;

      // PLAY AGAINST COMPUTER
      case 2:
        while(player < 1 || player > 5)
        {
          printf("Who is the  player? Player # (1, 2, 3, 4, or 5): ");
          player = readInt(stdin); // read in # of current player
        }

        againstComputerMode(dictionaryTree, board, visited, M, difficulty, player);

        break;

      // STATS
      case 3:
        printStats();
        break;

      // SETTINGS
      case 4:
        settingsOption = 0;
        while(settingsOption < 1 || settingsOption > 2)
        {
          printf("\n\nSETTINGS\n\n");
          printf("1 - BOARD SIZE\n");
          printf("2 - DIFFICULTY\n\n");
          printf("ENTER OPTION: ");
          settingsOption = readInt(stdin);
        }

        if(settingsOption == 1)
          M = setBoardSize();

        if(settingsOption == 2)
          difficulty = setDifficulty();

        break;

      // EXIT GAME
      case 5:
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
