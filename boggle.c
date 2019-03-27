#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "scanner.c"

struct Trie
{
  int isEndOfWord; // isLeaf = 1 when the current node is a leaf node
  struct Trie *nextChar[26];
};

char** createBoard(int M) // allocates memory for big boggle and fills the board with cubes
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

  int currentCube = 0;
  int currentSide = 0;
  int i = 0;
  int j = 0;

  char** board = malloc(M * M * sizeof(char*));

  for(i = 0; i < M; i++)
  {
    for(j = 0; j < M; j++)
    {
      int currentCube = random() % 25;
      int currentSide = random() % 6;
      *(board + i*M + j) = cubes[currentCube][currentSide];
    }
  }

  printf("\n");
  for(i = 0; i < M; i++)
  {
    for(j = 0; j < M; j++)
    {
      printf("%s ", *(board + i*M + j));
    }
    printf("\n");
  }
  printf("\n");


  free(board);

  return board;
}

struct Trie* initializeNode()
{
  struct Trie* node = malloc(sizeof(struct Trie));
  node->isEndOfWord = 0;

  int i = 0;
  for(i = 0; i < 26; i++)
  {
    node->nextChar[i] = NULL;
  }

  return node;
}

void insertWord(struct Trie* dictionaryTree, char word[])
	{
	  int i = 0;
	  int index = 0;

	  for(i = 0; i < strlen(word); i++)
	  {
	    int index = word[i] - 'a';

	    if(dictionaryTree->nextChar[index] == NULL)
	      dictionaryTree->nextChar[index] = initializeNode();

	    dictionaryTree = dictionaryTree->nextChar[index];
	  }
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

	/*void freeDictionary(struct Trie* tree) {

		int i;
		for (i=0; i<26; i++)
			if (tree->nextChar[i] != NULL)
				freeDictionary(tree->nextChar[i]);

		free(tree);
	}*/
