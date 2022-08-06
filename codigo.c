#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insercao(int n, int * v1, int *v2)
{
	for (int j = 1; j < n; ++j) {
      int x = *(v1 + j);
      int y = *(v2 + j);
      int i;
      for (i = j-1; i >= 0 && *(v1 + i) > x; --i){
        *(v1 + i + 1) = *(v1+i);
        *(v2 + i + 1) = *(v2+i);
        }
      *(v1 + i + 1) = x;
      *(v2 + i + 1) = y;
   }
   
}

int main(){
    FILE * arquivo1 = fopen("revisão.txt", "r");
    FILE * arquivo2 = fopen("ordenação.txt", "w+");
    int dia, mes, ano, rating;
    int *v1, *v2;
    int i = 0;
    
    while (1)
    {
        if(fscanf(arquivo1, "%d-%d-%d-%d", &ano, &mes, &dia, &rating) == EOF){break;}
        i++;
    }
    v1 = (int*)calloc(i, sizeof(int));
    v2 = (int*)calloc(i, sizeof(int));
    fseek(arquivo1,0,SEEK_SET);
    i = 0;
    while (1)
    {
        if(fscanf(arquivo1, "%d-%d-%d-%d", &ano, v2+i, &dia, v1+i) == EOF){break;}
        //printf("%d-%d-%d\n",i+1,*(v2+i), *(v1+i));
        i++;
    }
    insercao(i+1,v2,v1);
    for (int k = 0; k < i+1; k++)
    {
        fprintf(arquivo2,"%d-%d\n",*(v1+k),*(v2+k));
    }
    
    free(v1);
    free(v2);
    fclose(arquivo1);
    fclose(arquivo2);
    return 0;
}