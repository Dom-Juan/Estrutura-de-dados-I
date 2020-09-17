//
// Created by ratob on 08/09/2020.
//

#ifndef EXERCICIOS_ARVORE_ESTRUTURAS_H
#define EXERCICIOS_ARVORE_ESTRUTURAS_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct nodeArvore{
    int info;
    struct nodeArvore *left;
    struct nodeArvore *right;
}node_bin;

typedef struct nodeArvoreExp{
    char value;
    struct nodeArvoreExp *left;
    struct nodeArvoreExp *right;
}node_exp;

typedef struct nodeAVL{
    int info;
    int h;
    int balance;
    struct nodeAVL *left;
    struct nodeAVL *right;
}node_avl;

typedef struct nodeList{
    int info;
    struct nodeList *next;
}lt;

#endif //EXERCICIOS_ARVORE_ESTRUTURAS_H
