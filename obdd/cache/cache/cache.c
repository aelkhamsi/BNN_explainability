#include "cache.h"



struct cache* cah__empty() {
  struct cache* cah = malloc(sizeof(struct cache));
  for (int i=0; i<TREE_DEPTH+1; i++) {
    cah->set[i] = lnk__empty();
  }
  return cah;
}


int cah__add_llm(struct cache* cah, int depth, struct lelement* llm) {
  lnk__add_head(cah->set[depth], llm);
  return 1;
}


int cah__store(struct cache* cah, int depth, struct node* node) {
  struct lelement* llm = llm__create(node, NULL);
  lnk__add_head(cah->set[depth], llm);
  return 1;
}


struct node* cah__find(struct cache* cah, int depth, int evidence_weight) {
  struct link* lnk = cah->set[depth];
  struct lelement* cursor = lnk->head;
  while (cursor->next != cursor && cursor->next != NULL) {
    struct node* node = cursor->pt;
    if (evidence_weight >= node->eq_interval.lower_bound && evidence_weight <= node->eq_interval.upper_bound)
      return node;
    cursor = cursor->next;
  }
  return NULL;
}


int cah__free(struct cache* cah) {
  for (int i=0; i<TREE_DEPTH+1; i++) {
    lnk__free(cah->set[i]);
  }
  return 1;
}
