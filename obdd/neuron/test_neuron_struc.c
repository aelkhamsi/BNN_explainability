#include "neuron.h"
#include <assert.h>

int test_nrn__empty() {
  struct neuron n = nrn__empty();
  assert(list__is_empty(n.weights));
  assert(n.bias == 0);

  list__free(n.weights);
  printf(". ");
  return 1;
}

int test_nrn__set_weights() {
  struct neuron n = nrn__empty();
  float weights[] = {1, -1, -1, 1};
  n = nrn__set_weights(n, weights, 4);
  assert(list__size(n.weights) == 4);

  list__free(n.weights);
  printf(". ");
  return 1;
}

int test_nrn__set_bias() {
  struct neuron n = nrn__empty();
  int bias = 0.5;
  n = nrn__set_bias(n, bias);
  assert(n.bias == bias);

  list__free(n.weights);
  printf(". ");
  return 1;
}

int test_nrn__classify() {
  struct neuron n = nrn__empty();
  float weights[] = {1, -1, -1, 1};
  int bias = 0.5;
  nrn__set_weights(n, weights, 4);
  nrn__set_bias(n, bias);

  for (int a=0; a<=1; a++)
    for (int b=0; b<=1; b++)
      for (int c=0; c<=1; c++)
        for (int d=0; d<=1; d++) {
          int instance[4] = {a, b, c, d};
          if (((b==1 || c==1) && (a==0 && d==0)) || (b==1 && c==1 && (a==0 || d==0))) {
            // printf("[%d, %d, %d, %d] (0) -> %d\n", a, b, c, d, nrn__classify(n, instance, 4));
            assert(nrn__classify(n, instance, 4) == 0);
          }
          else {
            // printf("[%d, %d, %d, %d] (1) -> %d\n", a, b, c, d, nrn__classify(n, instance, 4));
            assert(nrn__classify(n, instance, 4) == 1);
          }
        }
  list__free(n.weights);
  printf(". ");
  return 1;
}


int main() {
  test_nrn__empty();
  test_nrn__set_weights();
  test_nrn__set_bias();
  test_nrn__classify();

  printf(" [");
  printf("\033[1;32m");
  printf("OK");
  printf("\033[0m");
  printf("]");

  printf("\n");
  return 0;
}
