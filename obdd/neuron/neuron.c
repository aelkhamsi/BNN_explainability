#include "neuron.h"



struct neuron nrn__empty() {
  struct list* l = list__empty();
  struct neuron n = {l, 0};
  return n;
}

struct neuron nrn__set_weights(struct neuron n, float weights[], size_t size) {
  for (size_t i=0; i<size; i++)
    list__add(n.weights, weights[i]);
  return n;
}

struct neuron nrn__set_bias(struct neuron n, int bias) {
  n.bias = bias;
  return n;
}

int nrn__classify(struct neuron n, int instance[], size_t size) {
  if (size != n.weights->size) return -1;
  int sum=0;
  for (size_t i=0; i<n.weights->size; i++)
    sum += n.weights->l[i] * instance[i];
  return sum + n.bias >= 0;
}
