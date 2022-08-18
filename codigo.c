#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insercao(int n, int * VetorNotas, int *VetorMes)
{
	for (int j = 1; j < n; ++j) {
      int x = *(VetorNotas + j);
      int y = *(VetorMes + j);
      int i;
      for (i = j-1; i >= 0 && *(VetorNotas + i) > x; --i){
        *(VetorNotas + i + 1) = *(VetorNotas+i);
        *(VetorMes + i + 1) = *(VetorMes+i);
        }
      *(VetorNotas + i + 1) = x;
      *(VetorMes + i + 1) = y;
   }
   
}

int main(){
    FILE * arquivo1 = fopen("revisão.txt", "r");
    int d, mes, ano, Notas;
    int *VetorNotas, *VetorMes;
    int i = 0;
    
    while (1)
    {
        if(fscanf(arquivo1, "%d-%d-%d-%d", &ano, &mes, &d, &Notas) == EOF){break;}
        i++;
    }
    VetorNotas = (int*)calloc(i, sizeof(int));
    VetorMes = (int*)calloc(i, sizeof(int));
    fseek(arquivo1,0,SEEK_SET);
    i = 0;
    while (1)
    {
        if(fscanf(arquivo1, "%d-%d-%d-%d", &ano, VetorMes+i, &d, VetorNotas+i) == EOF){break;}
        i++;
    }
    clock_t inicio2, fim2;
    inicio2 = clock();
    insercao(i+1,VetorMes,VetorNotas);
    fim2 = clock();

    double tempo2 = (double)(fim2 - inicio2) / CLOCKS_PER_SEC;
    clock_t inicio, fim;
    double tempo;
    double soma;
    int posicao = 1;
    double contador;
    inicio = clock();
    FILE *ponteiro = fopen("medias.csv","w+");
    fprintf(ponteiro,"Mes,Avaliação_Média\n");
    for (int j = 1; j <= 7; j++)
    {
        soma = 0;
        contador = 0;
        for (int k = posicao; k < i + 1; k++)
        {
            if (*(VetorMes+k) == j){
                soma += *(VetorNotas+k);
                contador++;
                }
            else
            {
                posicao = k;
                break;
            }
        }
        fprintf(ponteiro,"2022_0%d,%.2lf\n", j, soma / contador);

    }
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("média - %lf segundos\n", tempo);
    printf("ordenação - %lf segundos\n", tempo2);
    free(VetorNotas);
    free(VetorMes);
    fclose(arquivo1);
    fclose(ponteiro);
    return 0;
}