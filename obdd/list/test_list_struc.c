#include "list.h"
#include <assert.h>


int test_list__empty() {
  struct list* l = list__empty();
  assert(l->l != NULL && l->capacity == LIST_SIZE && l->size == 0);

  list__free(l);
  printf(". ");
  return 1;
}

int test_list__is_empty() {
  struct list* l = list__empty();
  assert(list__is_empty(l));

  list__free(l);
  printf(". ");
  return 1;
}

int test_list__add() {
  struct list* l = list__empty();
  assert(list__add(l, 0));
  assert(l->size == 1 && l->l[0] == 0);

  for (int i=1; i<LIST_SIZE+1; i++) {
    list__add(l, i);
  }
  assert(l->capacity == 2*LIST_SIZE);
  assert(l->size == LIST_SIZE+1);

  list__free(l);
  printf(". ");
  return 1;
}

int test_list__size() {
  struct list* l = list__empty();
  assert(list__size(l) == 0);

  list__add(l, 0);
  assert(list__size(l) == 1);

  for (int i=1; i<LIST_SIZE; i++) {
    list__add(l, i);
  }
  assert(list__size(l) == LIST_SIZE);

  list__free(l);
  printf(". ");
  return 1;
}

int test_list__find() {
  struct list* l = list__empty();
  assert(list__find(l, 0) == 0);

  list__add(l, 0);
  assert(list__find(l, 0) == 1);

  list__free(l);
  printf(". ");
  return 1;
}


int main(){
  test_list__empty();
  test_list__is_empty();
  test_list__add();
  test_list__size();
  test_list__find();

  printf(" [");
  printf("\033[1;32m");
  printf("OK");
  printf("\033[0m");
  printf("]");

  printf("\n");
  return 0;
}
