#include "cache.h"



struct cache* cah__empty() {
  struct cache* cah = malloc(sizeof(struct cache));
  for (int i=0; i<TREE_DEPTH; i++) {
    cah->set[i] = lnk__empty();
  }
  return cah;
}

int cah__add_llm(struct cache* cah, int depth, struct lelement* llm) {
  lnk__add_head(cah->set[depth], llm);
  return 1;
}


// int cah__remove_llm(struct cache*, struct lelement*) {
//   return 1;
// }

// if (cah->head == NULL)
//   cah->head = llm;
// else {
//   struct lelement* cursor = cah->head;
//   while(cursor->next != NULL)
//     cursor = cursor->next;
//   cursor->next = llm;
// }0
