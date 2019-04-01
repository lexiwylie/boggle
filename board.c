#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "trie.c"
#define CHAR_SIZE 26

// possible adjacent X, Y coordinates on board
const int DX[] = {1, 0, -1, 1,  1,  0, -1, -1};
const int DY[] = {1, 1,  1, 0, -1, -1, -1,  0};

char **foundWords;
int *foundPoints;
int numFoundWords = 0;
int compScore = 0;

char *createBoard(int M) // allocates memory for boggle and fills the board with cubes
{
  char cube0[] = {"aaafrs"};
  char cube1[] = {"aaeeee"};
  char cube2[] = {"aafirs"};
  char cube3[] = {"aqennn"};
  char cube4[] = {"aeeeem"};
  char cube5[] = {"aeegmu"};
  char cube6[] = {"aegmnn"};
  char cube7[] = {"afirsy"};
  char cube8[] = {"bbjkxz"};
  char cube9[] = {"ccenst"};
  char cube10[] = {"ceiitt"};
  char cube11[] = {"ceilpt"};
  char cube12[] = {"ceipst"};
  char cube13[] = {"ddhnot"};
  char cube14[] = {"dhhlor"};
  char cube15[] = {"dhlnor"};
  char cube16[] = {"dhlnor"};
  char cube17[] = {"eilttt"};
  char cube18[] = {"emttto"};
  char cube19[] = {"ensssu"};
  char cube20[] = {"fiprsy"};
  char cube21[] = {"gorrvw"};
  char cube22[] = {"iprrry"};
  char cube23[] = {"nootuw"};
  char cube24[] = {"ooottq"};

  char *cubes[] = {
                     cube0, cube1, cube2, cube3, cube4, cube5,
                     cube6, cube7, cube8, cube9, cube10, cube11,
                     cube12, cube13, cube14, cube15, cube16, cube17,
                     cube18, cube19, cube20, cube21, cube22, cube23,
                     cube24
                    };

  int currentCube = 0;
  int currentSide = 0;
  int i = 0;
  int j = 0;

  char *board = (char *)malloc(M * M * sizeof(char));

  for(i = 0; i < M; i++)
  {
    for(j = 0; j < M; j++)
    {
      int currentCube = random() % 25;
      int currentSide = random() % 6;
      *(board + i*M + j) = cubes[currentCube][currentSide];
    }
  }

  return board;
}

void printBoard(char *board, int M)
{
  printf("\n\n");
  for(int i = 0; i < M; i++)
  {
    for(int j = 0; j < M; j++)
    {
      printf(" %c  ", toupper(*(board + i*M + j)));
    }
    printf("\n\n");
  }

  return;
}

void printList()
{
  printf("\nLIST OF POSSIBLE WORDS:\n\n");
  int count = 0;
  while(count < numFoundWords)
  {
    printf("WORD: %s - POINTS: %d\n", foundWords[count], foundPoints[count]);
    count++;
  }
}

void insertList(char word[])
{
  if(numFoundWords == 0)
  {
    word[strlen(word)] = '\0';
    strcpy(foundWords[0], word);
    numFoundWords++;
  }

  else
  {
    int count = 0;
    while(count < numFoundWords)
    {
      if(strcmp(foundWords[count], word) == 0)
        return;

      count++;
    }

    word[strlen(word)] = '\0';
    strcpy(foundWords[count], word);
    numFoundWords++;
  }

  return;
}

int compareLengths(const void *one, const void *two) {

  const char *iOne = *(const char * const *)one;
  const char *iTwo = *(const char * const *)two;
  size_t len1 = strlen(iOne);
  size_t len2 = strlen(iTwo);

  if (len1 > len2)
    return -1;

  if (len2 > len1)
    return +1;

  return strcmp(iOne, iTwo);
}

void sortListByLength()
{
  qsort(foundWords, numFoundWords, sizeof(char*), compareLengths);
  return;
}

void scorePoints()
{
  int count = 0;
  int len = 0;

  while(count < numFoundWords)
  {
    len = strlen(foundWords[count]);

    if(len == 3 || len == 4)
      foundPoints[count] = 1;

    else if(len == 5)
      foundPoints[count] = 2;

    else if(len == 6)
      foundPoints[count] = 3;

    else if(len == 7)
      foundPoints[count] = 5;

    else
      foundPoints[count] = 11;

    count++;
  }

  return;
}

int isInRange(int *visited, int i, int j, int M)
{
  if(i >= 0 && i < M && j >= 0 && j < M && *(visited + i*M + j) == 0)
    return 1;

  return 0;
}

void buildWord(struct Trie *root, char *board, int *visited, char word[], int M, int i, int j)
{

  if(root->isLeaf == 1 && strlen(word) >= 3)
    insertList(word);

  if(isInRange(visited, i, j, M) == 1)
  {
    *(visited + i*M + j) = 1;

    for(int a = 0; a < CHAR_SIZE; a++)
    {
      if(root->nextChar[a])
      {
        char ch = a + 'a';

        for(int b = 0; b < 8; b++)
        {
          int iNew = i + DX[b];
          int jNew = j + DY[b];

          if(isInRange(visited, iNew, jNew, M) == 1 && *(board + iNew*M + jNew) == ch)
          {
            strncat(word, &ch, 1);
            buildWord(root->nextChar[a], board, visited, word, M, iNew, jNew);
            word[strlen(word) - 1] = '\0';
          }
        }
      }
    }

    *(visited + i*M + j) = 0;
  }

  return;
}

void solveBoard(struct Trie *dictionaryTree, char *board, int *visited, int M)
{
  foundWords = malloc(180000 * sizeof(char *));
  for(int a = 0; a < 180000; a++)
    foundWords[a] = (char*)malloc(50);

  foundPoints = malloc(180000 * sizeof(int));

  struct Trie *root = dictionaryTree;

  char word[50];
  memset(word, '\0', 50);

  for(int i = 0; i < M; i++)
  {
    for(int j = 0; j < M; j++)
    {
      int index = *(board + i*M + j) - 'a';
      if(root->nextChar[index] != NULL)
      {
        strncat(word, (board + i*M + j), 1);
        buildWord(root->nextChar[index], board, visited, word, M, i, j);
        memset(word, '\0', 50);
      }
    }
  }

  return;
}

void resetVisits(int *visited, int M)
{
  for (int i = 0; i < M; i++)
    for (int j = 0; j < M; j++)
      *(visited + i*M + j) = 0;

  return;
}
