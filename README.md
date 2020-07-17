# M2R

## For OBDD compilation of a neuron
In the **obdd** folder, follow these instructions:

1. Enter the **number of inputs** of the neuron by modifying the '#define TREE_DEPTH ...' in **cst.h**
2. Enter the **weights** and **bias** of the neuron by modifying the global variables 'float weights[]' and 'int bias' in **main.c**
3. Enter the following command:

```bash
  bash plot_obdd.sh
```
    
The OBDD will be represented in the **obdd.png** image
