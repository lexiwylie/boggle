#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define CHAR_SIZE 26

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

void insertWord(struct Trie *dictionaryTree, char word[], int count)
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

void freeNode(struct Trie* tree)
{
  for (int i = 0; i < CHAR_SIZE; i++)
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
