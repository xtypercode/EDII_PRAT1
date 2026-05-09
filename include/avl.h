#ifndef AVL_H
# define AVL_H

# include <stdio.h>
# include <stdlib.h>

typedef struct No
{
  int valor;
  int altura;
  struct No *esq;
  struct No *dir;
} AVL;

AVL *inserir(AVL *raiz, int valor);
AVL *remover(AVL *raiz, int valor);
AVL *procurar(AVL *raiz, int valor);
void preOrdem(AVL *raiz);
int distanciaEntreNos(AVL *raiz, int a, int b);
void liberar(AVL *raiz);

#endif