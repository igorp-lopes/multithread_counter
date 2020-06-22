/* Contador de palavras
 *
 * Este programa recebera uma serie de caracteres representando palavras em sua
 * entrada. Ao receber um caractere fim de linha ('\n'), deve imprimir na tela o
 * numero de palavras separadas que recebeu e, apos, encerrar.
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define maxThreads 4 // Máximo de threads a serem executadas simultaneamente

int *numeros = NULL; // Vetor que armazena os números a serem avaliados
int totPrimos = 0; // Total de números primos encontrados

pthread_mutex_t trava; // Mutex usado para o controle do fluxo de análise

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


/* Função a ser executada pelo thread, que conta quantos números são primos */
void* contarPrimos(void *arg)
{
  
  // Salvamos o identificador da thread atual
  int* temp = (int*) arg;
  int identificador = *temp;

  printf("\nThread %d foi iniciada\n", identificador);
  for (int j=0; j<1000000; j++);
  printf("\nThread %d foi encerrada\n", identificador);

  return NULL;

}

int main()
{

  int totNums = 0; // Total de números a serem avaliados

  totNums = receberEntrada(&numeros); // Recebemos as entradas do programa

  pthread_t vetThreads[maxThreads]; // Vetor que armazena os endereços das threads criadas
  int threadIds[maxThreads]; // Vetor que armazena os identificadores de cada thread

  // Atribuindo um identificador para cada thread
  for (int i = 0; i < maxThreads; i++)
  {
    threadIds[i] = i + 1;
  }

  // Criando as threads para realizarem as análises dos números
  for (int i = 0; i < maxThreads; i++)
  {
    pthread_create(&(vetThreads[i]), NULL, contarPrimos, (void*) (&threadIds[i]));
  }

  // Aguardamos pelo encerramento das threads
  for (int i = 0; i < maxThreads; i++)
  {
    pthread_join(vetThreads[i], NULL);
  }


  return 0;
}
