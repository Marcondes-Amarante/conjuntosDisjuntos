#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "bubbleSort.h"
#include "insertionSort.h"
#include "quickSort.h"
#include "mergeSort.h"

//declaração de struct para conjunto disjunto
typedef struct{
	int *pais; 			//array para os pais de cada subconjunto
	int *ranks;			//array para os ranks
	int **subconjuntos;	//matriz para armazenar valores de subconjuntos 		 
	int tam; 			//tamanho do conjunto
	int qtdSubconjuntos;//quantidade de subconjunto agrupados na estrutura
}ConjuntosDisjuntos;


void inicializarConjuntosDisjuntos(ConjuntosDisjuntos **conjunto, int capacidade, int qtdSubs){
	*conjunto = (ConjuntosDisjuntos *)malloc(sizeof(ConjuntosDisjuntos));
	
	(*conjunto)->pais = (int *)malloc(capacidade * sizeof(int));
	(*conjunto)->ranks = (int *)malloc(capacidade * sizeof(int));
	
	//alocando linhas para matriz de subconjuntos; cada linha representa os valores de um subConjunto da partição
	(*conjunto)->subconjuntos = (int **)malloc(qtdSubs * sizeof(int));
	(*conjunto)->qtdSubconjuntos = qtdSubs;
	
	//alocando colunas para linhas da matriz de acordo com a capacidade do vetor
	for(int i=0; i<qtdSubs; i++){
		(*conjunto)->subconjuntos[i] = (int *)malloc(capacidade * sizeof(int));
	}
	
	//alocando colunas
	
	//inicializando todos os elementos como seus próprios pais e com respectivo rank igual a 0
	for(int i=0; i<capacidade; i++){
		(*conjunto)->pais[i]=i;
		(*conjunto)->ranks[i]=0;
	}
}

int encontrarRepresentante(ConjuntosDisjuntos *conjunto, int elemento){
	
	//verificamos se o pai do elemento repassado é diferente de si próprio, pois caso contrário não é necessário alterações basta retorna-lo
	if(conjunto->pais[elemento] != elemento){
		
		//caso pai do elemento seja diferente dele, chamamos recursivamente a função até que ambos seja iguais, ou seja, encontremos seu representante
		conjunto->pais[elemento] = encontrarRepresentante(conjunto, conjunto->pais[elemento]);
	}
	
	return conjunto->pais[elemento];	
}

void exibirSubconjuntosPorRepComun(ConjuntosDisjuntos *conjunto, int elem, int n){
	
	printf("subconjunto contendo %d: {", elem);
	
	int representante = encontrarRepresentante(conjunto, elem);
	
	for(int i=1; i<=n; i++){
		if(encontrarRepresentante(conjunto, i) == representante){
			printf("%d, ", i);
		}
	}
	
	printf("}\n");
}

int retornarIndiceSubconjunto(ConjuntosDisjuntos *conjunto, int elem){
	
	int indiceSubconjunto;
	
	for(int i=0; i < conjunto->qtdSubconjuntos; i++){
		for(int j=0; j < conjunto->subconjuntos[i][0]; j++){
			if(conjunto->subconjuntos[i][j] == elem){
				indiceSubconjunto = i;
			}
		}
	}
	
	return indiceSubconjunto;
}

void exibirVetoresSubconjuntos(ConjuntosDisjuntos *conjunto){
	
	for(int i=0; i < conjunto->qtdSubconjuntos; i++){
		printf("subconjunto vetor %d: ", i);
		for(int j=1; j < conjunto->subconjuntos[i][0]; j++){
			printf("%d, ", conjunto->subconjuntos[i][j]);
		}
		printf("\n");
	}
		
}


void unirVetoresSubconjuntos(ConjuntosDisjuntos *conjunto, int elem1, int elem2){
	
	int indiceSubconjunto1 = retornarIndiceSubconjunto(conjunto, elem1);
	int indiceSubconjunto2 = retornarIndiceSubconjunto(conjunto, elem2);
	
	if(indiceSubconjunto1 == indiceSubconjunto2){
		printf("os elementos já se encontram no mesmo subconjunto");
	}
	
	int tamElemSubconjuntos = conjunto->subconjuntos[indiceSubconjunto1][0] + conjunto->subconjuntos[indiceSubconjunto2][0];
	
	
	//se elemento 1 possuir representante com maior rank copiar todos os elementos de 2 para 1
	
	//se elemento 2 possuir representante com maior rank copiar todos os elementos de 1 para 2
	
	//se ambos possuirem mesmo rank copiar todos os elementos de 2 para 1
	
	int repElem1 = encontrarRepresentante(conjunto, elem1);
	int repElem2 = encontrarRepresentante(conjunto, elem2);
	
	int maior;
	int menor;
	
	if(conjunto->ranks[repElem1] > conjunto->ranks[repElem2] || conjunto->ranks[repElem1] == conjunto->ranks[repElem2]){
		maior = indiceSubconjunto1;
		menor = indiceSubconjunto2;
	}else if(conjunto->ranks[repElem1] < conjunto->ranks[repElem2]){
		maior = indiceSubconjunto2;
		menor = indiceSubconjunto1;
	}
	
	// Copiar elementos do menor para o maior
    int tamMaior = conjunto->subconjuntos[maior][0];
    int tamMenor = conjunto->subconjuntos[menor][0];

    for (int i = 1; i < tamMenor; i++) {
        conjunto->subconjuntos[maior][tamMaior++] = conjunto->subconjuntos[menor][i];
    }

    // Atualizar o tamanho do subconjunto maior
    conjunto->subconjuntos[maior][0] = tamMaior;

    // Liberar memória do subconjunto menor
    free(conjunto->subconjuntos[menor]);

    // Reorganizar a matriz de subconjuntos para preencher o espaço
    for (int i = menor; i < conjunto->qtdSubconjuntos - 1; i++) {
        conjunto->subconjuntos[i] = conjunto->subconjuntos[i + 1];
    }

    // Decrementar a quantidade de subconjuntos
    conjunto->qtdSubconjuntos--;

    // Atualizar o rank se necessário
    if (conjunto->ranks[repElem1] == conjunto->ranks[repElem2]) {
        conjunto->ranks[repElem1]++;
    }

    printf("Subconjuntos unidos com sucesso.\n");
    exibirVetoresSubconjuntos(conjunto);
	
}


void uniaoSubconjuntos(ConjuntosDisjuntos **conjunto, int elemSub1, int elemSub2){
	
	//encontrar respectivos representantes de ambos os elementos
	int repElemSub1 = encontrarRepresentante(*conjunto, elemSub1);
	int repElemSub2 = encontrarRepresentante(*conjunto, elemSub2);
	
	int maiorRank;
	
	if (repElemSub1 == repElemSub2) return;
	
	//verifica o representante de ambos os elementos são diferentes pois caso contrário ambos já estão em no mesmo subconjunto e não é necessária a união
	if(repElemSub1 != repElemSub2){
		
		//verifica qual raiz dos elementos repassados possui maior rank e atualiza representante da raiz com menor rank
		if((*conjunto)->ranks[repElemSub1] > (*conjunto)->ranks[repElemSub2]){
			(*conjunto)->pais[repElemSub2] = repElemSub1;
			maiorRank=1; 
		}else if((*conjunto)->ranks[repElemSub1] < (*conjunto)->ranks[repElemSub2]){
			(*conjunto)->pais[repElemSub1] = repElemSub2;
			maiorRank=2;
		}else{
			
			//se ambas os elementos possuem raiz com ranks iguais, escolhemos aleatoriamente um para receber a raiz do outro e atualizamos seu rank
			(*conjunto)->pais[repElemSub2] = repElemSub1;
			
			//incrementamos rank da raiz repassada para a outro
			(*conjunto)->ranks[repElemSub1]++;
			
			maiorRank=1;
		}
		
	}
}


/*int* retornarSubconjunto(ConjuntosDisjuntos *conjunto, int n){
	
	conjunto->pais
	
}*/

char* obterLinhaDinamicamente(FILE *arquivo){
    
	if(arquivo == NULL){
    	printf("Arquivo inexistente ou caminho incorreto\n");
        exit(0);
    }
    
     // Inicializando variável para armazenamento das linhas do arquivo
    int tam = 5;
    char *linha = (char *)malloc(tam * sizeof(char));

    if(linha == NULL){
        printf("Memória indisponível para alocação de linha\n");
		exit(0);
    }

    //variável de controle para a posição lida referente a linha
    int posLinha = 0;
    
    while(fgets(linha + posLinha, tam - posLinha, arquivo)){
        
        // Verificando se o final da linha foi alcançado
        if(strchr(linha, '\n') != NULL) {
            break;
        }

        // Verificando se o espaço foi esgotado e realocando memória
        if(tam - posLinha == 1){
            tam *= 2;
            //verificar se posição de memória retornada por realloc é igual a posição de memória apontada anteriormente por linha
            linha = (char *)realloc(linha, tam * sizeof(char));

            if(linha == NULL){
                printf("Erro ao realocar memória\n");
                exit(0);
            }
        }

        // Atualizando posição da linha lida
        posLinha = strlen(linha);
    }

    //retornando conteudo da linha lida
    return linha;
}




int main(){
	
	setlocale(LC_ALL, "portuguese");
	
	//instruções de leitura da partiçõa
	FILE *arquivo;
	arquivo = fopen("entrada_particao.txt", "r");
	
	if(arquivo==NULL){
		printf("arquivo inexistente ou caminho de acesso incorreto\n");
	}
	
	//vetor de char para armazenar linhas do arquivo
	char *linha;
	linha = obterLinhaDinamicamente(arquivo);
	
	//variável de controle para indice da linha do arquivo
	int indiceLinha = 1;
	
	//ponteiros de string para armazenar as informações do arquivo
	char *infoTam;
	char *infoElemSubconjunto;
	
	int tam;
	int qtdSubconjuntos;
	int primeiroElem;
	int elemento;
	
	//variável de controle para acesso a linha correspondente do subconjunto
	int indiceLinhaSub = 0;
	
	//inicializando instância do conjuntoDisjunto
	ConjuntosDisjuntos *conjunto;
	conjunto = (ConjuntosDisjuntos *)malloc(sizeof(ConjuntosDisjuntos));
	
	while(linha!=NULL){
		
		if(indiceLinha == 1){
		
			//obtendo tamanho do conjunto
			infoTam = strtok(linha, ",");
			tam = atoi(infoTam);
			
			
			infoTam = strtok(NULL, ",");
			qtdSubconjuntos = atoi(infoTam);
			
			
			inicializarConjuntosDisjuntos(&conjunto, tam+1, qtdSubconjuntos);	
		}
		
		if(indiceLinha>1){
			
			//variável de controle para posição dos elementos na matriz de subconjuntos
			int indiceColuna = 1;
			
			//obtendo primeiro elemento do subconjunto
			infoElemSubconjunto = strtok(linha, ",");
			primeiroElem = atoi(infoElemSubconjunto);
			
			conjunto->subconjuntos[indiceLinhaSub][indiceColuna] = primeiroElem;
			indiceColuna++;
			
			
			while ((infoElemSubconjunto = strtok(NULL, ",")) != NULL) {
    			if (strlen(infoElemSubconjunto) > 0) {  // Verifica se o token não é vazio
        			elemento = atoi(infoElemSubconjunto);
        			
        			conjunto->subconjuntos[indiceLinhaSub][indiceColuna] = elemento;
        			
        			
        			indiceColuna++;
        			
					conjunto->subconjuntos[indiceLinhaSub][0] = indiceColuna;
        			
        			uniaoSubconjuntos(&conjunto, primeiroElem, elemento);
        			
    			}
			}
			
			indiceLinhaSub++;
		
		}
		
		//verificanco término do arquivo
   		if(feof(arquivo)){
   			fclose(arquivo);
   			break;	
		}
		
		//obtendo próxima linha
		free(linha);
		
		linha = obterLinhaDinamicamente(arquivo);
		
		indiceLinha++;	
	}
	
	
	
	//ordenarBubbleSort(conjunto->subconjuntos[1]);
	//ordenarInsertionSort(conjunto->subconjuntos[1]);
	printf("\ntam: %d", conjunto->subconjuntos[1][0]);
	//ordenarQuickSort(conjunto->subconjuntos[1], 1, conjunto->subconjuntos[1][0]);
	mergeSort(conjunto->subconjuntos[1], 2, conjunto->subconjuntos[1][0]);
	
	exibirVetoresSubconjuntos(conjunto);
	
	int opcao;
	
	printf("\nEscolha uma opção (1-3):\n");
    printf("1. encontrar representante\n");
    printf("2. união de subconjuntos\n");
    printf("3. ordenar subconjunto\n");
    printf("Digite sua opção: ");
    scanf("%d", &opcao);

    switch(opcao) {
        case 1:
        	int elem;
        	int rep;
        	printf("escolha o elemento do conjunto ao qual deseja busca o representante: ");
        	scanf("%d", &elem);
        	
           	rep = encontrarRepresentante(conjunto, elem);
           	printf("representante de %d: %d", elem, rep);
            break;
        case 2:
            
            int elem1;
            int elem2;
            
            printf("ensira o 1° elemento: ");
            scanf("%d", &elem1);
            
            printf("ensira o 2° elemento: ");
            scanf("%d", &elem2);
            
            unirVetoresSubconjuntos(conjunto, elem1, elem2);
            
            break;
        case 3:
        	int opOrdenacao;
        	int subconjunto;
        	
        	printf("selecione o subconjunto: \n");
        	scanf("%d", &subconjunto);
        	
        	printf("selecione o método de ordenação: \n");
            printf("1. bubbleSort\n");
    		printf("2. insertionSort\n");
    		printf("3. quickSort\n");
    		printf("4. mergeSort\n");
    		scanf("%d", &opOrdenacao);
    		
    		if(opOrdenacao==1){
    			ordenarBubbleSort(conjunto->subconjuntos[subconjunto]);
			}else if(opOrdenacao==2){
				ordenarInsertionSort(conjunto->subconjuntos[subconjunto]);
			}else if(opOrdenacao==3){
				ordenarQuickSort(conjunto->subconjuntos[subconjunto], 1, conjunto->subconjuntos[subconjunto][0]);
			}else if(opOrdenacao==4){
				mergeSort(conjunto->subconjuntos[subconjunto], 1, conjunto->subconjuntos[subconjunto][0]);
			}
			
			exibirVetoresSubconjuntos(conjunto);
    		
    		
        default:
            printf("Opção inválida.\n");
            break;
    }
	
	
	return 0;
}

