#include "avl.h"

/*
   FUNÇÕES AUXILIARES
*/
int max(int a, int b)
{
  return (a > b) ? a : b;
}

int altura(Avl *n)
{
  if (n == NULL)
    return 0;
  return n->altura;
}

Avl *criarAvl(int valor)
{
  Avl *alvo = (Avl *)malloc(sizeof(Avl));

  alvo->valor = valor;
  alvo->altura = 1;
  alvo->esq = NULL;
  alvo->dir = NULL;

  return alvo;
}

int calcularBalanceamento(Avl *n)
{
  if (n == NULL)
    return 0;

  return altura(n->esq) - altura(n->dir);
}

/*
   ROTAÇÕES Avl
*/

Avl *rotacaoDireita(Avl *y)
{
  Avl *x = y->esq;
  Avl *T2 = x->dir;

  x->dir = y;
  y->esq = T2;

  y->altura = max(altura(y->esq), altura(y->dir)) + 1;
  x->altura = max(altura(x->esq), altura(x->dir)) + 1;

  return x;
}

Avl *rotacaoEsquerda(Avl *x)
{
  Avl *y = x->dir;
  Avl *T2 = y->esq;

  y->esq = x;
  x->dir = T2;

  x->altura = max(altura(x->esq), altura(x->dir)) + 1;
  y->altura = max(altura(y->esq), altura(y->dir)) + 1;

  return y;
}

/*
   INSERÇÃO Avl
*/

Avl *inserir(Avl *Avl, int valor)
{

  if (Avl == NULL)
    return criarAvl(valor);

  if (valor < Avl->valor)
    Avl->esq = inserir(Avl->esq, valor);

  else if (valor > Avl->valor)
    Avl->dir = inserir(Avl->dir, valor);

  else
    return Avl;

  Avl->altura = 1 + max(altura(Avl->esq), altura(Avl->dir));

  int cb = calcularBalanceamento(Avl);

  // Caso LL
  if (cb > 1 && valor < Avl->esq->valor)
    return rotacaoDireita(Avl);

  // Caso RR
  if (cb < -1 && valor > Avl->dir->valor)
    return rotacaoEsquerda(Avl);

  // Caso LR
  if (cb > 1 && valor > Avl->esq->valor)
  {
    Avl->esq = rotacaoEsquerda(Avl->esq);
    return rotacaoDireita(Avl);
  }

  // Caso RL
  if (cb < -1 && valor < Avl->dir->valor)
  {
    Avl->dir = rotacaoDireita(Avl->dir);
    return rotacaoEsquerda(Avl);
  }

  return Avl;
}

/*
   MEAvlR VALOR
*/

Avl *menorValor(Avl *Avl)
{
  Avl *atual = Avl;

  while (atual->esq != NULL)
    atual = atual->esq;

  return atual;
}

/*
   REMOÇÃO Avl
*/

Avl *remover(Avl *raiz, int valor)
{

  if (raiz == NULL)
    return raiz;

  if (valor < raiz->valor)
    raiz->esq = remover(raiz->esq, valor);

  else if (valor > raiz->valor)
    raiz->dir = remover(raiz->dir, valor);

  else
  {

    if ((raiz->esq == NULL) || (raiz->dir == NULL))
    {

      Avl *temp = raiz->esq ? raiz->esq : raiz->dir;

      if (temp == NULL)
      {
        temp = raiz;
        raiz = NULL;
      }
      else
      {
        *raiz = *temp;
      }

      free(temp);
    }
    else
    {

      Avl *temp = menorValor(raiz->dir);

      raiz->valor = temp->valor;

      raiz->dir = remover(raiz->dir, temp->valor);
    }
  }

  if (raiz == NULL)
    return raiz;

  raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));

  int cb = calcularBalanceamento(raiz);

  // LL
  if (cb > 1 && calcularBalanceamento(raiz->esq) >= 0)
    return rotacaoDireita(raiz);

  // LR
  if (cb > 1 && calcularBalanceamento(raiz->esq) < 0)
  {
    raiz->esq = rotacaoEsquerda(raiz->esq);
    return rotacaoDireita(raiz);
  }

  // RR
  if (cb < -1 && calcularBalanceamento(raiz->dir) <= 0)
    return rotacaoEsquerda(raiz);

  // RL
  if (cb < -1 && calcularBalanceamento(raiz->dir) > 0)
  {
    raiz->dir = rotacaoDireita(raiz->dir);
    return rotacaoEsquerda(raiz);
  }

  return raiz;
}

/*
   PROCURA
*/

Avl *procurar(Avl *raiz, int valor)
{

  if (raiz == NULL || raiz->valor == valor)
    return raiz;

  if (valor < raiz->valor)
    return procurar(raiz->esq, valor);

  return procurar(raiz->dir, valor);
}

/*
   PRÉ-ORDEM
*/

void preOrdem(Avl *raiz)
{

  if (raiz != NULL)
  {
    printf("%d ", raiz->valor);
    preOrdem(raiz->esq);
    preOrdem(raiz->dir);
  }
}

/*
   DISTÂNCIA ENTRE NÓS
*/

Avl *LCA(Avl *raiz, int a, int b)
{

  if (raiz == NULL)
    return NULL;

  if (raiz->valor > a && raiz->valor > b)
    return LCA(raiz->esq, a, b);

  if (raiz->valor < a && raiz->valor < b)
    return LCA(raiz->dir, a, b);

  return raiz;
}

int distanciaDaRaiz(Avl *raiz, int valor)
{

  if (raiz->valor == valor)
    return 0;

  if (valor < raiz->valor)
    return 1 + distanciaDaRaiz(raiz->esq, valor);

  return 1 + distanciaDaRaiz(raiz->dir, valor);
}

int distanciaEntreNos(Avl *raiz, int a, int b)
{

  if (procurar(raiz, a) == NULL || procurar(raiz, b) == NULL)
    return -1;

  Avl *lca = LCA(raiz, a, b);

  int d1 = distanciaDaRaiz(lca, a);
  int d2 = distanciaDaRaiz(lca, b);

  return d1 + d2;
}

/*
   LIBERTAR MEMÓRIA
*/

void liberar(Avl *raiz)
{

  if (raiz != NULL)
  {
    liberar(raiz->esq);
    liberar(raiz->dir);
    free(raiz);
  }
}
