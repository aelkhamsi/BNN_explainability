#include "utils.h"


//AUXILIARY FUNCTIONS
struct interval offset(struct interval interval, float offset) {
  struct interval new_interval = {INT_MIN, INT_MAX, false};
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
  if (interval1.upper_bound <= interval2.lower_bound || interval2.upper_bound <= interval1.lower_bound) {
    struct interval empty_int = {0, 0, true};
    return empty_int;
  }
  float lower_bound = interval1.lower_bound <= interval2.lower_bound ? interval2.lower_bound : interval1.lower_bound;
  float upper_bound = interval1.upper_bound <= interval2.upper_bound ? interval1.upper_bound : interval2.upper_bound;
  struct interval conj_int = {lower_bound, upper_bound, false};
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
  // a[label=<Birth of George Washington<BR />
  //       <FONT POINT-SIZE="10">See also: American Revolution</FONT>>];
  // fprintf(fptr, "%d [label=\<%d\<BR /\> \<FONT POINT-SIZE=\"10\"\>[%.1f, %.1f[\</FONT\>\>];\n", file[0]->version, file[0]->variable_index, file[0]->eq_interval.lower_bound, file[0]->eq_interval.upper_bound);


  while(file[0] != NULL) {
    if (file[0]->rchild != NULL) {
      // fprintf(fptr, "%d [label=\"%d\", xlabel=\"[%.1f, %.1f[\"];\n", file[0]->version, file[0]->variable_index, file[0]->eq_interval.lower_bound, file[0]->eq_interval.upper_bound);
      fprintf(fptr, "%d [label=<<B>%d</B><BR /> <FONT POINT-SIZE=\"10\">[%.1f, %.1f[</FONT>>];\n", file[0]->version, file[0]->variable_index, file[0]->eq_interval.lower_bound, file[0]->eq_interval.upper_bound);
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


void check_cah(struct cache* cah) {
  for (int depth=0; depth<TREE_DEPTH+1; depth++) {
    struct lelement* cursor = cah->set[depth]->head;
    int flag=0;
    while((cursor != NULL && cursor->next != cursor) && (cursor->next != NULL && cursor->next->next != cursor->next)) { //at least 2 elements
      struct node* n1 = cursor->pt;
      struct node* n2 = cursor->next->pt;
      struct interval conj = conjunction(n1->eq_interval, n2->eq_interval);
      if (conj.empty == false) {
        flag=1;
        printf("1 ");
        printf("[%f, %f] - [%f, %f] -> conj [%f, %f]",
        n1->eq_interval.lower_bound, n1->eq_interval.upper_bound,
        n2->eq_interval.lower_bound, n2->eq_interval.upper_bound,
        conj.lower_bound, conj.upper_bound);
      }
      cursor = cursor->next;
    }
    flag ? printf("\n") : printf("0\n");
  }
}

void count_cache(struct cache* cah) {
  printf("\033[1;31m");
  printf("\nCACHE COUNT (number of elements in the cache)\n");
  printf("\033[0m");
  int counter=0;
  for (int depth=0; depth<TREE_DEPTH+1; depth++) {
    struct lelement* cursor = cah->set[depth]->head;
    while(cursor != NULL && cursor->next != cursor) {
      counter++;
      cursor = cursor->next;
    }
  }
  printf("%d\n", counter);
}

void print_cache(struct cache* cah) {
  printf("\033[1;31m");
  printf("\nCACHE PRINT\n");
  printf("\033[0m");

  printf("(x=variable --- equivalence interval)\n");

  for (int depth=0; depth<TREE_DEPTH+1; depth++) {
    printf("\033[1;32m");
    printf("DEPTH %d: ", depth);
    printf("\033[0m");
    struct lelement* cursor = cah->set[depth]->head;
    while(cursor != NULL && cursor->next != cursor) {
      struct node* node = cursor->pt;
      //print
      if (node->variable_index == -1) printf("x=one_sink --- [%f, %f] \033[1;32m | \033[0m ", node->eq_interval.lower_bound, node->eq_interval.upper_bound);
      else if (node->variable_index == -2) printf("x=zero_sink --- [%f, %f] \033[1;32m | \033[0m ", node->eq_interval.lower_bound, node->eq_interval.upper_bound);
      else printf("x=%d --- [%f, %f] \033[1;32m | \033[0m", node->variable_index, node->eq_interval.lower_bound, node->eq_interval.upper_bound);

      cursor = cursor->next;
    }
    printf("\n");
  }
  printf("\n");
}
