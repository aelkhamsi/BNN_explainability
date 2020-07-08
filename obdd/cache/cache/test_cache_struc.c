#include "cache.h"
#include <assert.h>



int test_cah__empty() {
  struct cache* cah = cah__empty();
  for (int i=0; i<TREE_DEPTH; i++) {
    assert(llm__is_end_mark(cah->set[i]->head));
  }

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

  printf(". ");
  return 1;
}


int main() {
  test_cah__empty();
  test_cah__add_llm();

  printf(" [");
  printf("\033[1;32m");
  printf("OK");
  printf("\033[0m");
  printf("]");

  printf("\n");
  return 0;
}
