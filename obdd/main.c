#include "tree.h"
#include "cache.h"
#include "utils.h"


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//GLOBAL VARIABLES
float weights[] = {1, -1, -1, 1};
int bias = 0.5;
//////////////////




//MAIN
struct node* build_sub_odd(int depth, float plo, struct cache* cah) {  //plo == prior_log_odds
  struct node* node = node__empty();
  node__set_eq_interval(node, INT_MIN, INT_MAX);
  node__set_variable_index(node, depth);

  for (int e=0; e<=1; e++) {  //every value ek+1 of Ek+1
    float weight_child = 0.5 * (e==1 ? weights[depth] : -1*weights[depth]);
    float plo_child = plo + weight_child;
    //searching for child node in cache
    struct node* child = cah__find(cah, depth+1, plo_child);
    if (child == NULL) {
      child = build_sub_odd(depth+1, plo_child, cah);
    }
    //add_child
    e==1 ? node__add_rchild(node, child): node__add_lchild(node, child);
    //update eq_interval
    node->eq_interval = conjunction(node->eq_interval, offset(child->eq_interval, -1*weight_child));
  }

  cah__store(cah, depth, node);
  return node;
}


struct node* build_odd(float weights[], float bias, struct cache* cah) {  //log_odds threshold == 0
  struct node* one_sink = node__empty();
  node__set_eq_interval(one_sink, 0, INT_MAX);
  node__set_variable_index(one_sink, -1);
  cah__store(cah, TREE_DEPTH, one_sink);

  struct node* zero_sink = node__empty();
  node__set_eq_interval(zero_sink, INT_MIN, 0);
  node__set_variable_index(zero_sink, -2);
  cah__store(cah, TREE_DEPTH, zero_sink);

  return build_sub_odd(0, bias + 1/2 * sum(weights), cah);
}


int odd__classify(struct node* root, int instance[]) {
  struct node* cursor = root;
  int variable_index = 0;
  while(cursor->variable_index >= 0) {
    cursor = instance[variable_index] ? cursor->rchild : cursor->lchild;
    variable_index++;
  }

  if (cursor->variable_index == -1) return 1;
  else if (cursor->variable_index == -2) return 0;
  else return -1;
}



int main() {
  struct cache* cah = cah__empty();
  struct node* root = build_odd(weights, bias, cah);

  //plot
  plot(root);


  cah__free(cah);


  //results

  for (int a=0; a<2; a++)
    for (int b=0; b<2; b++)
      for (int c=0; c<2; c++)
        for (int d=0; d<2; d++) {
          int instance[] = {a, b, c, d};
          printf("[%d, %d, %d, %d] -> %d\n", a, b, c, d, odd__classify(root, instance));
        }



  return 0;
}
