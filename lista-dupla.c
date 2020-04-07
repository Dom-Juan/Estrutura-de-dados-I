#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int info;
    struct node *next;
    struct node *prev;
}st_node;

void AdicionaInicio(st_node **head, int newData);
void AdicionaFim(st_node **head, int newData);
void DeletarNode(st_node **head, st_node *nodeDeletado);
void MostrarLista(st_node *head);

int main() {
    struct node *head = NULL;

    printf("* Lista duplamente encadeada *\n");

    AdicionaInicio(&head, 1);
    AdicionaFim(&head, 2);
    AdicionaInicio(&head, 0);
    AdicionaFim(&head, 3);

    printf("\nAntes de deletar um node.\n");
    MostrarLista(head);

    DeletarNode(&head, head->next); /*deleta o ultimo node*/
    printf("\n\n=========================================\n\n");

    printf("\nDepois de deletar um node.\n");
    MostrarLista(head);

    printf("\n");

    system("PAUSE");

    return 0;
}

void AdicionaInicio(st_node **head, int newData){
    // alocando o node.

    struct node *newNode = (struct node*)malloc(sizeof(struct node));

    // colocando a nova info no node.
    newNode->info = newData;

    // trocando o head para o novo node.
    newNode->prev = NULL;
    newNode->next = (*head);

    // liga o antigo head, que agora eh um node normal, ao novo head.
    if((*head) != NULL){
        (*head)->prev = newNode;
    }

    // move o head para apontar para o novo node.
    (*head) = newNode;

}

void AdicionaFim(st_node **head, int newData){
    // alocar o node
    struct node *newNode = (struct node*)malloc(sizeof(struct node));

    struct node *last = *head;

    // adicionando o novo node.
    newNode->info = newData;
    newNode->next = NULL;

    // se o head for NULL, apenas adiciona o node.
    if(*head == NULL) {
        newNode->prev = NULL;
        *head = newNode;
    }

    // percorrendo os nodes ate o ultimo
    while(last->next != NULL) {
        last = last->next;
    }

    // adiciona o novo node no ultimo node da lista.
    last->next = newNode;
    newNode->prev = last;

}

/* Funcao para deletar um node.
 * head -> aponta para o ponteiro do head
 * nodeDeletado -> aponta para o node que sera deletado.
 */
void DeletarNode(st_node **head, st_node *nodeDeletado) {

    // se os dois forem NULL, nao existe nodes.
    if(*head == NULL || nodeDeletado == NULL)
        printf("\n-> ERRO NA MEMORIA!!!\n\n");

    // se o node deletado eh o head.
    if(*head == nodeDeletado) {
        *head = nodeDeletado->next;
    }

    // modificando o proximo apenas se o node a ser deletado n eh o ultimo
    if(nodeDeletado->next != NULL) {
        nodeDeletado->next->prev = nodeDeletado->prev;
    }

    // modificando o proximo apenas se o node a ser deletado n eh o primeiro
    if(nodeDeletado->prev != NULL) {
        nodeDeletado->prev->next = nodeDeletado->next;
    }

    // removendo a memoria ocupada pelo nodeDeletado, aka deletando ele.
    free(nodeDeletado);
}

void MostrarLista(st_node *list) {
    struct node* last = NULL;
    printf("\nLista duplamente encadeada -> de frente pra tras \n");
    while (list != NULL) {
        printf(" %d ", list->info);
        last = list;
        list = list->next;
    }

    printf("\n\nLista duplamente encadeada -> de tras para frente \n");
    while (last != NULL) {
        printf(" %d ", last->info);
        last = last->prev;
    }
}
