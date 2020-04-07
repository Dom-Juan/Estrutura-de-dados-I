#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define  _MAX_ 20

typedef  struct stack{
    int id;
    char info[_MAX_];
    struct stack *next;
}st_stack;

void InicializarPilha(st_stack **stackHead);
void AdicionarPilha(st_stack **stackHead);
void RemoverDaPilha(st_stack **stackHead);
void EditarPilha(st_stack **stackHead);
void MostrarPilha(st_stack *stackHead);
void DestruirPilha(st_stack **stackHead);

bool PilhaEstaVazia(st_stack *stackHead);

int idCounter = 0;

int main() {
    int opt = 99;
    st_stack *stackHead = NULL;
    InicializarPilha(&stackHead);

    do{
        system("CLS");
        printf("* Pilha Dinamica em C *\n");
        printf("1 -> Inserir\n");
        printf("2 -> Remover\n");
        printf("3 -> Editar\n");
        printf("4 -> Monstrar\n");
        printf("5 -> Destruir Pilha\n");
        printf("0 -> Sair\n\n");

        printf("* Digite sua opcao\n>: ");
        scanf("%d",&opt);

        if(opt == 1){
            AdicionarPilha(&stackHead);
            system("pause");
        } else if(opt == 2) {
            RemoverDaPilha(&stackHead);
            system("pause");
        } else if(opt == 3) {
            EditarPilha(&stackHead);
            system("pause");
        } else if(opt == 4) {
            MostrarPilha(stackHead);
            system("pause");
        } else if(opt == 5) {
            DestruirPilha(&(stackHead));
            system("pause");
        } else if(opt == 0) {
            system("pause");
        } else {
            printf("\nOpcao invalida!!!!\n");
            system("pause");
        }

    }while(opt != 0);

    return 0;
}

void InicializarPilha(st_stack **stackHead){
    st_stack *node = (st_stack*)malloc(sizeof(st_stack));
    node->next = NULL;
    *stackHead = node;
}

void AdicionarPilha(st_stack **stackHead){
    char info[20];

    st_stack *newNode = (st_stack*)malloc(sizeof(st_stack));
    newNode->next = NULL;

    printf("Digite as informacoes pra adicionar no node...\n>: ");
    scanf("%s",info);

    // Adicionando as informacoes no node
    newNode->id=idCounter;
    strcpy(newNode->info,info);

    // Ligando o node ao topo.
    newNode->next = (*stackHead);
    (*stackHead) = newNode;

    idCounter++;

    /*if(PilhaEstaVazia((*stackHead)) == true){
        st_stack *newNode = (st_stack*)malloc(sizeof(st_stack));
        newNode->next = NULL;

        printf("Digite as informacoes pra adicionar no node...\n>: ");
        scanf("%s",info);

        // Adicionando as informacoes no node
        newNode->id=idCounter;
        strcpy(newNode->info,info);

        // Ligando o node ao topo.
        newNode->next = (*stackHead);
        (*stackHead) = newNode;

        idCounter++;
    } else {
        printf("\n--> A pilha esta vazia!!!\n\n");
        return;
    }*/
}

void MostrarPilha(st_stack *stackHead){
    while(stackHead->next != NULL) {
        printf("***************************************\n");
        printf("*  ID: %d                              \n",stackHead->id);
        printf("*  Info: %s                            \n",stackHead->info);
        printf("***************************************\n\n");
        stackHead = stackHead->next;
    }
}

void EditarPilha(st_stack **stackHead){
    int choosenId;

    printf("Digite o id para editar o node de mesmo id...\n>: ");
    scanf("%d",&choosenId);

    while((*stackHead)->id != choosenId) {
        (*stackHead) = (*stackHead)->next;
    }

    printf("Digite a nova info...\n>: ");
    scanf("%s",(*stackHead)->info);
}

void RemoverDaPilha(st_stack **stackHead){
    st_stack *newNode = (st_stack*)malloc(sizeof(st_stack));
    newNode->next = NULL;

    printf("Removendo um node da ponta...\n");

    newNode = (*stackHead);

    printf("   > Info do node a ser removido:\n\n");
    printf("***************************************\n");
    printf("*  ID: %d                              \n",newNode->id);
    printf("*  Info: %s                            \n",newNode->info);
    printf("***************************************\n\n");

    (*stackHead) = (*stackHead)->next;
    free(newNode);

    idCounter--;

    /*if(PilhaEstaVazia((*stackHead))){
        st_stack *newNode = (st_stack*)malloc(sizeof(st_stack));
        newNode->next = NULL;

        printf("Removendo um node da ponta...\n");

        newNode = (*stackHead);

        printf("   > Info do node a ser removido:\n\n");
        printf("***************************************\n");
        printf("*  ID: %d                              \n",newNode->id);
        printf("*  Info: %s                            \n",newNode->info);
        printf("***************************************\n\n");

        (*stackHead) = (*stackHead)->next;
        free(newNode);

        idCounter--;
    } else {
        printf("\n--> A pilha esta vazia!!!\n\n");
        return;
    }*/
}

void DestruirPilha(st_stack **stackHead) {
    while((*stackHead) != NULL) {
        RemoverDaPilha(&(*stackHead));
        (*stackHead) = (*stackHead)->next;
    }

    free(stackHead);
    printf("\nPilha Destruida\n\n");

    stackHead = NULL;
    InicializarPilha(stackHead);
}

bool PilhaEstaVazia(st_stack *stackHead){
    if(stackHead == NULL) {
        printf("\nA pilha esta vazia!!!\n");
            return true;
    } else {
        printf("\nA pilha esta cheia!!!\n");
        return false;
    }
}
