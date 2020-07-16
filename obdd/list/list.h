#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

#define LIST_SIZE 10


struct list {
  float *l;
  size_t capacity;
  size_t size;
};


struct list* list__empty(void); //constuctor

int list__is_empty(const struct list *s);

int list__add(struct list*, float c); //effet de bord

int list__size(const struct list*);

int list__find(const struct list*, float c);


//free
void list__free(struct list*);



#endif //LIST_H
