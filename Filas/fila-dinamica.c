#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct queue{
    int id;
    char info[20];
    struct queue *next;
}st_queue;

st_queue *frenteFila;
st_queue *atrasFila;

int idCounter = 0;
bool debug = false;

void InicializaFila();
void AdicionaNaFila();
void MostrarFila();
void RemoverDaFila();
bool FilaEstaVazia();
void EditarFila();

int main() {
    int opt = 99;
    //InicializaFila();

    do{
        //system("CLS");
        printf(" ** Fila dinamica **\n");
        printf("1 -> Inserir\n");
        printf("2 -> Remover\n");
        printf("3 -> Editar\n");
        printf("4 -> Monstrar\n");
        printf("0 -> Sair\n\n");

        printf("* Digite sua opcao\n>: ");
        scanf("%d",&opt);

        if(opt == 1){
            AdicionaNaFila();
            system("pause");
        } else if(opt == 2) {
            RemoverDaFila();
            system("pause");
        } else if(opt == 3) {
            EditarFila();
            system("pause");
        } else if(opt == 4) {
            MostrarFila();
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

void InicializaFila(){
    frenteFila = atrasFila = (st_queue*)malloc(sizeof(st_queue));
    frenteFila->next = atrasFila->next = NULL;
}

void AdicionaNaFila(){
    st_queue *nodeTemporario = (st_queue*)malloc(sizeof(st_queue));

    printf("Digite os valores a serem inseridos na fila...\n>: ");
    scanf("%s",nodeTemporario->info);
    nodeTemporario->id = idCounter;
    nodeTemporario->next = NULL;

    if(frenteFila == NULL) {
        frenteFila = atrasFila = nodeTemporario;

        if(debug) {
            printf("\n\nFrente da fila\n");
            printf("id: %d\n",frenteFila->id);
            printf("info: %s\n",frenteFila->info);
        }
    } else {
        atrasFila->next = nodeTemporario;
        atrasFila = nodeTemporario;

        if(debug) {
            printf("\n\nAtras da fila\n");
            printf("id: %d\n",atrasFila->id);
            printf("info: %s\n",atrasFila->info);
        }
    }

    idCounter++;
}

void EditarFila(){
    int choosenId = 0;
    st_queue *nodeTemporario = frenteFila;

    printf("Digite o node a ser editado...\n>: ");
    scanf("%d",&choosenId);

    while(nodeTemporario->id != choosenId) {
        if(debug) {
            printf("**************************************\n");
            printf("*  ID: %d                             \n",nodeTemporario->id);
            printf("*  Info: %s                           \n",nodeTemporario->info);
            printf("**************************************\n\n");
        }

        nodeTemporario = nodeTemporario->next;
    }

    printf("Digite o nova info no node...\n>: ");
    scanf("%s",nodeTemporario->info);
}

void MostrarFila(){
    st_queue *nodeTemporario = nodeTemporario = frenteFila;

    while(nodeTemporario) {

        printf("**************************************\n");
        printf("*  ID: %d                             \n",nodeTemporario->id);
        printf("*  Info: %s                           \n",nodeTemporario->info);
        printf("**************************************\n\n");

        nodeTemporario = nodeTemporario->next;
    }
}

void RemoverDaFila(){
    int choosenId = 0;
    st_queue *nodeTemporario = (st_queue*)malloc(sizeof(st_queue));

    nodeTemporario = frenteFila;

    if(frenteFila == NULL) {
        printf("\nErro! - A fila esta cheia...\n\n");
        frenteFila = atrasFila = NULL;
    } else {
        /*printf("Digite o id do node a ser deletado...\n\n>: ");
        scanf("%d",&choosenId);*/
        frenteFila = frenteFila->next;
        free(nodeTemporario);

    }
}

bool FilaEstaVazia(){
    if(frenteFila == NULL) {
        printf("\n  * A fila esta vazia... *\n");
        return true;
    } else {
        printf("\n  * Existem elementos na fila!! *\n");
        return false;
    }
}
