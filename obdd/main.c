#include "tree.h"
#include "cache.h"
#include "utils.h"
#include "neuron.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//GLOBAL VARIABLES
float weights[] = {1.0, -1.0, 1.0, 1.0, 1.0, -1.0, 1.0, 1.0, -1.0, -1.0};
float bias = 0.2;
//////////////////




//MAIN
struct node* build_sub_odd(int depth, float plo, struct cache* cah) {  //plo == prior_log_odds
  struct node* node = node__empty();
  node__set_eq_interval(node, (float)INT_MIN, (float)INT_MAX);
  node__set_variable_index(node, depth);

  for (int e=0; e<=1; e++) {  //every value ek+1 of Ek+1
    float weight_child = 0.5 * (e==1 ? weights[depth] : -1*weights[depth]);
    float plo_child = plo + weight_child;
    //searching for child node in cache
    struct node* child = cah__find(cah, depth+1, plo_child);
    if (child == NULL)
      child = build_sub_odd(depth+1, plo_child, cah);

    //add_child
    e==1 ? node__add_rchild(node, child): node__add_lchild(node, child);
    //update eq_interval
    node->eq_interval = conjunction(node->eq_interval, offset(child->eq_interval, -1*weight_child));

    // printf("[%f, %f]\n", node->eq_interval.lower_bound, node->eq_interval.upper_bound);
    // node->eq_interval.empty ? printf("empty\n") : printf("not empty\n");
  }

  if (node->rchild == node->lchild) {
    struct node* child = node->rchild;
    free(node);
    return child;
  }

  cah__store(cah, depth, node);
  return node;
}


struct node* build_odd(float weights[], float bias, struct cache* cah) {  //log_odds threshold == 0
  struct node* one_sink = node__empty();
  node__set_eq_interval(one_sink, 0.0, (float)INT_MAX);
  node__set_variable_index(one_sink, -1);
  cah__store(cah, TREE_DEPTH, one_sink);

  struct node* zero_sink = node__empty();
  node__set_eq_interval(zero_sink, (float)INT_MIN, 0.0);
  node__set_variable_index(zero_sink, -2);
  cah__store(cah, TREE_DEPTH, zero_sink);

  float prior_log_odds = bias + 0.5 * sum(weights);
  printf("BIAS: %f\n", bias);
  printf("PLO: %f\n", prior_log_odds);
  return build_sub_odd(0, prior_log_odds, cah);
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


double test(struct node* root) {
  struct neuron n = nrn__empty();
  nrn__set_weights(n, weights, TREE_DEPTH);
  nrn__set_bias(n, bias);
  int correct = 0;
  int total = 0;

  for (int a=0; a<2; a++)
    for (int b=0; b<2; b++)
      for (int c=0; c<2; c++)
        for (int d=0; d<2; d++) {
          int instance[] = {a, 0, 0, b, 0, c, 0, d, 0, 0};
          if (odd__classify(root, instance) == nrn__classify(n, instance, TREE_DEPTH))
            correct+=1;
          total+=1;
          // printf("[%d, %d, %d, %d] -> odd: %d | neuron: %d\n", a, b, c, d, odd__classify(root, instance), nrn__classify(n, instance, 4));
          // assert(odd__classify(root, instance) == nrn__classify(n, instance, 4));
        }
  return ((double)correct/(double)total)*100;
}





int main() {
  struct cache* cah = cah__empty();
  struct node* root = build_odd(weights, bias, cah);

  //plot
  plot(root);

  //test
  double precision = test(root);
  printf("ODD Precision: %f %% \n", precision);

  // check_cah(cah);
  count_cache(cah);
  print_cache(cah);

  cah__free(cah);

  return 0;
}
