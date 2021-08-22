#include <stdio.h>
#include <stdlib.h>
#include <mpi/mpi.h>

#define TRUE 1
#define FALSE 0

#define STA_TIME TRUE
//#define OUTPUT TRUE

int main(int argc, char **argv) {
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n = 10000000;
    int subTam = (int) n / nprocs;
    int *num = malloc((n) * sizeof(int));
    int *subvetor = NULL;
    int totalPrimos = n - 2;
    double h;

    //MPI
#ifdef STA_TIME
    double inicio, end, tiempo;
#endif // STA_TIME
    int i, j;
    if (rank == 0) {
        printf("CRIVO COM MPI com %d Processo(s)\n", nprocs);
        printf("~>Iniciando Variaveis...\n");

        for (i = 0; i < n; i++) num[i] = i;

        printf("~>Variaveis Iniciaizadas...\n");
        printf("~>Iniciando Buscas de Primos...\n");
    }

#ifdef STA_TIME
    inicio = MPI_Wtime();
#endif
    num[0] = -1;
    num[1] = -1;
    subvetor = malloc((subTam) * sizeof(int));
    MPI_Scatter(num, subTam, MPI_INT, subvetor, subTam, MPI_INT, 0, MPI_COMM_WORLD);

    int primosIntervalo = 0;
    int acc = 0;
    for (int i = 2; i < subTam; i++) {
        if (subvetor[i] != -1 || rank!=0) {
           for (j= rank == 0 ? i + i : 0; j < subTam; j += i) {
              if(subvetor[0] != -1) acc = subvetor[0];
                if (subvetor[j] % i == 0) {
                    if (subvetor[j] != -1) {
                        primosIntervalo++;
                    }
                    subvetor[j] = -1;
                }
                if(j == 0 && acc%i != 0) j -= (int)(acc%i);
            }
        }
    }

#ifdef OUTPUT
    for(int i = 2; i < n/2+1; i++){
        if(num[j]!=-1){
            printf("%d ", i);
        }
    }
#endif // OUTPUT

    int *resultados = NULL;
    if (rank == 0) resultados = malloc(nprocs * sizeof(int));
    MPI_Gather(&primosIntervalo, 1, MPI_INT, resultados, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (i = 0; i < nprocs; i++) totalPrimos -= resultados[i];

#ifdef STA_TIME
        end = MPI_Wtime();
        tiempo = end - inicio;
        printf("\n~>Tempo Inicial: %f\n", inicio);
        printf("~>Tempo Final: %f\n", end);
        printf("~>Tempo: %f\n", tiempo);
#endif
        printf("~>Busca Concluida\n");
        printf("~>%d Primos Encontrados", totalPrimos);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}