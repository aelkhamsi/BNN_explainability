#include "tree.h"
#include <assert.h>
#include <limits.h>

int test_tree__empty() {
  struct tree* tr = tree__empty();
  assert(tr->root == NULL);

  tree__free(tr);
  printf(". ");
  return 1;
}

int test_tree_is_empty() {
  //using tree__empty()
  struct tree* tr1 = tree__empty();
  assert(tree__is_empty(tr1));

  //without using tree__empty()
  struct tree tr2 = {NULL};
  assert(tree__is_empty(&tr2));

  tree__free(tr1);
  printf(". ");
  return 1;
}

int test_node__empty() {
  struct node* n = node__empty();
  assert(n->eq_interval.upper_bound == INT_MAX &&
         n->eq_interval.lower_bound == INT_MIN &&
         n->rchild == NULL &&
         n->lchild == NULL);

  node__free(n);
  printf(". ");
  return 1;
}

int test_node__set_eq_interval() {
  struct node* n = node__empty();
  assert(n->eq_interval.upper_bound == INT_MAX &&
         n->eq_interval.lower_bound == INT_MIN);

  node__set_eq_interval(n, 10, 20);
  assert(n->eq_interval.lower_bound == 10 &&
         n->eq_interval.upper_bound == 20);

  node__free(n);
  printf(". ");
  return 1;
}

int test_node__add_rchild() {
  struct node* parent = node__empty();
  struct node* rchild = node__empty();
  assert(node__add_rchild(parent, rchild));
  assert(parent->rchild == rchild && parent->lchild == NULL);

  node__free(parent);
  printf(". ");
  return 1;
}

int test_node__add_lchild() {
  struct node* parent = node__empty();
  struct node* lchild = node__empty();
  assert(node__add_lchild(parent, lchild));
  assert(parent->lchild == lchild && parent->rchild == NULL);

  node__free(parent);
  printf(". ");
  return 1;
}


int main() {
  test_tree__empty();
  test_tree_is_empty();
  test_node__empty();
  test_node__set_eq_interval();
  test_node__add_rchild();
  test_node__add_rchild();


  printf(" [");
  printf("\033[1;32m");
  printf("OK");
  printf("\033[0m");
  printf("]");

  printf("\n");
  return 0;
}
