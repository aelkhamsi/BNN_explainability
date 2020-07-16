#ifndef NEURON_H
#define NEURON_H

#include <stdio.h>
#include <stdlib.h>
#include "list.h"


struct neuron {
  struct list* weights;
  int bias;
};

struct neuron nrn__empty();

struct neuron nrn__set_weights(struct neuron n, float weights[], size_t size); //size of the instance

struct neuron nrn__set_bias(struct neuron n, int bias);

int nrn__classify(struct neuron n, int instance[], size_t size); //size of the instance

#endif
