#ifdef aktin
    totalPrimos = 2;
    for(int i = 0; i < n+1; i++){
        primo[i] = FALSE;
    }
    printf("Variaveis Iniciaizadas...\n");
    printf("Iniciando Buscas de Primos...\n");

    #ifdef STA_TIME
      double inicio, end, tempo;
      inicio = omp_get_num_threads();
    #endif

    for(int x = 1; x * x < n; x++) {
      for(int y = 1; y * y < n; y++) {
        int entry_number = (4 * x * x) + (y * y);
        if (entry_number <= n && (entry_number % 12 == 1 || entry_number % 12 == 5)){
          primo[entry_number] = TRUE;
          totalPrimos++;
        }
        entry_number = (3 * x * x) + (y * y);
        if (entry_number <= n && entry_number % 12 == 7){
          primo[entry_number] = TRUE;
          totalPrimos++;
        }
        entry_number = (3 * x * x) - (y * y);
        if (x > y && entry_number <= n && entry_number % 12 == 11){
          primo[entry_number] = TRUE;
          totalPrimos++;
        }
      }
    }

    for(int r = 5; r * r < n; r++) {
      if(primo[r]) {
        for(int i = r * r; i < n; i += r * r)
          primo[i] = FALSE;
          totalPrimos--;
        }
    }
    primo[2]=TRUE;
    primo[3]=TRUE;
    #ifdef STA_TIME
      end = omp_get_wtime();
      tempo = end-inicio;
      printf("Tempo para executar o crivo: %f\n", (float)tempo);
    #endif
    printf("Busca Concluida\n");
    printf("%d Primos Encrontados\n", totalPrimos);

    #ifdef OUTPUT
      for (int i = 2; i < n; i++){
        if (primo[i]){
          printf("%d ", i);
        }
      }
    #endif

  #endif
