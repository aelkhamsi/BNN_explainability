#include "tree.h"
#include "cache.h"

// #include "utils.h"

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
  node__set_variable_index(node, depth);

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
  node__set_variable_index(one_sink, -1);
  cah__store(cah, TREE_DEPTH, one_sink);

  struct node* zero_sink = node__empty();
  node__set_eq_interval(zero_sink, INT_MIN, 0);
  node__set_variable_index(zero_sink, -2);
  cah__store(cah, TREE_DEPTH, zero_sink);

  return build_sub_odd(0, bias + 1/2 * sum(weights), cah);
}



/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

void add_in_file(struct node* file[100], struct node* node) {
  if (node != NULL) {
    for (int i=0; i<100; i++) {
      if (file[i] == node)
        return;
      else if (file[i] == NULL) {
        file[i] = node;
        return;
      }
    }
  }
}

void shift_to_head(struct node* file[100]) {
  for (int i=1; i<100; i++) {
    file[i-1] = file[i];
  }
  return;
}

void breath_first_print(struct node* root) {  //Breath-first print
  //init file
  struct node* file[100];
  for (int i=0; i<100; i++) {
    file[i] = NULL;
  }
  file[0] = root;
  int variable_index = 0;

  //search
  while(file[0] != NULL) {
    if (variable_index != file[0]->variable_index) {
      variable_index = file[0]->variable_index;
      printf("\n");
    }
    printf("%d [%d, %d] | ", file[0]->variable_index, file[0]->eq_interval.lower_bound, file[0]->eq_interval.upper_bound);
    add_in_file(file, file[0]->lchild);
    add_in_file(file, file[0]->rchild);
    shift_to_head(file);
  }
  return;
}


void plot(struct node* root) {
  char* dotted_line = "[style=dotted, arrowhead=\"none\"];\n";
  char* solid_line = "[style=solid, arrowhead=\"none\"];\n";
  //ptr file
  struct node* file[100];
  for (int i=0; i<100; i++) {
    file[i] = NULL;
  }
  file[0] = root;
  //open gv file
  FILE *fptr = fopen("obdd.gv", "a");
  if(fptr == NULL) {
    printf("Error!");
    exit(1);
  }
  //write
  while(file[0] != NULL) {
    if (file[0]->rchild != NULL) {
      if (file[0]->rchild->variable_index == -1) {
        fprintf(fptr, "%d->%s ", file[0]->version, "oneSink");
        fprintf(fptr, "%s", solid_line);
      }
      else if (file[0]->rchild->variable_index == -2) {
        fprintf(fptr, "%d->%s ", file[0]->version, "zeroSink");
        fprintf(fptr, "%s", solid_line);
      }
      else {
        fprintf(fptr, "%d->%d ", file[0]->version, file[0]->rchild->version);
        fprintf(fptr, "%s", solid_line);
      }
    }
    if (file[0]->lchild != NULL) {
      if (file[0]->lchild->variable_index == -1) {
        fprintf(fptr, "%d->%s ", file[0]->version, "oneSink");
        fprintf(fptr, "%s", dotted_line);
      }
      else if (file[0]->lchild->variable_index == -2) {
        fprintf(fptr, "%d->%s ", file[0]->version, "zeroSink");
        fprintf(fptr, "%s", dotted_line);
      } else {
        fprintf(fptr, "%d->%d ", file[0]->version, file[0]->lchild->version);
        fprintf(fptr, "%s", dotted_line);
      }
    }

    add_in_file(file, file[0]->lchild);
    add_in_file(file, file[0]->rchild);
    shift_to_head(file);
  }
  fprintf(fptr, "}");
  //close gv file
  fclose(fptr);
  return;
}
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////


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
