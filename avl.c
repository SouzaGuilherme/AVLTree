/*Rotacoes que devem ser implementadas 
Os parametros e retorno sao de escolha do aluno
	rotation_LL(); 
	rotation_RR();  
	rotation_LR();  
	rotation_RL();
Obs: facam uma funcao para cada rotacao
Obs2: Essas funcoes sao exclusivas do avl.c, pois o usuario
NAO DEVE poder fazer uma dessas operacoes (ele pode apenas
inserir e remover na arvore). Assim, esses prototipos nao devem ir
no avl.h*/

#include "avl.h"

//Funcoes de impressao da arvore ja implementadas
void print_tab(int level){
  int i;
  for (i = 0; i < level; i++ )
    printf("\t");
}

void print_tree( Nodo_AVL *current, int level ){
  if ( current == NULL ) {
    print_tab(level );
    printf("~\n");
  } else {
    print_tree( current->right, level + 1 );
    print_tab(level);
    printf ("%d\n", current->key );
    print_tree( current->left, level + 1 );
  }
}



Nodo_AVL *avl_insert(Nodo_AVL *current, int key){
}


Nodo_AVL *avl_delete(Nodo_AVL *current, int key){
}

void print_inOrder(Nodo_AVL *current){
}


void avl_destroy(Nodo_AVL *current){
}


Nodo_AVL *avl_search(Nodo_AVL *current, int key){
}


int avl_height(Nodo_AVL *raiz){
}


