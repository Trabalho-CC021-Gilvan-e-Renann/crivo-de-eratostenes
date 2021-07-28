#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define TRUE 1
#define FALSE 0

#define STA_TIME TRUE
//#define OUTPUT TRUE

int main(){
  int n = 10*1000*1000;
  int *num = malloc((1+n)*sizeof(int));

  int totalPrimos = n+1-2;
  #ifdef STA_TIME
    double inicio, end, tiempo;
  #endif // STA_TIME
  int i, j;
  printf("SERIAL\n");
  printf("~>Iniciando Variaveis...\n");
  for (i = 0; i <= n; i++) {
    num[i] = i;
  }

  printf("~>Variaveis Iniciaizadas...\n");
  printf("~>Iniciando Buscas de Primos...\n");

  #ifdef STA_TIME
    inicio = omp_get_wtime();
  #endif
  num[0]=-1;
  num[1]=-1;
  for(int i = 2; i < n; i++){
    if(num[i]!=-1)
      for(int j=i+i; j<=n; j+=i){
        if(num[j]%i==0){
          if(num[j] != -1){
            totalPrimos--;
          }
          num[j] = -1;
        }
      }
  }
  #ifdef OUTPUT
    for(i = 2; i < n; i++){
      if(num[i]!=-1){
        printf("%d ", i);
      }
    }
  #endif // OUTPUT
  #ifdef STA_TIME
    end = omp_get_wtime();
    tiempo = end-inicio;
    printf("\n~>Tempo Inicial: %f\n",inicio);
    printf("~>Tempo Final: %f\n",end);
    printf("~>Tempo: %f\n", tiempo);
  #endif

  printf("~>Busca Concluida\n");
  printf("~>%d Primos Encrontados", totalPrimos);
  return 0;
}
