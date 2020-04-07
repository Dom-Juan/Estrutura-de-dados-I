#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define _MAX_ 255

char *q[_MAX_];
int pos_superior = 0;
int pos_inferior = 0;

// Functions
void queue_enter(void);
void queue_store(char *q);
void queue_show(void);
void queue_delete(void);
char *queue_retrive(void);

int main(void) {
    char inputString[80];
    char stringOption;
    int option = 99;
    register int i;

    for( i = 0; i < _MAX_; i++)
        q[i] = NULL;

    do{
        system("CLS");
        printf("        *Lista Simples*     \n");
        printf("  -> Operacoes com a Lista:\n");
        printf(" > [E]ntrada\n");
        printf(" > [L]eitura\n");
        printf(" > [R]emover\n");
        printf(" > [S]air\n\n");

        fflush(stdin);

        printf("Digite sua opcao:\n>: ");
        fflush(stdin);

        scanf("%c", &stringOption);
        //*stringOption = toupper(*stringOption);

        if( stringOption == 'e' || stringOption == 'E' ) {
            queue_enter();
        } else if( stringOption == 'l' || stringOption == 'L' ) {
            queue_show();
        } else if( stringOption == 'r' || stringOption == 'R' ) {
            queue_delete();
        } else if(stringOption == 's' || stringOption == 'S' ) {
            option = 0;
        } else {
            printf("Opcao invalida\n");
            system("PAUSE");
        }

    } while(option != 0);

    printf("Saindo do programa. . . !!\n");

    return 0;
}

// Realiza a operacao de armazenar a entrada na lista
void queue_enter(void) {
    char string[256], *p;
    int op = 1;

    do {
        printf("Digite a info aqui (posicao: %d): ", pos_superior + 1);
        scanf("%s", string);

        if( *string == 0 )
            break; // nao ocorreu entradas.
        p = malloc(strlen(string) + 1);

        if(!p) {
            printf("Nao existe memoria disponivel. . . \n");
            return;
        }

        strcpy(p, string);
        if(*string)
            queue_store(p);

        printf("Deseja continuara a inserir dados na lista ? 1 - sim, 0 - nao\n");
        scanf("%d", &op);
    }while(*string && op != 0);
}

// Armazena algo da lista.
void queue_store(char *qq){
    if( pos_superior == _MAX_) {
        printf("A lista está cheia");
        return;
    } else {
        q[pos_superior] = qq;
        pos_superior = pos_superior + 1;
    }
}

void queue_show(void) {
    register int i;

    for (i = pos_inferior; i < pos_superior; ++i) {
        printf("[%d]. %s\n", i, q[i]);
    }
    system("PAUSE");
}

void queue_delete(void) {
    char *p;
    if( (p = queue_retrive()) == NULL )
        return;
    printf("%s\n", p);
    system("PAUSE");
}

// Retorna algo da lista.
char *queue_retrive(){
    if( pos_inferior == pos_superior ) {
        printf("Sem conteudo para retorno. . .\n");
        system("PAUSE");
        return NULL;
    } else {
        printf("Removeu %s", q[pos_inferior]);
        pos_inferior = pos_inferior + 1;
        return q[pos_inferior - 1];
    }
}
