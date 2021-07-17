#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "lista.h"

#define TRUE 1
#define FALSE 0

#define EROS TRUE
//#define AKTIN TRUE
#define PARALELO TRUE
#define SERIAL TRUE
//#define OUTPUT TRUE
#define STA_TIME TRUE

int main(){
  int n = 1000;
  Lista *lista = (Lista*)malloc(sizeof(Lista));
  lista->inicio = NULL;
  lista->fim = NULL;

  int totalPrimos = n+1-2;
  #ifdef STA_TIME
    double inicio, end, t_serial, t_paralelo;
  #endif // STA_TIME
  #ifdef EROS
    int i, j;

    #ifdef SERIAL
      printf("SERIAL\n");
      printf("~>Iniciando Variaveis...\n");
      for (i = 0; i <= n; i++) {
        Num* numero = (Num*)malloc(sizeof(Num));
        numero->num = i;
        numero->marca = 0;
        if(lista->fim == NULL && lista->inicio == NULL){
          lista->inicio = numero;
        }else{
          lista->fim->prox = numero;
        }
        lista->fim = numero;
        numero->prox = NULL;
      }

      printf("~>Variaveis Iniciaizadas...\n");
      printf("~>Iniciando Buscas de Primos...\n");

      #ifdef STA_TIME
        inicio = omp_get_wtime();
      #endif

      Num* p = lista->inicio;
      for(int i = 2; i <= n; i++){
        while(p->prox != NULL){
            if(p->prox->num % i == 0 && p->prox->num != i){
                Num* atual = p->prox->prox;
                p->prox->marca++;
                p->prox = atual;
            }
            if(p->prox == NULL){
                break;
            }
            p = p->prox;
        }
        p = lista->inicio;
        if(p->num % i == 0 && p->num != i){
           p->marca++;
        }
      }
      #ifdef STA_TIME
        end = omp_get_wtime();
        printf("~>***%f\n",inicio);
        printf("~>***%f\n",end);
        t_serial = end-inicio;
        printf("~>Tempo para executar o crivo: %f\n", t_serial);
      #endif

      printf("~>Busca Concluida\n");
      printf("~>%d Primos Encrontados", totalPrimos);

      #ifdef OUTPUT
        printf("\n");
        for(i = 2; i <= n; i++){
  	      if(primo[i]){
            printf("%d ",i);
          }
        }
      #endif
    #endif // SERIAL
    #ifdef PARALELO
    printf("\n\n\n\n");

    totalPrimos=n+1-2;
    printf("PARALELO\n");
      printf("~>Iniciando Variaveis...\n");
      p = lista->inicio;
      for(int i = 0; i <= n; i++){
        if(p->prox == NULL){
            break;
        }
        p->marca = 0;
        p = p->prox;
      }

      printf("~>Variaveis Iniciaizadas...\n");
      printf("~>Iniciando Buscas de Primos...\n");

      #ifdef STA_TIME
        inicio = omp_get_wtime();
      #endif

      #pragma omp parallel num_threads(4)
      {
        p = lista->inicio;
        j=4;
        #pragma omp for
          for(int i = 2; i <= n; i++){
            while(p->prox != NULL){
              if(p->prox->num % i == 0 && p->prox->num != i){
                Num* atual = p->prox->prox;
                p->prox->marca++;
                p->prox = atual;
              }
              if(p->prox == NULL){
                break;
              }
              p = p->prox;
            }
            p = lista->inicio;
            if(p->num % i == 0 && p->num != i){
              p->marca++;
              totalPrimos--;
            }
          }
        }

      #ifdef STA_TIME
        end = omp_get_wtime();
        printf("***%f\n",inicio);
        printf("***%f\n",end);
        t_paralelo = end-inicio;
        printf("Tempo para executar o crivo: %f\n", t_paralelo);
        double speedup = t_serial/t_paralelo;
        printf("Speedup: %.4f\n", t_serial/t_paralelo);
        printf("Eficiencia: %.4f\n",speedup/4.0);

      #endif
      printf("~>Busca Concluida\n");
      printf("~>%d Primos Encontrados", totalPrimos);

      #ifdef OUTPUT
        printf("\n");
        for(i = 2; i <= n; i++){
  	      if(primo[i]){
            printf("%d ",i);
          }
        }
      #endif
    #endif // PARALELO
  #endif


  return 0;
}
