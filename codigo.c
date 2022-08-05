#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insercao(int n, int * v)
{
	for (int j = 1; j < n; ++j) {
      int x = *(v + j);
      int i;
      for (i = j-1; i >= 0 && *(v + i) > x; --i){*(v + i + 1) = *(v+i);}
      *(v + i + 1) = x;
   }
   
}

int main(){
    FILE * arquivo1 = fopen("revisão.txt", "r");
    int dia, mes, ano, rating;
    int *v;
    int i = 1;
    
    while (1)
    {
        if(fscanf(arquivo1, "%d-%d-%d-%d", &ano, &mes, &dia, &rating) == EOF){break;}
        i++;
    }
    v = (int*)calloc(i, sizeof(int));
    fseek(arquivo1,0,SEEK_SET);
    i = 1;
    while (1)
    {
        if(fscanf(arquivo1, "%d-%d-%d-%d", &ano, &mes, &dia, v+i) == EOF){break;}
        printf("%d-%d\n",i, *(v+i));
        i++;
    }
    fclose(arquivo1);
    return 0;
}