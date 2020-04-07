#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node{
    int id;
    char name[30];
    char ra[60];

    struct node *ptr_link;
}st_node;

int _counter_ = 0;
bool debug = false;

st_node *CreateNode();
st_node *PushInicio(struct node *lista);
st_node *AdicionarData(struct node *lista);
st_node *RemoverPorIndex(struct node *lista, int id);

void MostrarLista(struct node *lista);

int main() {

    struct node *lista = (struct node*)malloc(sizeof(struct node));
    lista = CreateNode();

    // Criando os nodes
    struct node *node_1 = NULL;
    struct node *node_2 = NULL;
    struct node *node_3 = NULL;

    printf("    * Lista encadeada Dinamica *\n");
    system("PAUSE");

    //Alocando a memoria
    /*
    node_1 = (struct node*)malloc(sizeof(struct node));
    node_2 = (struct node*)malloc(sizeof(struct node));
    node_3 = (struct node*)malloc(sizeof(struct node));

    node_1->id = 1;
    strcpy(node_1->name,"Joao");
    strcpy(node_1->ra, "123-444-156-27");

    node_2->id = 2;
    strcpy(node_2->name,"Pedro");
    strcpy(node_2->ra,"000-000-111-23");

    node_3->id = 3;
    strcpy(node_3->name,"Paula");
    strcpy(node_3->ra,"002-034-155-35");

    if(debug) {
        printf("id: %d\n", node_1->id);
        printf("Nome: %s\n", node_1->name);
        printf("RA: %s\n\n", node_1->ra);
    }

    if(debug) {
        printf("id: %d\n", node_2->id);
        printf("Nome: %s\n", node_2->name);
        printf("RA: %s\n\n", node_2->ra);
    }

    if(debug) {
        printf("id: %d\n", node_3->id);
        printf("Nome: %s\n", node_3->name);
        printf("RA: %s\n\n", node_3->ra);
    }

    //Conectando os nos
    node_1->ptr_link = node_2;
    node_2->ptr_link = node_3;
    node_3->ptr_link = NULL;*/

    PushInicio(lista);
    AdicionarData(lista);
    AdicionarData(lista);

    //Mostrando a lista.
    if(lista)  MostrarLista(lista);

    RemoverPorIndex(lista, 0);
    MostrarLista(lista);
    //if(node_1)  _mostrar_lista_(node_1);

    printf("Fim do programa. . .\n\n");

    system("PAUSE");
    return 0;
}

st_node *CreateNode() {
    st_node *pointer_node = (st_node *) malloc(sizeof(st_node));
    pointer_node->ptr_link = NULL;
    return pointer_node;
}

st_node *PushInicio(struct node *lista) {
    st_node *new_node = lista;

    printf("    ** Inserindo no inicio da Lista encadeada Dinamica **\n");

    new_node->id = _counter_;

    printf("Nome: ");
    scanf("%s", new_node->name);

    printf("\nRA: ");
    scanf("%s", new_node->ra);

    _counter_ = _counter_ + 1;

    if(debug) {
        printf("\nid: %d\n", lista->id);
        printf("Nome: %s\n", lista->name);
        printf("RA: %s\n\n", lista->ra);
    }

    return lista;
}

st_node *AdicionarData(struct node *lista) {
    st_node *new_node = (st_node *) malloc(sizeof(st_node));
    st_node *atual_node;

    new_node->id = _counter_;
    _counter_ = _counter_ + 1;

    printf("Nome: ");
    scanf("%s", new_node->name);

    printf("\nRA: ");
    scanf("%s", new_node->ra);

    new_node->ptr_link = NULL;

    if(lista == NULL) {
        lista = new_node;
    } else {
        while(lista->ptr_link != NULL) {
            lista = lista->ptr_link;
        }
        lista->ptr_link = new_node;
    }

    if(debug) {
        printf("id: %d\n", new_node->id);
        printf("Nome: %s\n", new_node->name);
        printf("RA: %s\n\n", new_node->ra);
    }
}

// Remove um elemento da lista por index.
st_node *RemoverPorIndex(struct node *lista, int id) {
    struct node *aux_lista = lista;
    struct node *temp_lista = NULL;

    if(id == 0) {
        aux_lista = lista->ptr_link;
        free(lista);
        lista = aux_lista;
    } else {
        while(aux_lista->id < id-1) {
            aux_lista = aux_lista->ptr_link;
        }

        temp_lista = aux_lista->ptr_link;
        aux_lista->ptr_link = temp_lista->ptr_link;

        
        lista = aux_lista;  
    }

    free(temp_lista); 

}

void MostrarLista(struct node *lista){
    system("cls");

    struct node *aux_lista = lista;

    printf("    ** Mostrando a Lista encadeada Dinamica **\n");

    if(aux_lista) {
        while(aux_lista != NULL){
            printf("******************************\n\n");
            printf("    id: %d\n", aux_lista->id);
            printf("    Nome: %s\n", aux_lista->name);
            printf("    RA: %s\n\n", aux_lista->ra);
            printf("******************************\n");
            aux_lista = aux_lista->ptr_link;
        }
    } else printf("ERRO, A lista esta vazia!!!\n\n");

    system("PAUSE");
}
