#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _max_vetor_ 20
#define _MAX_ 25


typedef struct data_pessoa {
	int id;
	char name[_max_vetor_];
	char desc[_max_vetor_];
	
	int next;
}ptr_st_data;

typedef struct data_pessoa_array_list{
	int ptr_superior;
	int ptr_inferior;
	
	struct data_pessoa Array[_MAX_];
}ptr_list;

struct data_pessoa_array_list* _inserir_data_( struct data_pessoa_array_list *list_array );
struct data_pessoa_array_list* _remover_data_( struct data_pessoa_array_list *list_array );
void _mostrar_data( struct data_pessoa_array_list *list_array );

int _counter_ = 0;

int main(void) {
	
	int _main_menu_op_ = 99;
	
	struct data_pessoa_array_list *list_array = (struct data_pessoa_array_list*)malloc(sizeof(struct data_pessoa_array_list));

    while(_main_menu_op_ != 0) {
    	printf("        **Lista Dinamca - Encadeada**\n");
    	
        printf(" [1] -> Inserir\n");
        printf(" [2] -> Remover\n");
        printf(" [3] -> Mostrar\n");
        printf(" [4] -> Editar\n");

        printf(" [0] -> Sair\n\n");
        printf("Digite o numero da sua opcao!\n>:");
        scanf("%d", &_main_menu_op_);

        if(_main_menu_op_ == 1){
            list_array = _inserir_data_(list_array);
            printf("Insercao concluida!!!\n");
        } else if (_main_menu_op_ == 2) {
            list_array = _remover_data_(list_array);
        } else if(_main_menu_op_ == 3) {
            _mostrar_data(list_array);
        } else if (_main_menu_op_ == 4) {

        } else if(_main_menu_op_ == 0){
            break;
        }else {
            printf("\n>Digite uma opcao valida!!!!\n");
        }
        
        system("pause");
        system("cls");

    }
	
	return 0;
}

struct data_pessoa_array_list* _inserir_data_( struct data_pessoa_array_list *list_array ) {
	int i = 0, op = 1;
	char aux_name[_max_vetor_];
    char aux_desc[_max_vetor_];
	
	system("cls");
	
	while ( op != 0) {
		
		printf("Digite as informacoes abaixo\n Nome: ");
        scanf("%s", aux_name);
        fflush(stdin);

        printf("Digite as informacoes abaixo\n Info: ");
        scanf("%s", aux_desc);
        fflush(stdin);
        
        strcpy(list_array->Array[i].name, aux_name);
        strcpy(list_array->Array[i].desc, aux_desc);
        
        list_array->Array[i].id = _counter_;
        list_array->Array[i].next = _counter_;
        
        _counter_ = _counter_ + 1;
        
        printf("Deseja adicionar mais nodes ? 1 para sim, 0 para nao\n >: ");
        scanf("%d", &op);
        
        if(op == 0){
        	list_array->ptr_superior = i;
        	i++;
			list_array->Array[i].next = -1;
		} else {
			list_array->ptr_superior = i;
			i++;	
		}
		
	}
	
	return list_array;
}

struct data_pessoa_array_list* _remover_data_( struct data_pessoa_array_list *list_array ){
	int id = 0, i = 0, j = 0, w = 0;
	struct data_pessoa_array_list *aux_list_array = list_array;
	printf("Digite o id a ser removido!\n>: ");
	scanf("%d", &id);
	
	do{
		if(aux_list_array->Array[i].id == id){
			w = i;
			while( j != aux_list_array->ptr_superior ){
				if(list_array->Array[w].next != -1) {
					aux_list_array->Array[w] = list_array->Array[w+1];	
				}
				w++;
				j++;
			}
			aux_list_array->Array[i-1].next = -1;
		}
		i++;
	} while(aux_list_array->Array[i].id != id);
	
	return aux_list_array;
}

void _mostrar_data( struct data_pessoa_array_list *list_array ){
	int i = 0;
	
	system("cls");
	
	do {
		if(list_array->Array[i].next != -1){
			printf("****************************************\n");
        	printf("    ID: %d\n",list_array->Array[i].id);
        	printf("    Nome: %s\n",list_array->Array[i].name);
        	printf("    Descricao: %s\n",list_array->Array[i].desc);
        	printf("****************************************\n\n");
		}
        
        i++;
	}while(list_array->Array[i].next != -1);
	
}

