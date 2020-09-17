#include "estruturas.h"

#define null NULL

int max(int x, int y){
    return (x > y) ? x : y;
}

node_bin *init_tree(node_bin *tree){
    tree = (node_bin*)malloc(sizeof(node_bin));
    tree = null;
    return tree;
}

// Inserir na arvore
void insert_on_tree(int info, node_bin **tree){
    node_bin *newNode;
    if((*tree) == null) {
        newNode = (node_bin*)malloc(sizeof(node_bin));
        newNode->info = info;
        newNode->left = newNode->right = null;
        (*tree) = newNode;
    } else{
        if((*tree)->info > info) {
            insert_on_tree(info, &(*tree)->left);
        } else if((*tree)->info < info) {
            insert_on_tree(info, &(*tree)->right);
        } else {
            printf("Elemento ja esta presente na arvore!!!\n\n\n");
        }
    }
}
//

// Inserir na arvore, recursivamente
node_bin *insertNode(int info) {
    node_bin *tempNode = (node_bin*)malloc(sizeof(node_bin));
    tempNode->info = info;
    tempNode->right = tempNode->left = null;

    return tempNode;
}

node_bin *insertOnTree(int info, node_bin *tree) {
    if(tree == null)
        return insertNode(info);

    if(info < tree->info) {
        tree->left = insertOnTree(info, tree->left);
    } else {
        tree->right = insertOnTree(info, tree->right);
    }

    return tree;
}
//

void emOderm(node_bin *tree){
    if(tree != null) {
        emOderm((tree->left));
        printf("%d\n", tree->info);
        emOderm((tree->right));
    }
}

void preOderm(node_bin *tree){
    if(tree != null) {
        printf("%d\n", tree->info);
        preOderm((tree->left));
        preOderm((tree->right));
    }
}

void posOderm(node_bin *tree){
    if(tree != null) {
        posOderm((tree->left));
        posOderm((tree->right));
        printf("%d\n", tree->info);
    }
}
//

// Ex 1 - percurso em largura
// calcula a altura e pega a mais alta.
int height(node_bin *tree) {
    if(tree == null) return 0;

    // Calculando as alturas.
    int left_height = height(tree->left);
    int right_height = height(tree->right);
    // Usa a altura de tamanho maior
    if(left_height > right_height) return left_height + 1;
    else return right_height + 1;
}

int height2(node_bin *tree) {
    if(tree == null) return 0;
    return 1+max(height2(tree->left),height2(tree->right));
}

bool check_balance_by_height(node_bin *tree) {
    int left_height, right_height;

    if(tree == null) return true;
    left_height = height(tree->left);
    right_height = height(tree->right);

    if(abs(left_height - right_height) <= 1 && (check_balance_by_height(tree->left) && check_balance_by_height(tree->right)))
        return true;
    return false;
}

// Mostra o node do nivel atual da arvore.
void showLevel(node_bin *tree, int level){
    if(tree == null) return;
    if(level == 1) printf("%d ", tree->info);
    else if(level > 1) {
        showLevel(tree->left, level - 1);
        showLevel(tree->right, level - 1);
    }
}
// Mostra o nivel da arvore em ordem transversal.
void showLevelOder(node_bin *tree) {
    int tree_height = height(tree);
    int i = 1;
    for(i; i <= tree_height; i++)
        showLevel(tree, i);
}
//

// Ex 2 - numero de folhas
unsigned int getLeafCount(node_bin *tree) {
    if(tree == null) return 0;                                         //se nao existir folha, retorna 0.
    if(tree->left == null && tree->right == null) return 1;            //chega na condicao do conceito de folha.
    else return getLeafCount(tree->left) + getLeafCount(tree->right);  //retorna a soma dos valores da function
}
//

// Ex 3 - buscar um valor na arvore
// Buscas em arvores
node_bin *searchTree(int info, node_bin *tree) {
    if (tree == null || tree->info == info)
        return tree;
    if (tree->info < info)
        return searchTree(info, tree->right);
    else return searchTree(info, tree->left);
}
//

// Ex 4 - espelhar uma arvore respeitando seus filhos.
node_bin *copyTree(node_bin *tree){
    if(tree == null) return null;
    else {
        node_bin  *newNode = (node_bin*)malloc(sizeof(node_bin));

        newNode->info = tree->info;
        newNode->left = tree->left;
        newNode->right = tree->right;

        newNode->left = copyTree(tree->left);
        newNode->right = copyTree(tree->right);

        return newNode;
    }
}

void mirror(node_bin *tree) {
    if(tree == null) return;
    else {
        node_bin *temp;
        // A troca ocorre recursivamente.
        mirror(tree->left);
        mirror(tree->right);

        // Trocando o lado dos nodes.
        temp = tree->left;
        tree->left = tree->right;
        tree->right = temp;
    }
}

node_bin *mirrored_tree(node_bin *tree, node_bin *mirror_tree){
   mirror_tree = copyTree(tree);    // copia a arvore atual
   mirror(mirror_tree);             // espelha a copia
   return mirror_tree;              // retorna o espelho
}
//

// Ex 5 - expressao validas em arvores binarias.
node_exp *init_tree_exp(node_exp *tree_exp){
    tree_exp = null;
    return tree_exp;
}

node_exp *insert_exp(char posfix[]){
    node_exp *root, *newNode;
    node_exp *stack[100];
    int i = 0, top = -1;
    for(i; posfix[i] != '\0'; i++) {
        newNode = (node_exp*)malloc(sizeof(node_exp));
        newNode->value = posfix[i];
        newNode->left = newNode->right = null;
        if(isalpha(posfix[i]) || isdigit(posfix[i])) {
            stack[++top] = newNode;
        } else {
            newNode->right = stack[top--];
            newNode->left = stack[top--];
            stack[++top] = newNode;
        }
    }
    root = stack[top--];
    return root;
}

bool validate_exp_tree(node_exp *tree) {
    if(tree == null) return true;

    if(isalpha(tree->value) == true) {
        if(isalpha(tree->right->value) == true || isalpha(tree->left->value) == true) {
            return false;
        } else if (isalpha(tree->right->value) == false || isalpha(tree->left->value) == false) {
            validate_exp_tree(tree);
        }
    }

    return false;
}
//

// Ex 6 - mostrar uma arvore binaria de expressao, pos ordem e pre ordem.
void preOdermExp(node_exp *tree_exp){
    if(tree_exp != null) {
        printf("%c", tree_exp->value);
        preOdermExp((tree_exp->left));
        preOdermExp((tree_exp->right));
    }
}

void emOdermExp(node_exp *tree_exp){
    if(tree_exp != null) {
        emOdermExp((tree_exp->left));
        printf("%c", tree_exp->value);
        emOdermExp((tree_exp->right));
    }
}

void posOdermExp(node_exp *tree_exp){
    if(tree_exp != null) {
        posOdermExp((tree_exp->left));
        posOdermExp((tree_exp->right));
        printf("%c", tree_exp->value);
    }
}
//

// Ex 7 - calcula  o balanceamento em todos nos da arvores avl.
// Inserir na arvore, recursivamente
node_avl *init_tree_avl(node_avl *tree_avl){
    tree_avl = null;
    return tree_avl;
}

int height_avl_node(node_avl *tree_avl) {
    if(tree_avl == null) return 0;
    return tree_avl->h;
}

int height_avl(node_avl *tree_avl){
    if(tree_avl == null) return -1;

    int he = height_avl(tree_avl->left);
    int hd = height_avl(tree_avl->right);

    if(he > hd) return he + 1;
    return hd + 1;
}

int fator(node_avl *tree_avl) {
    if(tree_avl != null)
        return height_avl(tree_avl->left) - height_avl(tree_avl->right);
    return -1;
}

void rotate_left(node_avl **tree_avl) {
    node_avl *aux_node = (*tree_avl)->right;

    (*tree_avl)->right = aux_node->left;
    aux_node->left = (*tree_avl);
    (*tree_avl) = aux_node;

    //(*tree_avl)->h = max(height_avl((*tree_avl)->left),  height_avl((*tree_avl)->right) + 1);
}

void rotate_right(node_avl **tree_avl) {
    node_avl *aux_node = (*tree_avl)->left;

    (*tree_avl)->left = aux_node->right;
    aux_node->right = (*tree_avl);
    (*tree_avl) = aux_node;

    //(*tree_avl)->h = max(height_avl((*tree_avl)->left),  height_avl((*tree_avl)->right) + 1);
}

int getBalance(node_avl *tree_avl){
    if(tree_avl == null) return 0;
    return (height_avl(tree_avl->left) - height_avl(tree_avl->right));
}

void insert_on_tree_avl(int info, node_avl **tree_avl) {
    int fb = 0;
    if(*tree_avl == null) {
        node_avl *newNode = (node_avl*)malloc(sizeof(node_avl));
        newNode->info = info;
        newNode->h = 1;
        newNode->balance = 0;
        newNode->left = newNode->right = null;
        *tree_avl = newNode;
    } else if((*tree_avl)->info > info){
        insert_on_tree_avl(info, &(*tree_avl)->left);
    } else if((*tree_avl)->info < info){
        insert_on_tree_avl(info, &(*tree_avl)->right);
    } else {
        printf("\nValores iguais nao sao permitidos na AVL!!!\n\n");
        return;
    }

    fb = fator(*tree_avl);

    if(fb >= 2){
        if(fator((*tree_avl)->right) > 0) {
            rotate_left(&(*tree_avl));
        } else {
            rotate_right(&(*tree_avl)->right);
            rotate_left(&(*tree_avl));
        }
    } else if(fb <= -2) {
        if(fator((*tree_avl)->left) > 0) {
            rotate_left(&(*tree_avl)->left);
            rotate_right(&(*tree_avl));
        } else rotate_right(&(*tree_avl));
    }
}

void preOdermAvl(node_avl *tree_avl){
    if(tree_avl != null) {
        printf("%d\n", tree_avl->info);
        preOdermAvl((tree_avl->left));
        preOdermAvl((tree_avl->right));
    }
}
//

// Ex 8

//

// Ex 9
/* Metodo recursivo */
node_bin *min(node_bin *tree){
    if(tree == null) {
        return tree;
    } else {
        node_bin *left_node, *right_node, *found_node;
        left_node = min(tree->left);
        right_node = min(tree->right);

        if(left_node->info > right_node->info) found_node = right_node;
        if(right_node->info > left_node->info) found_node = left_node;
        return found_node;
    }
}

/* Nao recursivo */
node_bin *min2(node_bin *tree){
    node_bin *aux = tree;

    if(aux == null) return aux;

    while(aux->left != null) {
        aux = aux->left;
    }
    return aux;
}

//

// Ex 10
bool has_negative_key(node_bin *tree){
    node_bin *aux = tree;

    if(aux == null) return false;

    while(aux->left != null) {
        aux = aux->left;
    }

    if(aux->info < 0) {
        return true;
    }

    return false;
}
//

// Ex 11
// Se chegar no ultimo no da arvore e nao houver uma discrepancia na arvore, ela eh binaria de busca valida.
/*
bool isBst(node_bin *tree, int min, int max){
    if(tree == null) return true;
    if(tree->info < min || tree->info > max) return false;
    return ((isBst(tree->left, min, tree->info-1) && isBst(tree->right, tree->info+1, max)));
}
*/

bool isBst(node_bin *tree) {
    static node_bin *prev = null;

    if (tree) {
        if (!isBst(tree->left))
            return false;

        if (prev != NULL && tree->info <= prev->info)
            return false;
        prev = tree;
        return isBst(tree->right);
    }
    return true;
}
//

// Ex 12 arvore com: 20,25,10,5,12,22,23, deleta-se 20, quem pode substituir ele ?.
// Pode-se usar o maior dos menores, nesse caso o 12 ou o node 25, primeiro maior.
//

// Ex 13
lt *CreateNode(int info){
    lt *node = (lt*)malloc(sizeof(lt));
    node->info = info;
    node->next = null;
    return node;
}

void addNodeToList(lt **head, int info){
    lt *newNode = CreateNode(info);
    if(*head == null || (*head)->info >= info) {
        newNode->next = (*head);
        (*head) = newNode;
    } else {
        lt *current = (*head);
        while(current->next != null && current->next->info < info) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void preOderToList(node_bin *tree,lt **head){
    if(tree != null) {
        addNodeToList(&(*head),tree->info);
        preOderToList((tree->left),&(*head));
        preOderToList((tree->right),&(*head));
    }
}

void showList(lt *list){
    lt *aux = list;
    printf("Elementos da lista:");
    if(aux == null) printf("Lista vazia!!!\n\n\n");
    while(aux != null){
        printf("%d ",aux->info);
        aux = aux->next;
    }
}
//


int main() {
    printf("Lista de Exercicios - Arvores Binarias\n");

    node_bin *tree = init_tree(tree);
    node_exp *tree_exp = init_tree_exp(tree_exp);
    node_avl *tree_avl = init_tree_avl(tree_avl);
    lt *head_list = null;

    insert_on_tree(50,&tree);
    insert_on_tree(30,&tree);
    insert_on_tree(20,&tree);
    insert_on_tree(40,&tree);
    insert_on_tree(70,&tree);
    insert_on_tree(60,&tree);
    insert_on_tree(80,&tree);


    /*
    tree = insertOnTree(50,tree);
    insertOnTree(30,tree);
    insertOnTree(20,tree);
    insertOnTree(40,tree);
    insertOnTree(70,tree);
    insertOnTree(60,tree);
    insertOnTree(80,tree);
     */

    printf("\n");
    printf("Arvore a ser utilizada - em Ordem se insercao\n");
    emOderm(tree);
    printf("\n");

    printf("Exercicio 1 - mostrar a arvore por nivel\n");
    showLevelOder(tree);

    printf("\n\nVerificando se a arvore eh perfeitamente balanceada:");
    if(check_balance_by_height(tree) == true) printf(" Sim\n");
    else printf(" Nao\n");

    printf("\n\nExercicio 2 - numero de folhas\n");
    printf("O numero de folhas eh: %d", getLeafCount(tree));

    printf("\n\nExercicio 3 - achar um elemento na arvore\n");
    node_bin *found = searchTree(20,tree);
    printf("Achado: %d em:\n",found->info);
    preOderm(tree);


    printf("\n\nExercicio 4\n");
    node_bin *other_tree = null;
    other_tree = init_tree(other_tree);
    other_tree = mirrored_tree(tree, other_tree);

    printf("\n Arvore 1:\n");
    preOderm(tree);
    printf("\n");
    printf("\nSeu espelho:\n");
    preOderm(other_tree);
    printf("\n");

    printf("\n\nExercicio 5\n");
    char postfix[20];
    printf("Digite a expressao posfixa:");
    gets(postfix);
    fflush(stdin);
    tree_exp = insert_exp(postfix);

    printf("\n\nExercicio 6\n");
    printf("Pre ordem:\n");
    preOdermExp(tree_exp);
    printf("\n");

    printf("Em ordem:\n");
    emOdermExp(tree_exp);
    printf("\n");

    printf("Pos ordem:\n");
    posOdermExp(tree_exp);
    printf("\n");

    printf("\n\nExercicio 7\n");

    /*

    insert_on_tree_avl(50, &tree_avl);
    insert_on_tree_avl(20, &tree_avl);
    insert_on_tree_avl(30, &tree_avl);
    insert_on_tree_avl(40, &tree_avl);
    insert_on_tree_avl(60, &tree_avl);
    insert_on_tree_avl(70, &tree_avl);
    insert_on_tree_avl(80, &tree_avl);
    printf("Pre ordem avl:\n");
    preOdermAvl(tree_avl);

    */


    printf("\n\nExercicio 8\n");

    printf("\n\nExercicio 9\n");
    node_bin *found2 = min2(tree);
    printf("Menor achado na arvore binaria: %d\n", found2->info);

    printf("\n\nExercicio 10\n");
    bool flag = has_negative_key(tree);
    if (flag == true) printf("Existe chave negativa!!!\n");
    else printf("Nao existe chave negativa!!!\n");

    printf("\n\nExercicio 11\n");
    flag = isBst(tree);
    if (flag == true) printf("Eh uma arvore valida!!!\n");
    else printf("Nao eh uma arvore valida!!!\n");

    printf("\n\nExercicio 12\n");
    printf("Teorico, resolvido na mao... \n");

    printf("\n\nExercicio 13\n");
    printf("Percorrendo arvore e criando uma lista ordenada com os elemntos...\n\n");
    preOderToList(tree,&head_list);
    showList(head_list);


    return 0;
}
