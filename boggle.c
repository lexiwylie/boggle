#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "scanner.c"

static int wordListSize = 0;
static char wordList[180000];
#define CHAR_SIZE 26
const int DX[] = {1, 0, -1, 1,  1,  0, -1, -1};
const int DY[] = {1, 1,  1, 0, -1, -1, -1,  0};

struct Trie
{
  int isLeaf; // isLeaf = 1 when the current node is a leaf node
  struct Trie *nextChar[CHAR_SIZE];
};

struct Trie *initializeNode()
{
  struct Trie *node = (struct Trie*)malloc(sizeof(struct Trie));
  node->isLeaf = 0;

  for(int i = 0; i < CHAR_SIZE; i++)
    node->nextChar[i] = NULL;

  return node;
}

void insertWord(struct Trie* dictionaryTree, char word[], int count)
{
	 if(strlen(word) == count)
   {
    dictionaryTree->isLeaf = 1;
    return;
   }

  int index = word[count] - 'a';

  if(dictionaryTree->nextChar[index] == NULL)
    dictionaryTree->nextChar[index] = initializeNode();

  insertWord(dictionaryTree->nextChar[index], word, count + 1);
}

char* createBoard(int M) // allocates memory for boggle and fills the board with cubes
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

  printf("\n\n");
  for(i = 0; i < M; i++)
  {
    for(j = 0; j < M; j++)
    {
      printf(" %c  ", toupper(*(board + i*M + j)));
    }
    printf("\n\n");
  }


  free(board);

  return board;
}

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
	  printf("\nThe board size can be M x M where M is an integer greater than or equal to 4.\n\n");

	  while(M < 4)
	  {
	    printf("Enter your desired M, where M is a integer greater than or equal to 4: ");
	    M = readInt(stdin);
	  }

	  printf("\nThe board size will be %d x %d with the board containing %d total cubes.\n\n", M, M, M*M);
	  return M;
	}

void resetVisits(int *visited, int M)
{
  for (int i = 0; i < M; i++)
    for (int j = 0; j < M; j++)
      *(visited + i*M + j) = 0;

  return;
}

int isInRange(int *visited, int i, int j, int M)
{
  if(i >= 0 && i < M && j >= 0 && j < M && *(visited + i*M + j) == 0)
    return 1;

  return 0;
}

void insertList(char word[])
{
  int count = 0;

  while(count < wordListSize)
  {
    if(strcmp(&wordList[count], word) == 0)
      return;

    count++;
  }

  printf("MATCH: %s\n", word);
  strcpy(&wordList[count], word);
  wordListSize++;
}

void searchWord(struct Trie *root, char *board, int *visited, char word[], int M, int i, int j)
{

  if(root->isLeaf == 1)
    insertList(word);

  if(isInRange(visited, i, j, M) == 1)
  {
    *(visited + i*M + j) = 1;

    for(int a = 0; a < 26; a++)
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
            searchWord(root->nextChar[a], board, visited, word, M, iNew, jNew);
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

  resetVisits(visited, M);

  struct Trie *root = dictionaryTree;

  char buildWord[30];
  memset(buildWord, '\0', 30);

  for(int i = 0; i < M; i++)
  {
    for(int j = 0; j < M; j++)
    {
      int index = *(board + i*M + j) - 'a';
      if(root->nextChar[index] != NULL)
      {
        strncat(buildWord, (board + i*M + j), 1);
        searchWord(root->nextChar[index], board, visited, buildWord, M, i, j);
        memset(buildWord, '\0', 30);
      }
    }
  }

  return;
}

void freeNode(struct Trie* tree)
{
  for (int i = 0; i < 26; i++)
		if (tree->nextChar[i] != NULL)
			freeNode(tree->nextChar[i]);

	free(tree);
}

void freeTrie(struct Trie* root)
{
  if (root != NULL) {
    struct Trie* tCurrent = root;
    freeNode(tCurrent);
  }
}
