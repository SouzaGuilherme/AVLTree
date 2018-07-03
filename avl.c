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

int maior(int x, int y){
  if(x >= y){
     return x;
  } 
  return y;
}

int factorBalancing(Nodo_AVL *no){
    //printf("FB: %d\n", avl_height(no->left) - avl_height(no->right));
    //printf("Height no-left: %d\n", avl_height(no->left));
    //printf("Height no->right: %d\n\n", avl_height(no->right));
    return labs(avl_height(no->left) - avl_height(no->right));
    // labs -> returns the absolute value of x;
}


Nodo_AVL* rotation_LL(Nodo_AVL *raiz) {

    Nodo_AVL *no;
    no = raiz->left;
    raiz->left = no->right;
    no->right = raiz;
    raiz->height = maior(avl_height(raiz->left), avl_height(raiz->right)) + 1;
    no->height = maior(avl_height(no->left), raiz->height) + 1;
    return no;
  
}

Nodo_AVL* rotation_RR(Nodo_AVL *raiz) {
    Nodo_AVL *no; 
    no = raiz->right;
    raiz->right = no->left;
    no->left = raiz;
    raiz->height = maior(avl_height(raiz->left), avl_height(raiz->right)) + 1;
    no->height = maior(avl_height(no->right), raiz->height) + 1;
    return no;     
}

Nodo_AVL* rotation_RL(Nodo_AVL *raiz){
  raiz->right = rotation_LL(raiz->right);
  raiz = rotation_RR(raiz);
  return raiz;
}

Nodo_AVL* rotation_LR(Nodo_AVL *raiz) {
    raiz->left = rotation_RR(raiz->left);
    raiz = rotation_LL(raiz);
    return raiz;
}


Nodo_AVL *avl_insert(Nodo_AVL *current, int key){

    if(current == NULL){
        Nodo_AVL *newNodo;
        if((newNodo = (Nodo_AVL *) malloc(sizeof(Nodo_AVL))) == NULL){
            printf("Nao foi possivel alocar um novo nodo ao inserir!\n");
            return NULL;
        }
        newNodo->key = key;
        newNodo->height = 1;
        newNodo->left = NULL;
        newNodo->right = NULL;
        current = newNodo;
        return current;
    }



    Nodo_AVL *atual = current;

    if(key < atual->key){ 
        if((atual->left = avl_insert((atual->left), key)) != NULL){
        
            if(factorBalancing(atual) >= 2){
                if(key < (atual->left->key)){ 
                    atual = rotation_LL(atual);
                } else {
                    atual = rotation_LR(atual);
                }
            }
        }
    } else {
        if (key > atual->key){
            if((atual->right = avl_insert((atual->right), key)) != NULL){
                if(factorBalancing(atual) >= 2){
                    if(key < (atual->right->key)){
                        atual = rotation_RL(atual);
                    } else {
                        atual = rotation_RR(atual);
                    }
                }
            }
        } else {
            printf("O valor já foi inserido!\n");
            return NULL;
        }
    }

    
    atual->height = maior(avl_height(atual->left), avl_height(atual->right)) +1;
    return atual;
}








Nodo_AVL *maiorDireita(Nodo_AVL *current){
	Nodo_AVL *nodoAcesso = current;
	
	if (nodoAcesso->right != NULL){
		return maiorDireita(nodoAcesso->right);
	}else{
		Nodo_AVL *nodoAUX = nodoAcesso;
		if (nodoAcesso->left != NULL){
			nodoAcesso = nodoAcesso->left;
		}else{
			nodoAcesso = NULL;
		}
		return nodoAUX;
	}
}

Nodo_AVL *procuraMenor(Nodo_AVL *current){
	Nodo_AVL *nodo1 = current;
	Nodo_AVL *nodo2 = current->left;
	while(nodo2 != NULL){
		nodo1 = nodo2;
		nodo2 = nodo2->left;
	}
	return nodo1;
}


Nodo_AVL *avl_delete(Nodo_AVL *current, int key){
	Nodo_AVL *nodoAcesso = current;
	// Quando for nulo
	if ( *nodoAcesso == NULL ){
		printf("Aqui e nullo\n");
		return nodoAcesso;
	}

	// verifico para qual lado o valor deve estar
	if (key < nodoAcesso->key){
		nodoAcesso->left = avl_delete(nodoAcesso->left, key);
		// testando
		if(factorBalancing(nodoAcesso) >= 2){
      		if(key < (nodoAcesso->left->key)){ 
       			nodoAcesso = rotation_LL(nodoAcesso);
            } else {
                nodoAcesso = rotation_LR(nodoAcesso);
            }
        }

	}else if (key > nodoAcesso->key){
		nodoAcesso->right = avl_delete(nodoAcesso->right, key);
        // testando
		if(factorBalancing(nodoAcesso) >= 2){
      		if(key < (nodoAcesso->left->key)){ 
       			nodoAcesso = rotation_LL(nodoAcesso);
            } else {
                nodoAcesso = rotation_LR(nodoAcesso);
            }
        }

	}else{
		// nodo o qual quero deletar afinal
		if ((nodoAcesso->right == NULL) || (nodoAcesso->left == NULL)){
			Nodo_AVL *nodoAUX = nodoAcesso;
			if (nodoAcesso->left != NULL){
				nodoAcesso = nodoAcesso->left;		
			}else{
				nodoAcesso = nodoAcesso->right;
			}
			free(nodoAUX);
			
		}else{
			Nodo_AVL *nodoTemp = procuraMenor(nodoAcesso->right);
			nodoAcesso->key = nodoTemp->key;
			avl_delete(&(nodoAcesso->right), nodoAcesso->key);
			// testando
			if(factorBalancing(nodoAcesso) >= 2){
      			if(key < (nodoAcesso->left->key)){ 
       				nodoAcesso = rotation_LL(nodoAcesso);
            	} else {
                nodoAcesso = rotation_LR(nodoAcesso);
            }
        }
        return current;
	}
	return current;
}
}

void print_inOrder(Nodo_AVL *current){
}


void avl_destroy(Nodo_AVL *current){
    if(current == NULL){
        avl_destroy(current->left);
        avl_destroy(current->right);
        free(current);
    }
    current = NULL;
}


Nodo_AVL *avl_search(Nodo_AVL *current, int key){
    

    if(current == NULL){
        return NULL;
    }

    Nodo_AVL *atual = current;

    
    while(atual != NULL){
        if(key == atual->key){
            return atual;
        }
        if(key > atual->key){
            atual = atual->right;
        } else {
            atual = atual->left;
        }
        
    }
    return NULL;
}

int avl_height(Nodo_AVL *current){
  if(current == NULL){
    return 0; 
  }
  return current->height;
}


