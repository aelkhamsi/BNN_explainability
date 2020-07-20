#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>


struct interval {
  float lower_bound;
  float upper_bound;
};

struct node {
  //data
  struct interval eq_interval;
  int variable_index;
  int version; //for the plot of the obdd
  //pt
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

int node__set_eq_interval(struct node*, float lower_bound, float upper_bound);

int node__set_variable_index(struct node*, int variable_index);

int node__add_rchild(struct node* parent, struct node* child);

int node__add_lchild(struct node* parent, struct node* child);


//FREE
int tree__free(struct tree*);

int node__free(struct node*);

#endif //TREE_H
