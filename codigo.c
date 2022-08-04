#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insercao(int n, int * v)
{
	for (int j = 1; j < n; ++j) {
      int x = *(v + j);
      int i;
      for (i = j-1; i >= 0 && *(v + i) > x; --i){*(v + i + 1) = *(v+i);}// COMANDO A SER CONTABILIZADO
      *(v + i + 1) = x;
   }
   
}

int main(){
    FILE * arquivo1 = fopen("revisão.txt", "r");
    FILE * arquivo2;
    FILE * arquivo3;
    int dia, mes, ano, rating;
    while (1)
    {
        if(fscanf(arquivo1, "%d-%d-%d-%d", &ano, &mes, &dia, &rating) == EOF){break;}
    }
    
    return 0;
}