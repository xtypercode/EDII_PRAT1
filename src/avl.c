#include "avl.h"

/*
   FUNÇÕES AUXILIARES
*/
int max(int a, int b)
{
  return (a > b) ? a : b;
}

static int altura(AVL *n)
{
  if (n == NULL)
    return 0;
  return n->altura;
}

static AVL *criarAVL(int valor)
{
  AVL *alvo = (AVL *)malloc(sizeof(AVL));

  if (alvo == NULL)
    return NULL;

  alvo->valor = valor;
  alvo->altura = 1;
  alvo->esq = NULL;
  alvo->dir = NULL;

  return alvo;
}

static int calcularBalanceamento(AVL *n)
{
  if (n == NULL)
    return 0;

  return altura(n->esq) - altura(n->dir);
}

/*
   ROTAÇÕES AVL
*/

static AVL *rotacaoDireita(AVL *y)
{
  AVL *x = y->esq;
  AVL *T2 = x->dir;

  x->dir = y;
  y->esq = T2;

  y->altura = max(altura(y->esq), altura(y->dir)) + 1;
  x->altura = max(altura(x->esq), altura(x->dir)) + 1;

  return x;
}

static AVL *rotacaoEsquerda(AVL *x)
{
  AVL *y = x->dir;
  AVL *T2 = y->esq;

  y->esq = x;
  x->dir = T2;

  x->altura = max(altura(x->esq), altura(x->dir)) + 1;
  y->altura = max(altura(y->esq), altura(y->dir)) + 1;

  return y;
}

/*
   INSERÇÃO AVL
*/

AVL *inserir(AVL *raiz, int valor)
{

  if (raiz == NULL)
    return criarAVL(valor);

  if (valor < raiz->valor)
    raiz->esq = inserir(raiz->esq, valor);

  else if (valor > raiz->valor)
    raiz->dir = inserir(raiz->dir, valor);

  else
    return raiz;

  raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));

  int cb = calcularBalanceamento(raiz);

  // Rtoação simples à direita
  if (cb > 1 && valor < raiz->esq->valor)
    return rotacaoDireita(raiz);

  // Rotação simples à esquerda
  if (cb < -1 && valor > raiz->dir->valor)
    return rotacaoEsquerda(raiz);

  // Rotação dupla à direita
  if (cb > 1 && valor > raiz->esq->valor)
  {
    raiz->esq = rotacaoEsquerda(raiz->esq);
    return rotacaoDireita(raiz);
  }

  // Rotação dupla à esquerda
  if (cb < -1 && valor < raiz->dir->valor)
  {
    raiz->dir = rotacaoDireita(raiz->dir);
    return rotacaoEsquerda(raiz);
  }

  return raiz;
}

/*
   MENOR VALOR
*/

static AVL *menorValor(AVL *raiz)
{
  AVL *atual = raiz;

  while (atual->esq != NULL)
    atual = atual->esq;

  return atual;
}

/*
   REMOÇÃO AVL
*/

AVL *remover(AVL *raiz, int valor)
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

      AVL *temp = raiz->esq ? raiz->esq : raiz->dir;

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

      AVL *temp = menorValor(raiz->dir);

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

AVL *procurar(AVL *raiz, int valor)
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

void preOrdem(AVL *raiz)
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

static AVL *LCA(AVL *raiz, int a, int b)
{

  if (raiz == NULL)
    return NULL;

  if (raiz->valor > a && raiz->valor > b)
    return LCA(raiz->esq, a, b);

  if (raiz->valor < a && raiz->valor < b)
    return LCA(raiz->dir, a, b);

  return raiz;
}

static int distanciaDaRaiz(AVL *raiz, int valor)
{

  if (raiz == NULL)
    return -1;

  if (raiz->valor == valor)
    return 0;

  int sub;

  if (valor < raiz->valor)
    sub = distanciaDaRaiz(raiz->esq, valor);
  else
    sub = distanciaDaRaiz(raiz->dir, valor);

  if (sub == -1)
    return -1;

  return 1 + sub;
}

int distanciaEntreNos(AVL *raiz, int a, int b)
{

  if (procurar(raiz, a) == NULL || procurar(raiz, b) == NULL)
    return -1;

  AVL *lca = LCA(raiz, a, b);

  int d1 = distanciaDaRaiz(lca, a);
  int d2 = distanciaDaRaiz(lca, b);

  return d1 + d2;
}

/*
   LIBERTAR MEMÓRIA
*/

void liberar(AVL *raiz)
{

  if (raiz != NULL)
  {
    liberar(raiz->esq);
    liberar(raiz->dir);
    free(raiz);
  }
}
