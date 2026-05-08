#include "avl.h"

int main()
{

  AVL *raiz = NULL;

  int opcao;
  int valor;
  int a, b;

  do
  {

    printf("\n===== AVL =====\n");
    printf("1. Inserir\n");
    printf("2. Remover\n");
    printf("3. Procurar\n");
    printf("4. Imprimir Pre-Ordem\n");
    printf("5. Distancia entre dois nos\n");
    printf("0. Sair\n");

    printf("Opcao: ");
    scanf("%d", &opcao);

    switch (opcao)
    {

    case 1:

      printf("Valor a inserir: ");
      scanf("%d", &valor);

      raiz = inserir(raiz, valor);

      break;

    case 2:

      printf("Valor a remover: ");
      scanf("%d", &valor);

      raiz = remover(raiz, valor);

      break;

    case 3:

      printf("Valor a procurar: ");
      scanf("%d", &valor);

      if (procurar(raiz, valor))
        printf("Valor encontrado!\n");
      else
        printf("Valor nao encontrado!\n");

      break;

    case 4:

      printf("Pre-Ordem: ");
      preOrdem(raiz);
      printf("\n");

      break;

    case 5:

      printf("Primeiro no: ");
      scanf("%d", &a);

      printf("Segundo no: ");
      scanf("%d", &b);

      int dist;
      dist = distanciaEntreNos(raiz, a, b);

      if (dist == -1)
        printf("Um ou ambos os nos nao existem.\n");
      else
        printf("Distancia entre %d e %d = %d\n", a, b, dist);

      break;

    case 0:

      printf("Encerrando...\n");
      break;

    default:

      printf("Opcao invalida!\n");
    }

  } while (opcao != 0);

  liberar(raiz);

  return 0;
}