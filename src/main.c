/* Data de submissão:
 * Nome: Igor Peterossi Lopes
 * RA: 174929
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define maxThreads 4 // Máximo de threads a serem executadas simultaneamente

int *numeros = NULL; // Vetor que armazena os números a serem avaliados
int totNums = 0;     // Total de números a serem avaliados
int totPrimos = 0;   // Total de números primos encontrados
int numsAval = 0;    // Quantos números já foram avaliados

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
void *contarPrimos()
{

  int numero = 0; // Número que será avaliado pela thread

  while (1)
  {
    // Se todos os números já foram avaliados
    if (numsAval >= totNums)
      break;

    pthread_mutex_lock(&trava); // Bloqueamos o acesso das outras threads para realizarmos a análise

    numero = checarSePrimo(numeros[numsAval]); // Testamos se o número é primo

    // Se o número é primo
    if (numero != -1)
      totPrimos++; // Incrementamos o contador de números primos

    numsAval++; // Incrementamos o contador de números analisados

    pthread_mutex_unlock(&trava); // Liberamos o acesso para as outras threads
  }

  return NULL;
}

int main()
{

  totNums = receberEntrada(&numeros); // Recebemos as entradas do programa

  pthread_t vetThreads[maxThreads]; // Vetor que armazena os endereços das threads criadas

  // Criamos as threads para realizarem as análises dos números
  for (int i = 0; i < maxThreads; i++)
  {
    pthread_create(&(vetThreads[i]), NULL, contarPrimos, NULL);
  }

  // Aguardamos pelo encerramento das threads
  for (int i = 0; i < maxThreads; i++)
  {
    pthread_join(vetThreads[i], NULL);
  }

  printf("%d\n", totPrimos); // Printamos o total de números primos encontrados

  return 0;
}
