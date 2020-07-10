#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>


struct interval {
  int lower_bound;
  int upper_bound;
};

struct node {
  struct interval eq_interval;
  struct node* rchild;
  struct node* lchild;
};

struct tree {
  struct node* root;
};



//TREE
struct tree* tree__empty();

int tree__is_empty(const struct tree*);


//NODE
struct node* node__empty();

int node__set_eq_interval(struct node*, int lower_bound, int upper_bound);

int node__add_rchild(struct node* parent, struct node* child);

int node__add_lchild(struct node* parent, struct node* child);


//FREE
int tree__free(struct tree*);

int node__free(struct node*);

#endif //TREE_H
