/* Contador de palavras
 *
 * Este programa recebera uma serie de caracteres representando palavras em sua
 * entrada. Ao receber um caractere fim de linha ('\n'), deve imprimir na tela o
 * numero de palavras separadas que recebeu e, apos, encerrar.
 */

#include <stdio.h>

/* Função que recebe a string de entrada com os números a serem análisados e extrai desta 
   cada número e os salva em um vetor */
int receberEntrada(int **numeros)
{

  char entrada[300]; // Armazena a entrada do programa como uma string
  char *p;
  int tam = 0; // Tamanho do vetor que armazena os números

  fgets(entrada, sizeof(entrada), stdin); // Recebemos a string de entrada

  p = strtok(entrada, " \n");     // Selecionamos o primeiro número da entrada
  for (tam = 0; p != NULL; tam++) // Extraímos os números da string
  {
    *numeros = (int *)realloc(*numeros, (sizeof(int) * (tam + 1))); // Alocamos mais espaço para o vetor

    (*numeros)[tam] = atoi(p); // Salvamos no vetor o número convertido para int

    p = strtok(NULL, " \n"); // Selecionamos o próximo número
  }

  return tam;
}

/* Função que identifica se o número é primo, retornando o número se ele for 
   primo e -1 se ele não for primo*/
int checarSePrimo(int numero)
{

  // Casos base
  if ((numero == 1) || (numero == 0))
  {
    return -1;
  }

  for (int i = 2; i <= numero / 2; ++i)
  {

    // Se o número não é primo
    if (numero % i == 0)
    {
      numero = -1;
      break;
    }
  }

  return numero;
}

int main()
{

  int x, y;

  scanf("%d %d\n", &x, &y);
  printf("%d\n", x + 200);
  return 0;
}
