#ifndef CAHCE_H
#define CACHE_H

#include <stdlib.h>
#include <stdio.h>
#include <link.h>

#define TREE_DEPTH 7


struct cache {
  struct link* set[TREE_DEPTH];
};


struct cache* cah__empty();

int cah__add_llm(struct cache*, int depth, struct lelement*);



int cah__free(struct cache*);

#endif
