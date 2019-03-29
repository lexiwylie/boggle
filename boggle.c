#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "scanner.c"

const int DX[] = { 0, -1, -1, -1, 1, 1, 1, 0 };
const int DY[] = { 1, 0, 1, 1, -1, 0, -1, -1 };

struct Trie
{
  int isLeaf; // isLeaf = 1 when the current node is a leaf node
  struct Trie *nextChar[26];
};

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

struct Trie* initializeNode()
{
  struct Trie* node = malloc(sizeof(struct Trie));
  node->isLeaf = 0;

  int i = 0;
  for(i = 0; i < 26; i++)
  {
    node->nextChar[i] = NULL;
  }

  return node;
}

void freeDictionary(struct Trie* tree)
{
  int i = 0;
  for(i=0; i<26; i++)
  {
    if (tree->nextChar[i] != NULL)
      freeDictionary(tree->nextChar[i]);
  }

  free(tree);
}

void insertWord(struct Trie* dictionaryTree, char word[], int count)
	{
	  if(strlen(word) == count)
    {
      dictionaryTree->isLeaf = 1;
      return;
    }

    int index = word[count] - 'a';

    if(!dictionaryTree->nextChar[index])
      dictionaryTree->nextChar[index] = initializeNode();

    insertWord(dictionaryTree->nextChar[index], word, count + 1);
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

int isInRange(int X, int Y, int *visited, int M)
{
  if(X >= 0 && X < M && Y >= 0 && Y < M && *(visited + X*M + Y) == 0)
    return 1;

  return 0;
}

void searchDictionary(struct Trie *root, char *board, int *visited, char word[], int M, int currX, int currY, int index)
{
  int i = 0;
  word[index] = '\0';

  printf("2\n");
  if(root->isLeaf == 1)
    printf("MATCH: %s\n", word);

  printf("3\n");

  for(i = 0; i < 8; i++)
  {
    int newX = currX + DX[i];
    int newY = currY + DY[i];

    if(isInRange(currX, currY, visited, M) == 1)
    {
      *(visited + currX*M + currY) = 1;
      word[index] = *(board + currX*M + currY);
      printf("4\n");

      int nextIndex = word[index] - 'a';
      printf("5\n");

      if(root->nextChar[nextIndex] != NULL)
        searchDictionary(root->nextChar[nextIndex], board, visited, word, M, newX, newY, index + 1);
    }
  }

  *(visited + currX*M + currY) = 0;

  return;
}

void solveBoard(struct Trie *root, char *board, int *visited, int M)
{

  int i = 0;
  int j = 0;
  int index = 0;
  char buildWord[30] = "";

  for(i = 0; i < M; i++)
  {
    for(j = 0; j < M; j++)
    {
      int k = 0;
      resetVisits(visited, M);
      strcpy(buildWord, "");

      buildWord[k] = *(board + i*M + j);
      printf("1\n");
      searchDictionary(root, board, visited, buildWord, M, i, j, index);
    }
  }

  return;
}
	/*void freeDictionary(struct Trie* tree) {

		int i;
		for (i=0; i<26; i++)
			if (tree->nextChar[i] != NULL)
				freeDictionary(tree->nextChar[i]);

		free(tree);
	}*/
