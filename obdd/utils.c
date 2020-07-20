#include "utils.h"


//AUXILIARY FUNCTIONS
struct interval offset(struct interval interval, float offset) {
  struct interval new_interval = {INT_MIN, INT_MAX};
  if (interval.lower_bound != INT_MIN)
    new_interval.lower_bound = interval.lower_bound + offset;
  if (interval.upper_bound != INT_MAX)
    new_interval.upper_bound = interval.upper_bound + offset;
  return new_interval;
}


float sum(float weights[]) {
  float sum = 0.0;
  for (int i=0; i<TREE_DEPTH; i++) {
    sum += weights[i];
  }
  return sum;
}


struct interval conjunction(struct interval interval1, struct interval interval2) {
  float lower_bound = interval1.lower_bound < interval2.lower_bound ? interval2.lower_bound : interval1.lower_bound;
  float upper_bound = interval1.upper_bound < interval2.upper_bound ? interval1.upper_bound : interval2.upper_bound;
  struct interval conj_int = {lower_bound, upper_bound};
  return conj_int;
}
/////////////////////


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
    printf("%d [%f, %f] | ", file[0]->variable_index, file[0]->eq_interval.lower_bound, file[0]->eq_interval.upper_bound);
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
