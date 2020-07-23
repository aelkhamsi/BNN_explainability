#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "tree.h"
#include "cache.h"
#include "cst.h"


struct interval offset(struct interval interval, float offset);

float sum(float weights[]);

struct interval conjunction(struct interval interval1, struct interval interval2);

void breath_first_print(struct node* root) ;

void plot(struct node* root);


//cache
void check_cah(struct cache* cah);

void count_cache(struct cache* cah);

void print_cache(struct cache* cah);


#endif
