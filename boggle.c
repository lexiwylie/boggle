#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "scanner.c"
#include "board.c"

char userWord[50];
char **userWords;
int numUserWords;
int userScore;
int *userWordPoints;

int scores[6] = {0, 0, 0, 0, 0, 0};
int wins[6] = {0, 0, 0, 0, 0, 0};
int losses[6] = {0, 0, 0, 0, 0, 0};
int ties[6] = {0, 0, 0, 0, 0, 0};


void practiceMode(struct Trie *dictionaryTree, char *board, int *visited, int M)
{
  board = createBoard(M); // creates new board of size M
  solveBoard(dictionaryTree, board, visited, M);
  sortListByLength();
  scorePoints();

  printf("\nPRACTICE MODE\n");
  printf("\nYou have three minutes to find words. Enter q to quit early. Go!\n");
  printBoard(board, M);

  userWords = malloc(1000 * sizeof(char *));
  for(int i = 0; i < 1000; i++)
    userWords[i] = (char *)malloc(50);

  userWordPoints = malloc(1000 * sizeof(int));

  scanf("%s", userWord);
  userWord[strlen(userWord)] = '\0';
  int count = 0;
  int isDup = 0;

  unsigned int timeP = time(0) + 180;

  while(strcmp(userWord, "q") != 0)
  {
    count = 0;
    while(count < numFoundWords)
    {
      if(strcmp(foundWords[count], userWord) == 0)
      {
        for(int i = 0; i < numUserWords; i++)
        {
          if(strcmp(userWords[i], userWord)) // check if word has already been found
            isDup = 1;
        }

        if(isDup != 1)
        {
          strcpy(userWords[numUserWords], foundWords[count]);
          userWordPoints[numUserWords] = foundPoints[count];
          userScore += foundPoints[count];
          numUserWords++;
        }
      }
      count++;
    }
    if (time(0) > timeP) break;
    scanf("%s", userWord);
    userWord[strlen(userWord)] = '\0';
  }

  printf("\nYOU FOUND THE FOLLOWING WORDS:\n\n");

  count = 0;
  while(count < numUserWords)
  {
    printf("%s - %d POINTS\n", userWords[count], userWordPoints[count]);
    count++;
  }
  printf("\nFOR A TOTAL OF %d POINTS\n\n", userScore);

  resetVisits(visited, M);
  free(board);
  for(int a = 0; a < 180000; a++)
    free(foundWords[a]);
  free(foundWords);
  free(foundPoints);
  numFoundWords = 0;
  compScore = 0;

  memset(userWord, '\0', 50);
  free(userWords);
  numUserWords = 0;
  userScore = 0;

  return;
}

void againstComputerMode(struct Trie *dictionaryTree, char *board, int *visited, int M, int diff, int p)
{
  printf("%d\n", diff);
  board = createBoard(M); // creates new board of size M
  solveBoard(dictionaryTree, board, visited, M);
  sortListByLength();
  scorePoints();

  printf("\nAGAINST COMPUTER MODE\n");
  printf("\nYou have three minutes to find words. Enter q to quit early. Go!\n");
  printBoard(board, M);

  userWords = malloc(1000 * sizeof(char *));
  for(int i = 0; i < 1000; i++)
    userWords[i] = (char *)malloc(50);

  userWordPoints = malloc(1000 * sizeof(int));

  scanf("%s", userWord);
  int count = 0;
  int isDup = 0;

  while (strcmp(userWord, "q") != 0)
  {
    count = 0;
    while(count < numFoundWords)
    {
      if(strcmp(foundWords[count], userWord) == 0)
      {
        for(int i = 0; i < numUserWords; i++)
        {
          if(strcmp(userWords[i], userWord)) // check if word has already been found
            isDup = -1;
        }

        if(isDup != -1)
        {
          strcpy(userWords[numUserWords], foundWords[count]);
          userWordPoints[numUserWords] = foundPoints[count];
          userScore += foundPoints[count];
          numUserWords++;
        }
      }
      count++;
    }
    scanf("%s", userWord);
  }

  printf("\nYOU FOUND THE FOLLOWING WORDS:\n\n");

  count = 0;
  while(count < numUserWords)
  {
    printf("%s - %d POINTS\n", userWords[count], userWordPoints[count]);
    count++;
  }
  printf("\nFOR A TOTAL OF %d POINTS\n\n", userScore);

  int chance = (random() % 3) - 1;

  // EASY
  if(diff == 1)
  {
    printf("\nTHE COMPUTER FOUND THE FOLLOWING WORDS:\n\n");

    count = 0;
    while(count + chance < numUserWords)
    {
      printf("%s - %d POINTS\n", foundWords[numFoundWords - count - 1], foundPoints[numFoundWords - count - 1]);
      compScore += foundPoints[numFoundWords - count - 1];
      count++;
    }
    printf("\nFOR A TOTAL OF %d POINTS\n", compScore);
  }

  // MEDIUM
  else if(diff == 2)
  {
    printf("\nTHE COMPUTER FOUND THE FOLLOWING WORDS:\n\n");

    count = 0;
    while(count + chance < numUserWords)
    {
      int ranIndex = random() % numFoundWords;
      printf("%s - %d POINTS\n", foundWords[ranIndex], foundPoints[ranIndex]);
      compScore += foundPoints[ranIndex];
      count++;
    }
    printf("\nFOR A TOTAL OF %d POINTS\n", compScore);
  }

  // HARD
  else if(diff == 3)
  {
    printf("\nTHE COMPUTER FOUND THE FOLLOWING WORDS:\n\n");

    count = 0;
    while(count + chance < numUserWords)
    {
      printf("%s - %d POINTS\n", foundWords[count], foundPoints[count]);
      compScore += foundPoints[count];
      count++;
    }
    printf("\nFOR A TOTAL OF %d POINTS\n", compScore);
  }

  scores[p] += userScore;
  if(userScore > compScore)
  {
    wins[p]++;
    losses[5]++;
  }

  else if(userScore == compScore)
  {
    ties[p]++;
    ties[5]++;
  }

  else if(userScore < compScore)
  {
    wins[5]++;
    losses[p]++;
  }

  resetVisits(visited, M);
  free(board);
  for(int a = 0; a < 180000; a++)
    free(foundWords[a]);
  free(foundWords);
  free(foundPoints);
  numFoundWords = 0;
  compScore = 0;

  memset(userWord, '\0', 50);
  free(userWords);
  numUserWords = 0;
  userScore = 0;

  return;
}

void printStats()
{
  printf("\n\nSTATS\n\n");

  printf("PLAYER 1\n");
  printf("TOTAL POINTS: %d\n", scores[0]);
  printf("WINS: %d\n", wins[0]);
  printf("LOSSES: %d\n", losses[0]);
  printf("TIES: %d\n\n", ties[0]);

  printf("PLAYER 2\n");
  printf("TOTAL POINTS: %d\n", scores[1]);
  printf("WINS: %d\n", wins[1]);
  printf("LOSSES: %d\n", losses[1]);
  printf("TIES: %d\n\n", ties[1]);

  printf("PLAYER 3\n");
  printf("TOTAL POINTS: %d\n", scores[2]);
  printf("WINS: %d\n", wins[2]);
  printf("LOSSES: %d\n", losses[2]);
  printf("TIES: %d\n\n", ties[2]);

  printf("PLAYER 4\n");
  printf("TOTAL POINTS: %d\n", scores[3]);
  printf("WINS: %d\n", wins[3]);
  printf("LOSSES: %d\n", losses[3]);
  printf("TIES: %d\n\n", ties[3]);

  printf("PLAYER 5\n");
  printf("TOTAL POINTS: %d\n", scores[4]);
  printf("WINS: %d\n", wins[4]);
  printf("LOSSES: %d\n", losses[4]);
  printf("TIES: %d\n\n", ties[4]);

  printf("COMPUTER\n");
  printf("TOTAL POINTS: %d\n", scores[5]);
  printf("WINS: %d\n", wins[5]);
  printf("LOSSES: %d\n", losses[5]);
  printf("TIES: %d\n\n", ties[5]);
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
