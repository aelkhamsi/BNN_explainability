#ifndef CAHCE_H
#define CACHE_H

#include <stdlib.h>
#include <stdio.h>
#include <link.h>
#include <tree.h>

#define TREE_DEPTH 5


struct cache {
  struct link* set[TREE_DEPTH+1];
};


struct cache* cah__empty();

int cah__add_llm(struct cache*, int depth, struct lelement*);

int cah__store(struct cache*, int depth, struct node*);

struct node* cah__find(struct cache*, int depth, int evidence_weight);  //struct node* or NULL


//FREE
int cah__free(struct cache*);

#endif
