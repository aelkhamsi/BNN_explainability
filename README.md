# M2R

We explored is this project a variant of neural networks with binary parameters (Binarized neural networks). We've tried to compile this type of networks into OBDDs (Ordered Binary Decision Diagram) and use the compiled version to explain decisions taken by the original neural networks. The report of our study gives a lot of insight and list all the ressources that we've used to carry out successfully this project. You can read the study report by following the link bellow:
https://documentcloud.adobe.com/link/review?uri=urn:aaid:scds:US:666a19ee-db33-404a-ae71-5f0cba59149b

## BNN (Binarized Neural Networks)
In the **bnn** folder, we developed a BNN for the dataset MNIST, along with a CNN and a classical NN for performance comparison.

We extended the study of BNN to more datasets like CIFAR10 and BreastCancerDiagnose. We also compared between the preformance of different types of networks. For more convenience, we've worked with Google Colaboratory so that the code will be ready to run. We will find a lot of ressources in the following link:
https://drive.google.com/drive/folders/1jPQTYmlhDubGk8le6MMNZNNgtv1GQqA7?usp=sharing



## For OBDD compilation of a neuron
In the **obdd** folder, follow these instructions:

1. Enter the **number of inputs** of the neuron by modifying the '#define TREE_DEPTH ...' in **cst.h**
2. Enter the **weights** and **bias** of the neuron by modifying the global variables 'float weights[]' and 'int bias' in **main.c**
3. Enter the following command:

```bash
  bash plot_obdd.sh
```
    
The OBDD will be represented in the **obdd.png** image. Details of the algorithm are given in the study report (link above).
