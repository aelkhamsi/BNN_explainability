#include "cache.h"
#include <assert.h>



int test_cah__empty() {
  struct cache* cah = cah__empty();
  for (int i=0; i<TREE_DEPTH; i++) {
    assert(llm__is_end_mark(cah->set[i]->head));
  }

  cah__free(cah);
  printf(". ");
  return 1;
}


int test_cah__add_llm() {
  struct cache* cah = cah__empty();
  struct lelement* llm = malloc(sizeof(struct lelement));
  llm->pt = NULL;
  llm->next = NULL;
  assert(llm__is_end_mark(cah->set[0]->head));
  assert(cah__add_llm(cah, 0, llm));
  assert(cah->set[0]->head == llm);
  assert(llm__is_end_mark(cah->set[0]->head->next));

  cah__free(cah);
  printf(". ");
  return 1;
}

int test_cah__store() {
  struct cache* cah = cah__empty();
  struct node* node = node__empty();
  node__set_eq_interval(node, 10, 20);
  assert(cah__store(cah, TREE_DEPTH-1, node));
  assert(cah->set[TREE_DEPTH-1]->head->pt == node);
  assert(llm__is_end_mark(cah->set[TREE_DEPTH-1]->head->next));

  node__free(node);
  cah__free(cah);
  printf(". ");
  return 1;
}

int test_cah__find() {
  struct cache* cah = cah__empty();
  struct node* node = node__empty();
  node__set_eq_interval(node, 10, 20);
  cah__store(cah, TREE_DEPTH-1, node);
  assert(cah__find(cah, TREE_DEPTH-1, 15) == node);
  assert(cah__find(cah, TREE_DEPTH-1, 25) == NULL);

  node__free(node);
  cah__free(cah);
  printf(". ");
  return 1;
}


int main() {
  test_cah__empty();
  test_cah__add_llm();
  test_cah__store();
  test_cah__find();

  printf(" [");
  printf("\033[1;32m");
  printf("OK");
  printf("\033[0m");
  printf("]");

  printf("\n");
  return 0;
}
