#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

struct aluno {
	int matricula;             
    char nome[80];     
    char email[40]; 
}; 
typedef struct aluno tpaluno;

//TipoChave = int / matricula
int hash(int chave) {
	int i, comp, soma = 0;
	char s[10];
    itoa(chave, s, 10);
	comp = strlen(s);
	for (i = 0; i < comp; i++)
	soma = soma + s[i];
	return (soma % MAX);
}

void inicializarTabelaHash(tpaluno *tbHash[]) {
	int i = 0;
    for (i=0; i < MAX; i++)
		tbHash[i] = NULL;
}

void inserir(tpaluno *tbHash[], tpaluno reg) {     
	// x é endereço do vetor
	int x = hash(reg.matricula); 
	// não trata a colisão
	tpaluno *aux;
	aux = malloc(sizeof(tpaluno));
	aux->matricula = reg.matricula;
	strcpy(aux->nome,reg.nome);
	strcpy(aux->email,reg.email);
	tbHash[x] = aux;
}

void remocao(tpaluno *tbHash[], int matricula) {
	int x = hash(matricula); 
    tpaluno *aux = tbHash[x];
	if (aux->matricula == matricula)  {
		free (aux);
		tbHash[x] = NULL; 
	}
    else 
		printf("Matrícula não existente na tabela");
}

void busca(tpaluno *tbHash[], int matricula) {
	int x = hash(matricula); 
	tpaluno *aux = tbHash[x];
    if (aux != NULL) {
		if (aux->matricula == matricula) {
			printf("Nome: %s ", aux->nome);
			printf("Email: %s ", aux->email);
		}
	} 
	else 
		printf("Chave não existente na tabela");
}

void imprimir(tpaluno *tbHash[]) {
    int i;
    for(i=0 ; i<MAX ; i++) {
        if(tbHash[i] == NULL) {
            printf("\n Vet[%d]: ", i);
            printf("--");
		}
        else {
            printf("\n Vet[%d]: ", i);
            printf("%d %s %s", tbHash[i]->matricula, tbHash[i]->nome, tbHash[i]->email);
		}
    }
    printf("\n\n");
}


int main(void) {
	tpaluno *tabHash[MAX];
	
	tpaluno aux;
	
    inicializarTabelaHash(tabHash);
    
    aux.matricula = 1;
    strcpy(aux.nome, "Giovanna");
    strcpy(aux.email, "gi@email.com");
    inserir(tabHash, aux);
    
	aux.matricula = 2;
    strcpy(aux.nome, "Fernanda");
    strcpy(aux.email, "fer@email.com");
    inserir(tabHash, aux);
    
    aux.matricula = 3;
	strcpy(aux.nome, "Leticia");
    strcpy(aux.email, "le@email.com");
    inserir(tabHash, aux);
    
    aux.matricula = 4;
	strcpy(aux.nome, "David");
    strcpy(aux.email, "dvd@email.com");
    inserir(tabHash, aux);
    
    aux.matricula = 5;
    strcpy(aux.nome, "Alexandre");
    strcpy(aux.email, "ale@email.com");
    inserir(tabHash, aux);
    
    printf("\nResultado da Busca: ");
    busca(tabHash, 1);
    printf("\n");
    
    imprimir(tabHash);
    
    remocao(tabHash, 1);
	
    imprimir(tabHash);
    
	printf("\nResultado da Busca: ");
    busca(tabHash, 1);
    printf("\n");	
	return(0);
}