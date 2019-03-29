#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "boggle.c"

int main(void)
{
  int players[50];
	int option = 0;
	int M = 4;
	int difficulty = 0;

  // -------- READ DICTIONARY INTO TRIE --------

  struct Trie* dictionaryTree = initializeNode();
  FILE *fp = fopen("testdict.txt", "r");
  char currentWord[30];

  while(fscanf(fp, "%s", currentWord) != EOF)
    insertWord(dictionaryTree, currentWord, 0);

  fclose(fp);

  // -------- FINISHED READING DICTIONARY --------

  char* board = createBoard(M);

  int *visited = (int *)malloc(M * (M+1) * sizeof(int));
  resetVisits(visited, M);

  while(option != 7)
  {
    srandom((unsigned int)time(NULL)); // sets new random() seed everytime the user returns to the menu

    int currentPlayer = 0;
    int numPlayers = 0;
    printf("\n\nWELCOME TO BOGGLE\n\n");

    /*

    -------------- SELECT MODE --------------
	    If the user fails to enter a valid option or doesn't
	    select "7 - EXIT GAME", the loop executes again.

    */

    printf("1 - PLAY SINGLE PLAYER\n");
    printf("2 - PLAY MULTIPLAYER\n"); // Change wording of "Vs the Computer"
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
      int settingsOption = 0;

      // SINGLE PLAYER
	      case 1:
          printf("Which player is playing? Player #: ");
	        currentPlayer = readInt(stdin);
          solveBoard(dictionaryTree, board, visited, M);
	        break;

      // MULTIPLAYER
      case 2:
        while(numPlayers < 2 || numPlayers > 8)
        {
          printf("\nHow many people are playing? Multiplayer must have a minimum of 2 players but no more than 8 players.\n");
          printf("Enter the number of players: ");
          numPlayers = readInt(stdin);
        }

        break;

      // AGAINST COMPUTER
      case 3:
        break;

      // STATS
      case 4:
        break;

      // SETTINGS
      case 5:
        while(settingsOption < 1 || settingsOption > 2)
        {
          printf("\n\nSETTINGS\n\n");
          printf("1 - BOARD SIZE\n");
          printf("2 - DIFFICULTY\n\n");
          printf("ENTER OPTION: ");
          settingsOption = readInt(stdin);
        }

        if(settingsOption == 1)
          setBoardSize();

        if(settingsOption == 2)
          setDifficulty();

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
    option = 0;
  }

  free(board);
  freeDictionary(dictionaryTree);

  return 0;
}
