#include <stdio.h>
#include <stdlib.h>
#define N 250

struct Pilha{
    int run[N];
};
struct Pilha P[N];


void intercala(int *vetor, int posicao, int inicio, int meio, int fim){

    int *aux = malloc(N * sizeof(int));
    int in, comeco1, comeco2;

    in = inicio;
    comeco1 = inicio;
    comeco2 = inicio;

    while(comeco1 < meio && comeco2 < fim){
        if(P[posicao-1].run[comeco1] < P[posicao].run[comeco2]){
            aux[in] = P[posicao-1].run[comeco1];
            comeco1++;
            in++;
        }
        else {
            aux[in] = P[posicao].run[comeco2];
            comeco2++;
            in++;
        }
    }
    while(comeco1 < meio){
        aux[in] = P[posicao-1].run[comeco1];
        comeco1++;
        in++;
    }
    while(comeco2 < fim){
        aux[in] = P[posicao].run[comeco2];
        comeco2++;
        in++;
    }

    for(int i = inicio; i < (meio+meio); i++)
        vetor[i] = aux[i];


    for(int i = inicio; i < (meio+meio); i++)
        printf("| %d ", vetor[i]);
    printf("\n");

    free(aux);
}


void insertion_sort(int posicao, int n){

  int i, j, atual;

  for(i = 1; i < n; i++){
      atual = P[posicao].run[i];

      for(j = i - 1; (j >= 0) && (P[posicao].run[j] > atual); j--)
          P[posicao].run[j+1] = P[posicao].run[j];

      P[posicao].run[j+1] = atual;
  }

}


int define_minrun(){

    int r = 0;
    int n = N;

    while(n >= 64){
        r |= n & 1;
        n >>= 1;
    }

    return n + r;
}

void timsort(int *vetor){

    int i, j, MinRun, indice_atual = 0;

    j = 0;
    MinRun = define_minrun();

    //O indice_atual irá percorrer cada elemento do vetor.
    while(indice_atual < N){

      if((indice_atual + MinRun) > N){
          MinRun = N - indice_atual;
      }

      for(i = 0; i < MinRun; i++){
          P[j].run[i] = vetor[indice_atual];
          indice_atual++;
      }

      //Ordenando as run's com o insertion sort.
      insertion_sort(j, MinRun);

      for(i = 0; i < MinRun; i++){
          printf("| %d ", P[j].run[i]);
      }
      printf("|\n");

      //Verifica se há duas run's para realizar o merge.
      if(j % 2 != 0){
          printf("Realizando o merge:\n");
          intercala(vetor, j, 0, MinRun, MinRun);
      }

      j++;

    }

}


int main(){

  int *vetor = malloc(N * sizeof(int));


  for(int i = 0; i < N; i++)
    vetor[i] = N - i;

  // printf("Vetor original:\n");
  // for(int i = 1; i <= N; i++)
  //       printf("%d ", vetor[i - 1]);
  // printf("\n\n");

  //Teste para os algoritmos de ordenação
  //insertion_sort(vetor);
  //mergesort(vetor);


  printf("Valor do Minrun: %d\n", define_minrun());
  timsort(vetor);


  // printf("Vetor apos ordenacao:\n");
  // for(int i = 1; i <= N; i++)
  //     printf("%d ", vetor[i - 1]);
  // printf("\n\n");

  printf("\n");
  for(int i = 0; i < N; i++)
    printf("| %d ", vetor[i]);

  free(vetor);

  return(0);
}
