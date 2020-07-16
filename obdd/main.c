#include "tree.h"
#include "cache.h"
#include "utils.h"


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//GLOBAL VARIABLES
float weights[] = {1, -1, 1, 1, -1, -1, 1, -1, 1, -1};
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




int main() {
  struct cache* cah = cah__empty();
  struct node* root = build_odd(weights, bias, cah);

  breath_first_print(root);
  plot(root);
  cah__free(cah);


  //results

  // for (int a=0; a<2; a++) {
  //   for (int b=0; b<2; b++) {
  //     for (int c=0; c<2; c++) {
  //       for (int d=0; d<2; d++) {
  //         for (int e=0; e<2; e++) {
  //           int instance[] = {a, b, c, d, e};
  //           struct node* cursor = root;
  //           for (int i=0; i<TREE_DEPTH; i++) {
  //             cursor = instance[i] ? cursor->rchild : cursor->lchild;
  //           }
  //
  //           //result
  //           if (cursor->eq_interval.lower_bound == 0 && cursor->eq_interval.upper_bound == INT_MAX) printf("1\n");
  //           else if (cursor->eq_interval.lower_bound == INT_MIN && cursor->eq_interval.upper_bound == 0) printf("0\n");
  //         }
  //       }
  //     }
  //   }
  // }


  //result

  // int instance[] = {1, 0, 0, 1, 1};
  // struct node* cursor = root;
  // for (int i=0; i<TREE_DEPTH; i++) {
  //   cursor = instance[i] ? cursor->rchild : cursor->lchild;
  // }
  // if (cursor->eq_interval.lower_bound == 0 && cursor->eq_interval.upper_bound == INT_MAX) printf("1\n");
  // else if (cursor->eq_interval.lower_bound == INT_MIN && cursor->eq_interval.upper_bound == 0) printf("0\n");


  //size of links in cache
  // printf("%d", lnk__size(cah->set[TREE_DEPTH]));



  return 0;
}
