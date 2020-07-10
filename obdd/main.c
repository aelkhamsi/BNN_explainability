#include "tree.h"
#include "cache.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//GLOBAL VARIABLES
float weights[] = {1, -1, -1, 1, 1};
int bias = 1;
//////////////////


//AUXILIARY FUNCTIONS
struct interval offset(struct interval interval, int offset) {
  struct interval new_interval = {INT_MIN, INT_MAX};
  if (interval.lower_bound != INT_MIN)
    new_interval.lower_bound = interval.lower_bound + offset;
  if (interval.upper_bound != INT_MAX)
    new_interval.upper_bound = interval.upper_bound + offset;
  return new_interval;
}

float sum(float weights[]) {
  float sum = 0;
  for (int i=0; i<TREE_DEPTH; i++) {
    sum += weights[i];
  }
  return sum;
}

struct interval conjunction(struct interval interval1, struct interval interval2) {
  int lower_bound = interval1.lower_bound < interval2.lower_bound ? interval2.lower_bound : interval1.lower_bound;
  int upper_bound = interval1.upper_bound < interval2.upper_bound ? interval1.upper_bound : interval2.upper_bound;
  struct interval conj_int = {lower_bound, upper_bound};
  return conj_int;
}
/////////////////////


//MAIN
struct node* build_sub_odd(int depth, float plo, struct cache* cah) {  //plo == prior_log_odds
  struct node* node = node__empty();
  node__set_eq_interval(node, INT_MIN, INT_MAX);

  for (int e=0; e<=1; e++) {  //every value ek+1 of Ek+1
    float weight_child = 1/2 * (e ? weights[depth] : -1*weights[depth]);
    float plo_child = plo + weight_child;
    //searching for child node in cache
    struct node* child = cah__find(cah, depth+1, plo_child);
    if (child == NULL) {
      child = build_sub_odd(depth+1, plo_child, cah);
    }
    //add_child
    e ? node__add_rchild(node, child): node__add_lchild(node, child);
    //update eq_interval
    node->eq_interval = conjunction(node->eq_interval, offset(child->eq_interval, -1*weight_child));
  }

  cah__store(cah, depth, node);
  return node;
}

struct node* build_odd(float weights[], float bias, struct cache* cah) {  //log_odds threshold == 0
  struct node* one_sink = node__empty();
  node__set_eq_interval(one_sink, 0, INT_MAX);
  cah__store(cah, TREE_DEPTH, one_sink);

  struct node* zero_sink = node__empty();
  node__set_eq_interval(zero_sink, INT_MIN, 0);
  cah__store(cah, TREE_DEPTH, zero_sink);

  return build_sub_odd(0, bias + 1/2 * sum(weights), cah);
}


int main() {
  struct cache* cah = cah__empty();
  struct node* root = build_odd(weights, bias, cah);
  cah__free(cah);

  int instance[] = {0, 1, 1, 0, 0};
  struct node* cursor = root;
  for (int i=0; i<TREE_DEPTH; i++) {
    cursor = instance[i] ? cursor->rchild : cursor->lchild;
  }

  if (cursor->eq_interval.lower_bound == 0 && cursor->eq_interval.upper_bound == INT_MAX) printf("1\n");
  else if (cursor->eq_interval.lower_bound == INT_MIN && cursor->eq_interval.upper_bound == 0) printf("0\n");

  return 0;
}
