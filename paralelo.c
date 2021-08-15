#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define TRUE 1
#define FALSE 0
#define NUM_THEARDS 4

#define STA_TIME TRUE

int main(){
  int n = 10000000;
  int *num = malloc((1+n)*sizeof(int));

  #ifdef STA_TIME
    double inicio, end, tiempo;
  #endif // STA_TIME
  int i;
  printf("PARALELO Com T\n");
  printf("~>Iniciando Variaveis...\n");
  for (i = 0; i <= n; i++) {
    num[i]=i;
  }

  printf("~>Variaveis Iniciaizadas...\n");
  printf("~>Iniciando Buscas de Primos...\n");

  #ifdef STA_TIME
    inicio = omp_get_wtime();
  #endif
  num[0]=-1;
  num[1]=-1;
  #pragma omp parallel num_threads(2)
  {
  #pragma omp for
    for(int i = 2; i <= n/2 +1; i++){
      if(num[i]!=-1){
        for(int j=i+i; j<=n; j+=i){
          if(num[j]%i==0){
            num[j] = -1;
          }
        }
      }
    }
  }
  #ifdef STA_TIME
    end = omp_get_wtime();
    tiempo = end-inicio;
    printf("~>Tempo Inicial: %f\n",inicio);
    printf("~>Tempo Final: %f\n",end);
    printf("~>Tempo: %f\n", tiempo);
  #endif

  printf("~>Busca Concluida\n");
  return 0;
}
