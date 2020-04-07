#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#define _MAX_ 20

typedef struct stackStatic{
    int id;
    char info[20];
}st_static;

st_static *stack[_MAX_];
int stackCounter;
int stackHead;
int idCounter;
bool debug = false;

void InicializarPilha();    // init
void InserirPilha();        // push
void MostrarPilha();        // show
void RemoverDaPilha();      // pop
void EditarPilha();         // edit

int main() {
    setlocale(LC_ALL, "Portuguese");
    int opt = 99;

    idCounter = stackCounter = stackHead = 0;
    InicializarPilha();

    do{
        //system("CLS");
        printf(" ** Pilha estatica **\n");
        printf("1 -> Inserir\n");
        printf("2 -> Remover\n");
        printf("3 -> Editar\n");
        printf("4 -> Monstrar\n");
        printf("0 -> Sair\n\n");

        printf("* Digite sua opcao\n>: ");
        scanf("%d",&opt);

        if(opt == 1){
            InserirPilha();
            system("pause");
        } else if(opt == 2) {
            RemoverDaPilha();
            system("pause");
        } else if(opt == 3) {
            EditarPilha();
            system("pause");
        } else if(opt == 4) {
            MostrarPilha();
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

void InicializarPilha(){
    st_static *node = (st_static*)malloc(sizeof(st_static));

    node->id = -1;
    strcpy(node->info,"NULL");

    stack[stackCounter] = node;
}

void InserirPilha(){
    char info[20];

    printf("\nDigite as infos a serem adicionadas!\n>: ");
    scanf("%s", info);

    st_static *newNode = (st_static*)malloc(sizeof(st_static));

    newNode->id = idCounter; // adiciona o id no node.
    strcpy(newNode->info, info); // adiciona a info no node.

    idCounter++; // aumenta o id.
    stack[stackCounter] = newNode; // adiciona o novo node na pilha.

    if(debug) {
        printf("\n* ID: %d                              \n",stack[stackCounter]->id);
        printf("\n* Info: %s                            \n",stack[stackCounter]->info);
        printf("\n* Contador da pilha: %d                            \n",stackCounter);
    }

    stackCounter++; // vai para proxima casa da pilha.
    InicializarPilha();
    printf("\n\nData adicionada a pilha com sucesso!\n");
}

void MostrarPilha(){
    int auxCounter = 0;
    auxCounter = stackCounter;

    for(auxCounter; auxCounter != -1; auxCounter--) {
        if(stack[auxCounter]->id != -1) {
            printf("**************************************\n");
            printf("*  ID: %d                             \n",stack[auxCounter]->id);
            printf("*  Info: %s                           \n",stack[auxCounter]->info);
            printf("**************************************\n\n");
        } else {
            printf("***************************************\n");
            printf("*  ID: %d                             *\n",stack[auxCounter]->id);
            printf("*            STACK HEAD               *\n");
            printf("***************************************\n\n");
        }
    }
}

void RemoverDaPilha(){
    printf("\n* Removendo o item mais ao topo *\n");

    st_static *node = (st_static*)malloc(sizeof(st_static));
    if( stackCounter != 0) {
        node->id = -1;
        strcpy(node->info,"NULL");
        free(stack[stackCounter]);
        stackCounter--;
        stack[stackCounter] = node;
    } else {
        node->id = -1;
        strcpy(node->info,"NULL");
        free(stack[stackCounter]);
        stack[stackCounter] = node;
    }

    MostrarPilha();
}

void EditarPilha() {
    int choosenID, auxCounter;
    bool flag = false;

    MostrarPilha();
    printf("\n\n Digite o ID a ser Editado...\n>:");
    scanf("%d",&choosenID);

    auxCounter = 0;
    if(choosenID != -1) {
        do{
            if(stack[auxCounter]->id == choosenID) {
                printf("Digite a nova info:\n>: ");
                scanf("%s", stack[auxCounter]->info);
                flag = true;
                break;
            }
            auxCounter++;
        }while(stack[auxCounter]->id != choosenID);

        if(flag == true) {
            printf("\nEdicao feita com sucesso!!!\n\n");
        } else {
            printf("\nEdicao falhou. . .\n\n");
        }
    } else {
        printf("\n Operacao invalida !!! nao pode sobrepor a head da pilha!!!\n");
    }
}
