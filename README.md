
## CRIVO DE ERATÓSTENES 
_Projeto referente a cadeira do curso de ciência da computação da UFCA (CC0021 - Programação Concorrente)_

O crivo de eratóstenes é um método utilizado para se encontrar números primos entre 0 e um número qualquer (em todas as execuções realizadas o número que será adotado será o 10.000.000).

**Passos:**

 -  Liste todos os números de 2 até um limite estabelecido.
 - Marque todo número múltiplo do número 2 (4, 6, 8, ...).
 - Repita o procedimento com todos os números não marcados.
 - Ao percorrer todos os números do intervalo ([2,n]), tem-se que todos os números marcados são compostos e todos os números não marcados são primos.

## Repositório do Github/BitBucket/GitLab a ser utilizado

Será utilizado o github para hospedar o código fonte e arquivos, o [link do repositório](https://github.com/TrabalhosCC-Gilvan-e-Renann/crivo-de-eratostenes)

## Recursos Computacionais que serão utilizados

| Notebook Acer | Notebook Acer |
| ------ | ------ |
| Intel(R) Core(TM) i3-8130U CPU @ 2.20GHz 2.21 GHz | Intel(R) Core(TM) i3-7020U CPU @ 2.30GHz |
| RAM: 4,00 GB | RAM: 11,6 GB |
| Windows 64 bits | Ubuntu 21.04 64 bits |
| Dev C++ | CodeBlocks|

## Descrição dos algoritmos que serão implementados

 1. Aspectos Comuns em Todos os Algoritmos
-   Foi utilizado uma alocação na memória de tamanho 10.000.001(* tamanho de um int) onde cada um dos seus 10.000.001 representa os números naturais de 0 até 10.000.000. Onde caso um elemento tenha valor -1 isto implica da respectiva posição não é primo, caso contrário ou o número da posição é primo ou não foi avaliado.
-   É considerado um número marcado como aquele cuja posição no espaço alocado possui valor igual a -1.
-   A partir do 2 até 5.000.000 todos os número que são múltiplos de outros são marcados.
-   Se um número já tiver sido marcado, este não marca seus múltiplos.
-   O tempo de cada algoritmo é medido a partir do momento em que a verificação se o número 2 é primo ou não, até o último elemento do intervalo. Tal ação é feita pela função omp_get_wtime(), presente na biblioteca OMP.
    
2.   Aspectos do Algoritmo Serial 1
-   Tal algoritmo utiliza apenas as configurações citadas acima.

3.   Aspectos do Algoritmo Paralelo Utilizando Threads
-   O algoritmo tido como base para este foi o mesmo utilizado no item anterior, onde as mudanças realizadas são citadas nos próximos subitens.
-   Tal algoritmo utiliza a biblioteca OMP, a qual possibilita a criação de threads, onde serão criadas 4 threads (uma para cada núcleo dos computadores).
-   Tais threads criados tem o intuito de subdividir o procedimento de marcação de números múltiplos de outros.
-   Os comandos utilizados para tais ações são: ‘pragma omp parallel num_threads(4)’ e ‘pragma omp for’.
    

4.  Aspectos do Algoritmo Paralelo Utilizando MPI
-   O algoritmo tido como base para este foi o mesmo utilizado no item anterior, onde as mudanças realizadas são citadas nos próximos subitens.
-   Tal algoritmo utiliza a biblioteca Open MPI, o qual trabalha com memória distribuída e compartilhada, onde serão separadas em 4 processos(um para cada núcleo dos computadores).
-   Teremos a inicialização no processo principal e teremos que será quebrado em outros 3 processos e serão realizados os cálculos referentes ao crivo de eratóstenes.
-   Os comandos utilizados para tais ações são ‘MPI_Init’,’MPI_Comm_rank’, ’MPI_Comm_size’,‘MPI_Bcast’, ‘MPI_Finalize’ e ‘MPI_Wtime()’.
   
5. Aspectos do Algoritmo Serial Utilizando MPI
-   Tal algoritmo usa o mesmo código que o anterior, entretanto com apenas 1 processo.
-   Teoricamente este é o mesmo algoritmo que o anterior (só separamos para questões de análise).
-   Esta aplicação é realizada, pois não é justo aplicar o algoritmo serial anterior com um paralelo que usa MPI, já que usam compiladores diferentes.

## Descrição de como será apresentado a análise de desempenho

A análise de desempenho será realizada após a execução dos 3 algoritmos anteriores (Serial, Serial utilizando MPI Paralelo utilizando Threads, Paralelo utilizando MPI) na linguagem de programação C, teremos que cada algoritmo será executada no total de 5 vezes e após terminarmos a execução dos algoritmos, será realizado uma análise do tempo médio de cada um, o seu desvio padrão, o speedup para os algoritmos paralelas e sua eficiência.

A análise de desempenho será realizada após a execução dos 3 algoritmos anteriores (Serial, Serial utilizando MPI Paralelo utilizando Threads, Paralelo utilizando MPI) na linguagem de programação C, teremos que cada algoritmo será executada no total de 5 vezes e após terminarmos a execução dos algoritmos, será realizado uma análise do tempo médio de cada um, o seu desvio padrão, o speedup para os algoritmos paralelas e sua eficiência.
