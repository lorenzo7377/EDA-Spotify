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
    insercao(i+1,VetorMes,VetorNotas);
    // for (int j = 0; j < i; j++)
    // {
    //     printf("%d - %d\n", *(VetorMes+j), *(VetorNotas+j));
    // }
    
    double soma;
    int posicao = 1;
    double contador;
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
        printf("Média do mês %d: %.2lf\n", j, soma / contador);

    }
    
    
    free(VetorNotas);
    free(VetorMes);
    fclose(arquivo1);

    return 0;
}