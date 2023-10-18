#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define QTD_SORT 3 // quantidade de tipos de ordenação
#define QTD_AMOS 4 // quantidade de tipos de amostra

long long int atribuicao = 0, compara = 0;

typedef struct{
    char tipo_ordenacao[30];
    long long int atribuicao, compara;
}ORDENACAO;

typedef struct{
    char tipo_amostra[150];
    ORDENACAO ordenacao[QTD_SORT];
}AMOSTRA;

typedef struct{
    int num_teste;
    AMOSTRA amostra[QTD_AMOS];
}RESULTADO;

void bubble(RESULTADO *, int, int, int *, int);
void insertion(RESULTADO *, int, int, int *, int);
void selection(RESULTADO *, int, int, int *, int);
void gera_aleatorio(RESULTADO *, int, int, int **, int);
void gera_invertido(RESULTADO *, int, int, int **, int);
void gera_quase_ordenado(RESULTADO *, int, int, int **, int);
void gera_com_repeticoes(RESULTADO *, int, int, int **, int);
void ordenar(RESULTADO *, int, int, int **, int);
void gravar_amostra(RESULTADO *, int, int, char *);
void exibe(RESULTADO *, int);
void escreverArquivo(char *, RESULTADO *, int);

int main(){
    int **v;
    int n, i, qtd_teste = 0;
    RESULTADO *resultado;
    //inicializando o gerador pseudo-randomico
    srand(time(0));
    printf("Digite a quantidade de testes que deseja realizar: ");
    scanf("%d", &qtd_teste);
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);
    
    resultado = (RESULTADO *) malloc (qtd_teste*sizeof(RESULTADO));

    for(i=0;i<qtd_teste;i++){
        //alocar a matriz dinamicamente
        v = (int **) malloc (QTD_SORT*sizeof(int)); 
        for(int j=0;j<QTD_SORT;j++){
            v[j] = (int *) malloc (n*sizeof(int));
        }

        resultado[i].num_teste = i+1;  
        
        int k = 0;
        gera_aleatorio(resultado, i, k,v,n);
        ordenar(resultado, i, k, v ,n);
        k++;

        gera_invertido(resultado, i, k,v,n);
        ordenar(resultado, i, k, v ,n);
        k++;
              
        gera_quase_ordenado(resultado, i, k,v,n);
        ordenar(resultado, i, k, v ,n);
        k++;
                   
        gera_com_repeticoes(resultado, i, k,v,n);
        ordenar(resultado, i, k, v ,n);

        free (v);
    }
    exibe(resultado, qtd_teste);
    escreverArquivo("ordenacao.csv",resultado,qtd_teste);
    free (resultado);
    return 0;
}

void bubble(RESULTADO * resultado, int num_teste, int num_amostra, int *v, int n){
    int i, j, aux;
    for(i=1;i<n;i++){
        for(j=0;j<n-i;j++){
            compara ++;        
            if(v[j]>v[j+1]){
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
                atribuicao += 3;
            }
        }
    }
    strcpy(resultado[num_teste].amostra[num_amostra].ordenacao[0].tipo_ordenacao,"BUBBLE");
    resultado[num_teste].amostra[num_amostra].ordenacao[0].atribuicao = atribuicao;
    resultado[num_teste].amostra[num_amostra].ordenacao[0].compara = compara;
    atribuicao = 0;
    compara = 0;
}
void insertion(RESULTADO * resultado, int num_teste, int num_amostra, int *v, int n){
    int i, j, k,  x;
    for (i=1; i<n; i++){
        x = v[i];
        atribuicao++;
        for(j=i-1;j>=0 && v[j]>x; j--){
            compara ++;
            v[j+1] = v[j];
            atribuicao++;
        }
        v[j+1] = x;
        atribuicao++;
    }
    strcpy(resultado[num_teste].amostra[num_amostra].ordenacao[1].tipo_ordenacao,"INSERTION");
    resultado[num_teste].amostra[num_amostra].ordenacao[1].atribuicao = atribuicao;
    resultado[num_teste].amostra[num_amostra].ordenacao[1].compara = compara;
    atribuicao = 0;
    compara = 0;
}
void selection(RESULTADO * resultado, int num_teste, int num_amostra, int *v, int n){
    int i, j, k, min, x;
    long long int atribuicao=0, compara=0;
    for(i=0;i<n-1;i++){
        min = i;
        for(j=i+1;j<n;j++){
            compara ++;
            if(v[j]<v[min]){
                min = j;
            }
        }
        x = v[i];
        v[i] = v[min];
        v[min] = x;
        atribuicao += 3;
    }
    strcpy(resultado[num_teste].amostra[num_amostra].ordenacao[2].tipo_ordenacao,"SELECTION");
    resultado[num_teste].amostra[num_amostra].ordenacao[2].atribuicao = atribuicao;
    resultado[num_teste].amostra[num_amostra].ordenacao[2].compara = compara;
    atribuicao = 0;
    compara = 0;
}
void gera_aleatorio(RESULTADO * resultado, int l, int m, int **v, int n){
    int i;
    for(i=0; i<n; i++){
        v[0][i] = rand()%(n*10);
    }
    for (int j=1; j<QTD_SORT; j++){
        for(i=0; i<n; i++){
            v[j][i] = v[j-1][i];
        }
    }
    gravar_amostra(resultado, l, m,"AMOSTRA COM NUMEROS ALEATORIOS");
}
void gera_invertido(RESULTADO * resultado, int l, int m, int **v, int n){
    int i, j,k, min, x;
    gera_aleatorio(resultado, l, m, v, n);
    for(k=0;k<QTD_SORT;k++){
        for(i=0;i<n-1;i++){
            min = i;
            for(j=i+1;j<n;j++){
                if(v[k][j]>v[k][min]){
                    min = j;
                }
            }
            x = v[k][i];
            v[k][i] = v[k][min];
            v[k][min] = x;
        }
    }
    gravar_amostra(resultado, l, m,"AMOSTRA COM NUMEROS ORDENADOS DECRESCENTE");
}
void gera_quase_ordenado(RESULTADO * resultado, int l, int m, int **v, int n){
    gera_aleatorio(resultado, l, m,v,n);
    int i, j, k, aux = 0;
    for(k=0;k<QTD_SORT;k++){
        for(i=1;i<n;i++){
            for(j=0;j<n-i;j++){       
                if(v[k][j]>v[k][j+1]){
                    aux = v[k][j];
                    v[k][j] = v[k][j+1];
                    v[k][j+1] = aux;
                }
            }
        }
    }
    j = 1;
    while (j<= n*0.1){
        i = rand()%n;
        v[0][i] = rand()%(n*10);
        for(k=1;k<QTD_SORT;k++){
            v[k][i] = v[k-1][i];
        }
        j++; 
    }
    gravar_amostra(resultado, l, m,"AMOSTRA COM NUMEROS QUASE ORDENADOS"); 
}
void gera_com_repeticoes(RESULTADO * resultado, int l, int m, int **v, int n){
    int i, j;
    for(i=0; i<n; i++){
        v[0][i] = rand()%(n/2);
    }
    for (j=1; j<QTD_SORT; j++){
        for(i=0; i<n; i++){
            v[j][i] = v[j-1][i];
        }
    }
    gravar_amostra(resultado, l, m,"AMOSTRA COM NUMEROS REPETIDOS");   
}
void ordenar(RESULTADO * resultado, int num_teste, int num_amostra, int **v, int n){
        bubble (resultado,num_teste, num_amostra, v[0],n);
        insertion (resultado,num_teste,  num_amostra, v[1],n);
        selection (resultado,num_teste, num_amostra, v[2],n);
}
void gravar_amostra(RESULTADO * resultado, int i, int k , char * amostra){
    strcpy(resultado[i].amostra[k].tipo_amostra, amostra);
}
void exibe(RESULTADO *resultado, int qtd_teste){
    for(int i=0;i<qtd_teste;i++){
        printf("TESTE N %d\n\n", resultado[i].num_teste);
        for(int j=0; j<QTD_AMOS;j++){
           printf("%s\n", resultado[i].amostra[j].tipo_amostra);
           for(int k=0; k<QTD_SORT; k++){
                printf("%s    ", resultado[i].amostra[j].ordenacao[k].tipo_ordenacao);
                printf("-> comparacoes = %10lld ", resultado[i].amostra[j].ordenacao[k].compara);
                printf("- atribuicoes = %10lld\n", resultado[i].amostra[j].ordenacao[k].atribuicao);
           }
           printf("\n"); 
        }
        printf("\n"); 
    }
}
void escreverArquivo(char * nome_arquivo,RESULTADO * resultado, int qtd_teste){
    FILE *fp;
    fp = fopen(nome_arquivo,"w");
    if(!fp){
        printf( "\nErro na abertura do arquivo\n\n");
        exit(-1);
    }
    for(int i=0;i<qtd_teste;i++){
        
        fprintf(fp,"TESTE Nº%d\n\n", resultado[i].num_teste);
        for(int j=0; j<QTD_AMOS;j++){
           fprintf(fp,"%s\n", resultado[i].amostra[j].tipo_amostra);
           for(int k=0; k<QTD_SORT; k++){
                fprintf(fp,"%s,", resultado[i].amostra[j].ordenacao[k].tipo_ordenacao);
                fprintf(fp,"comparações,%lld,", resultado[i].amostra[j].ordenacao[k].compara);
                fprintf(fp,"atribuições,%lld\n", resultado[i].amostra[j].ordenacao[k].atribuicao);
           }
           fprintf(fp,"\n"); 
        }
        fprintf(fp,"\n"); 
    }
    fclose(fp);
}