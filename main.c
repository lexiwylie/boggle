#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "boggle.c"
#include "menu.c"

int main(void)
{
  int M = 4; // board size
  int option = 0; // menu selection
  int settingsOption = 0; // settings selection

  int scores[10];
  int wins[10];
  int playerLoses[10];
  int playerTies[10];

  // -------- READ DICTIONARY INTO TRIE --------

  struct Trie* dictionaryTree = initializeNode();
  FILE *fp = fopen("dictionary.txt", "r");
  char currentWord[30];

  while(fscanf(fp, "%s", currentWord) != EOF)
    insertWord(dictionaryTree, currentWord, 0);

  fclose(fp);

  // -------- FINISHED READING DICTIONARY --------

  while(1)
  {
    srandom((unsigned int)time(NULL)); // sets new random() seed everytime the user returns to the menu

    char* board; // points to board
    int *visited = (int *)malloc(M * M * sizeof(int)); // create 2D array of int given size M to keep track of letters visited

    int difficulty = 0;
    int currentPlayer = 0;

    printf("\n\nWELCOME TO BOGGLE\n\n");

    /*

    -------------- SELECT MODE --------------
	    If the user fails to enter a valid option or doesn't
	    select "7 - EXIT GAME", the loop executes again.

    */

    printf("1 - PRACTICE\n");
    printf("2 - PLAY AGAINST LOCAL PLAYER\n");
    printf("3 - PLAY AGAINST COMPUTER\n");
    printf("4 - STATS\n");
    printf("5 - SETTINGS\n");
    printf("6 - RULES\n");
    printf("7 - EXIT GAME\n\n");
    while(option < 1 || option > 7)
    {
      printf("ENTER OPTION: ");
      option = readInt(stdin);
    }

    switch(option)
    {
      // PRACTICE
	    case 1:
        practiceMode(dictionaryTree, board, visited, M);

        //clean up
        free(board);
        resetVisits(visited, M);
        free(foundWords);
        numFoundWords = 0;

	      break;

      // PLAY AGAINST LOCAL PLAYER
      case 2:

        printf("Which player is playing? Player #: ");
	      currentPlayer = readInt(stdin); // read in # of current player

        board = createBoard(M); // creates new board of size M
        resetVisits(visited, M); // resets visits
        solveBoard(dictionaryTree, board, visited, M);
        free(board);

        break;

      // PLAY AGAINST COMPUTER
      case 3:
        board = createBoard(M); // creates new board of size M
        resetVisits(visited, M); // resets visits
        solveBoard(dictionaryTree, board, visited, M);
        free(board);

        break;

      // STATS
      case 4:
        printf("\n\nSTATS\n\n");
        break;

      // SETTINGS
      case 5:
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

      // RULES
      case 6:
        printRules();
        break;

      // EXIT GAME
      case 7:
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
