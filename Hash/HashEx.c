#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 9 // Tamanho total do vetor ( overflow + tabela).
#define P 7   // Tamanho do vetor onde nao eh o overflow, ou seja, a tabela.

// Nodes que poderao ficar dentro do vetor q representa a tabela
typedef struct node {
    int key;
    char nome[35];
    int matricula;
    int next;
}nodeHash;

// Estrutura da tabela
typedef struct tabelaHash {
    struct node tabHash[max]; // tabela
    int firstColision;        // marcador de overflow na tabela
}tbHash;

/**Inicia a tabela Hash
 * Aqui inicia os elementos int como -1 para indicar q eles estao disponiveis para serem utilizados
 * o nome utilzando NULL é apenas estetico para evitar mostrar lixo na memoria.
 * */ 
void init(tbHash *hash) {
    int i = 0;
    hash->firstColision = 7;                    // Inicio da tabela de colisao
    for(i; i < max; i++) {
        hash->tabHash[i].key = -1;              // inicia chave com -1
        hash->tabHash[i].next = -1;             // o proximo recebe -1
        hash->tabHash[i].matricula = -1;        // a matricula recebe -1
        strcpy(hash->tabHash[i].nome, "NULL");  // marca o nome como NULL.
    }
}

// Função hash para gerar os endereços
int _hash_data_(int matricula) {
    return (matricula) % P;
}

/* Hash caso fosse utilizado matricula por char
int _hash_data_(int size, char matricula[size]) {
    int i = 0, comp, soum;
    char str[10];
    itoa(matricula,str,10);
    comp = strlen(str);

    for(i; i < comp; i++)
        soum = soum + str[i];

    return (soum % P);
}*/

// Insere na tabela
void insert(tbHash *hash, nodeHash *node) {

    // cria um node local com espaço de memória e passa do node de ponteiro para esse node local.
    nodeHash newNode;
    strcpy(newNode.nome, node->nome);
    newNode.matricula = node->matricula;
    newNode.key = node->key;
    newNode.next = node->next;

    int address = _hash_data_(newNode.matricula); // endereço do hash
    newNode.key = address;                        // guardando o endereço na variável key, para marcar q esse espaço ta usado.

    if (hash->tabHash[address].key == -1 && address < hash->firstColision) {  // se a key == -1, o lugar esta disponivel e adiciona o newNode.
        hash->tabHash[address].key = newNode.key;
        strcpy(hash->tabHash[address].nome, newNode.nome);
        hash->tabHash[address].matricula = newNode.matricula;
        hash->tabHash[address].next = newNode.next;

        printf("            Hash[%d]: \n", address);
        printf("                    |->Key: %d\n                    |->Nome: %s\n                    |->Matricula: %d\n                    |->Proximo: %d\n\n",
               hash->tabHash[address].key, hash->tabHash[address].nome, hash->tabHash[address].matricula,
               hash->tabHash[address].next);
    } else {    // do contrário verifica se existe espaço para dicionar na área de overflow.
        if (hash->firstColision < max) { // existe espaço ainda
            if (hash->tabHash[address].key == newNode.key) { //  confirma se realmente houve uma colisao.
                int auxAtual = hash->tabHash[address].key; // salva o valor da posicao atual

                // adiciona o node
                hash->tabHash[address].next = hash->firstColision;
                hash->tabHash[hash->firstColision].key = newNode.key;
                strcpy(hash->tabHash[hash->firstColision].nome, newNode.nome);
                hash->tabHash[hash->firstColision].matricula = newNode.matricula;
                // atualiza o proximo desse nome como o node da colisao.
                hash->tabHash[hash->firstColision].next = auxAtual;

                printf("     Colidiu! atual --> Hash[%d] tem Proximo key %d em:\n",address, hash->tabHash[address].next);
                printf("            Overflow Hash[%d]:\n", hash->firstColision);
                printf("                    |->Key: %d\n                    |->Nome: %s\n                    |->Matricula: %d\n                    |->Proximo: %d\n\n",
                       hash->tabHash[hash->firstColision].key, hash->tabHash[hash->firstColision].nome,
                       hash->tabHash[hash->firstColision].matricula, hash->tabHash[hash->firstColision].next);

                hash->firstColision++;  // incrementa o colisao.
            }
        }
    }
}

// Busca um elemento na tabela
void search(tbHash *hash, int matricula) {
    int result = _hash_data_(matricula);

    printf("\n**************************** Busca ****************************\n");

    printf("\nMatricula digitada %d\n", matricula);
    printf("Resultado: %d\n", result);
    printf("Hash[Resultado] -> Hash[%d]\n", result);
    printf("Matricula nessa Hash: %d\n\n",hash->tabHash[result].matricula);
    int auxResult = hash->tabHash[result].next;
    printf("auxResult: %d\n\n", auxResult);

    // Caso o elemento procurado esteja no overflow
    if(hash->tabHash[result].next != -1 && hash->tabHash[auxResult].matricula == matricula) {
        printf("*hash[%d]: \n",auxResult);
        printf("    |Key: %d\n    |Nome:%s\n    |Matricula:%d\n    |Proximo:%d*\n    |-----------------\n",hash->tabHash[auxResult].key, hash->tabHash[auxResult].nome, hash->tabHash[auxResult].matricula, hash->tabHash[auxResult].next);
    } else if(hash->tabHash[result].matricula == matricula) { // caso o elemento esteja na tabela.
        printf("*hash[%d]: \n",result);
        printf("    |Key: %d\n    |Nome:%s\n    |Matricula:%d\n    |Proximo:%d*\n    |-----------------\n",hash->tabHash[result].key, hash->tabHash[result].nome, hash->tabHash[result].matricula, hash->tabHash[result].next);
    } else printf("\nChave nao encontrada!!\n\n");

    printf("\n***************************************************************\n");
}

// Funciona que nem a busca, entretanto voce reseta a posição atual e remove o elemento.
void remover(tbHash *hash, int matricula) {
    int result = _hash_data_(matricula);
    int auxResult = hash->tabHash[result].next;
    printf("\n************************* Remocao *****************************\n");
    if(hash->tabHash[result].next != -1 && hash->tabHash[auxResult].matricula == matricula) {
        printf("*hash[%d]: \n",auxResult);
        printf("    |Key: %d\n    |Nome:%s\n    |Matricula:%d\n    |Proximo:%d*\n    |-----------------\n",hash->tabHash[auxResult].key, hash->tabHash[auxResult].nome, hash->tabHash[auxResult].matricula, hash->tabHash[auxResult].next);

        hash->tabHash[auxResult].key = hash->tabHash[auxResult].next = -1;
        hash->tabHash[auxResult].matricula = -1;
        strcpy(hash->tabHash[auxResult].nome,"NULL");
    } else if(hash->tabHash[result].matricula == matricula) {
        printf("*hash[%d]: \n",result);
        printf("    |Key: %d\n    |Nome:%s\n    |Matricula:%d\n    |Proximo:%d*\n    |-----------------\n",hash->tabHash[result].key, hash->tabHash[result].nome, hash->tabHash[result].matricula, hash->tabHash[result].next);

        hash->tabHash[result].key = hash->tabHash[result].next = -1;
        hash->tabHash[result].matricula = -1;
        strcpy(hash->tabHash[result].nome,"NULL");
    } else printf("\nChave nao encontrada!!\n\n");

    printf("\n***************************************************************\n");
}

// Mostra os nodes da tabela hash.
void _show_hash_(tbHash *hash) {
    int i = 0;
    printf("\n********************Mostrando a Tabela Hash********************\n");
    while(i < max) {
        if(hash->tabHash[i].next == -1) {
            printf("*hash[%d]: \n",i);
            printf("    |Key: %d\n    |Nome:%s\n    |Matricula:%d\n    |Proximo:%d*\n    |----------------------------------\n",hash->tabHash[i].key, hash->tabHash[i].nome, hash->tabHash[i].matricula, hash->tabHash[i].next);
        } else {
            int next = hash->tabHash[i].next;
            printf("*hash[%d]:              *hash[%d]\n",i, next);
            printf("    |Key: %d              |Key: %d\n    |Nome: %s             |Nome: %s\n    |Matricula: %d        |Matricula: %d\n    |Proximo: %d          |Proximo: %d\n    |----------------------------------\n",hash->tabHash[i].key, hash->tabHash[next].key, hash->tabHash[i].nome, hash->tabHash[next].nome, hash->tabHash[i].matricula, hash->tabHash[next].matricula, hash->tabHash[i].next, hash->tabHash[next].next);
        }

        i++;
    }
    printf("\n***************************************************************\n");
}


int main() {
    printf("Estrutura de dados I --> Hash\n\n");
    tbHash  *hash = (tbHash*)malloc(sizeof(tbHash)); // Aloca a memoria para o ponteiro para a estrutura da tabela.
    init(hash); //Inicia a tabela

    /* Iniciando os nodes com o conteudo */
    nodeHash *node1 = (nodeHash*)malloc(sizeof(nodeHash));
    nodeHash *node2 = (nodeHash*)malloc(sizeof(nodeHash));
    nodeHash *node3 = (nodeHash*)malloc(sizeof(nodeHash));
    nodeHash *node4 = (nodeHash*)malloc(sizeof(nodeHash));
    nodeHash *node5 = (nodeHash*)malloc(sizeof(nodeHash));
    nodeHash *node6 = (nodeHash*)malloc(sizeof(nodeHash));
    nodeHash *node7 = (nodeHash*)malloc(sizeof(nodeHash));
    nodeHash *node8 = (nodeHash*)malloc(sizeof(nodeHash));
    nodeHash *node9 = (nodeHash*)malloc(sizeof(nodeHash));

    strcpy(node1->nome,"A");
    strcpy(node2->nome,"B");
    strcpy(node3->nome,"C");
    strcpy(node4->nome,"D");
    strcpy(node5->nome,"E");
    strcpy(node6->nome,"F");
    strcpy(node7->nome,"G");
    strcpy(node8->nome,"H");
    strcpy(node9->nome,"I");

    node1->matricula = 1;
    node2->matricula = 2;
    node3->matricula = 3;
    node4->matricula = 4;
    node5->matricula = 5;
    node6->matricula = 6;
    node7->matricula = 7;
    node8->matricula = 8;
    node9->matricula = 9;

    node1->next = node1->key = -1;
    node2->next = node2->key = -1;
    node3->next = node3->key = -1;
    node4->next = node4->key = -1;
    node5->next = node5->key = -1;
    node6->next = node6->key = -1;
    node7->next = node7->key = -1;
    node8->next = node8->key = -1;
    node9->next = node9->key = -1;

    printf("\n**Antes do hashing**\n");
    _show_hash_(hash);

    printf("\n*******************Nodes que entraram no Hash***************\n");
    printf(" Key: %d\n Nome:%s\n Matricula:%d\n proximo:%d\n\n",node1->key, node1->nome, node1->matricula, node1->next);
    printf(" Key: %d\n Nome:%s\n Matricula:%d\n proximo:%d\n\n",node2->key, node2->nome, node2->matricula, node2->next);
    printf(" Key: %d\n Nome:%s\n Matricula:%d\n proximo:%d\n\n",node3->key, node3->nome, node3->matricula, node3->next);
    printf(" Key: %d\n Nome:%s\n Matricula:%d\n proximo:%d\n\n",node4->key, node4->nome, node4->matricula, node4->next);
    printf(" Key: %d\n Nome:%s\n Matricula:%d\n proximo:%d\n\n",node5->key, node5->nome, node5->matricula, node5->next);
    printf(" Key: %d\n Nome:%s\n Matricula:%d\n proximo:%d\n\n",node6->key, node6->nome, node6->matricula, node6->next);
    printf(" Key: %d\n Nome:%s\n Matricula:%d\n proximo:%d\n\n",node7->key, node7->nome, node7->matricula, node7->next);
    printf(" Key: %d\n Nome:%s\n Matricula:%d\n proximo:%d\n",node8->key, node8->nome, node8->matricula, node8->next);
    printf(" Key: %d\n Nome:%s\n Matricula:%d\n proximo:%d\n",node9->key, node9->nome, node9->matricula, node9->next);
    printf("\n************************************************************\n");
    /* Fim da incializacao os nodes com o conteudo */

    printf("\n*Inserindo na tabela hash*\n");
    insert(hash, node2);
    insert(hash, node1);
    insert(hash, node3);
    insert(hash, node4);
    insert(hash, node6);
    insert(hash, node5);
    insert(hash, node8);
    insert(hash, node7);
    insert(hash, node9);

    _show_hash_(hash);

    //Procurando 2 elementos
    search(hash, 3);
    search(hash, 2);

    //Removendo dois elementos
    remover(hash, 3);
    remover(hash, 4);

    _show_hash_(hash);

    // Pausando o sistema
    system("PAUSE");
    return 0;
}
