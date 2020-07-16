#include "list.h"


struct list* list__empty(void){
  struct list* l = malloc(sizeof(struct list));
  l->l = malloc(LIST_SIZE * sizeof(int));
  l->capacity = LIST_SIZE;
  l->size = 0;
  return l;
}


int list__is_empty(const struct list *l){
  return l->size == 0;
}


int list__add(struct list *l, int c){
  size_t i;
  //Check if the set is full (realloc in that case)
  if (l->size == l->capacity){
    l->l = realloc(l->l, l->capacity*2*sizeof(int));
    l->capacity *= 2;
  }

  l->l[l->size] = c;
  l->size += 1;
  return 1;
}


int list__size(const struct list* l){
  return l->size;
}


int list__find(const struct list* l, int c){
  size_t i;
  for (i=0; i<l->size; i++){
    if (l->l[i] == c) return 1;
  }
  return 0;
}


void list__free(struct list* l){
  free(l->l);
}
