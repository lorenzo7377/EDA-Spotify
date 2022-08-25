#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*parte que ordena o vetor "V1" de acordo com o modo de insertionSort e, ao mesmo tempo, organiza o vetor "V2"
para que não se perca a relação entre os dois. Então, se uma das notas foi 1 no mês de março, assim que o valor "3" for ordenado,
o valor "1" vai mudar para o mesmo índice, voltando a conectar os dois dados.*/
void insercao(int n, int * V1, int *V2)
{
	for (int j = 1; j < n; ++j) {
      int x = *(V1 + j);
      int y = *(V2 + j);
      int i;
      for (i = j-1; i >= 0 && *(V1 + i) > x; --i){
        *(V1 + i + 1) = *(V1+i);
        *(V2 + i + 1) = *(V2+i);
        }
      *(V1 + i + 1) = x;
      *(V2 + i + 1) = y;
   }
   
}

int main(){
    FILE * arquivo1 = fopen("revisão.txt", "r");
    int d, mes, ano, Notas;
    int *VetorNotas, *VetorMes;
    int i = 0;
    /*Leitura do arquivo revisão.txt, onde está todas as colunas válidas, contando a quantidade de linhas*/
    while (1)
    {
        if(fscanf(arquivo1, "%d-%d-%d-%d", &ano, &mes, &d, &Notas) == EOF){break;}
        i++;
    }
    //agora são alocadas as memórias dos ponteiros/vetores, usando o número de linhas como a quantidade de inteiros a serem guardados.
    VetorNotas = (int*)calloc(i, sizeof(int));
    VetorMes = (int*)calloc(i, sizeof(int));
    //Cursor colocado para o início do arquivo
    fseek(arquivo1,0,SEEK_SET);
    i = 0;
    while (1)
    {
        //aqui, "i" serve apenas para deslocar os índices dos ponteiros
        if(fscanf(arquivo1, "%d-%d-%d-%d", &ano, VetorMes+i, &d, VetorNotas+i) == EOF){break;}
        i++;
    }
    clock_t inicio2, fim2;
    inicio2 = clock();
    
    insercao(i,VetorMes,VetorNotas);//chamada do insertionSort, ordenando o vetor de mêses, e o vetor de notas acompanha
    fim2 = clock();

    double tempo2 = (double)(fim2 - inicio2) / CLOCKS_PER_SEC;// Cálculo do tempo para ordenar os vetores
    clock_t inicio, fim;
    double tempo;
    double soma;
    int posicao = 0;
    double contador;
    inicio = clock();
    FILE *ponteiro = fopen("medias.csv","w+");// Criação do arquivo para as médias
    fprintf(ponteiro,"Mes,Avaliação_Média\n");

    int vetormediames[7] = {1,2,3,4,5,6,7};//esse vetor só existe pra facilitar o processo de escrever os meses
    float media[7];//Esse vetor serve apenas para armazenar as médias dos mêses
    for (int j = 0; j < 7; j++)
    {
        soma = 0;
        contador = 0;//esse contador apenas conta quantas médias no mês
        for (int k = posicao; k < i; k++)
        {
            if (*(VetorMes+k) == j + 1){
                soma += *(VetorNotas+k);//caso o valor do mês seja igual ao valor de j, some
                contador++;
                }
            else
            {
                posicao = k;//caso não seja, porque estamos em outro mês, saímos e guardamos a posição onde paramos
                break;
            }
        }
        media[j] = soma / contador; //Por fim, é guardado o valor da média
    }
    //note que existe um aviso nessa linha pois está sendo enviado um vetor de números reais no lugar de um para inteiros.
    insercao(7, media, vetormediames);//ordenação das médias e os mêses acompanham
    fim = clock();// Cálculo do tempo para calcular as médias e ordená-las
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    for (int k = 6; k >= 0; k--)
    {
        //Como as médias devem estar em ordem decrescente, são escritas da última para a primeira
        fprintf(ponteiro,"2022_0%d;%.2lf\n", vetormediames[k], media[k]);
        /*Por padrão, Floats tem as casas decimais após ".", mas para tratar as médias como números na planilha,
        os pontos devem ser trocados por vírgulas*/
    }
    
    
    printf("média - %lf segundos\n", tempo);
    printf("ordenação - %lf segundos\n", tempo2);
    free(VetorNotas);
    free(VetorMes);
    fclose(arquivo1);
    fclose(ponteiro);
    return 0;
}