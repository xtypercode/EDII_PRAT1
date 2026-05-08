#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Avl
{
  int valor;
  int altura;
  struct No *esq;
  struct No *dir;
} No;