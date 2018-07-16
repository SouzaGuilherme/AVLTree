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

// Nomes: Guilherme Souza e Thiago Heron Ávila


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

// Função auxiliar utilizada para retornar o maior elemento entre dois.
int maior(int x, int y){
  if(x >= y){
     return x;
  } 
  return y;
}

// Função auxiliar utilizada para retornar o valor absoluta da difença de altura das duas sub-árvores de um nodo. 
int factorBalancing(Nodo_AVL *no){
    return labs(avl_height(no->left) - avl_height(no->right));
}

/* Função auxiliar para retornar o menor valor da árvore, recebe como parametro um nodo, e enquanto seu filho 
*  da esquerda for diferença de nulo e percore árvore a dentro. Por fim, retorna o menor elemento.
*/
Nodo_AVL* searchLess(Nodo_AVL *atual){
    Nodo_AVL *no1 = atual;
    Nodo_AVL *no2 = atual->left;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->left;
    }
    return no1;
}

/* Função de ROTACOES para realizar o balanceamento da arvore apartir da decisoria recebida do factorBalancing, 
*  recebe como parametro um no da sub-arvore, utilizando a devida rotacao das listadas abaixo e como dito
*  anteriormente a rotacao da qual sera aplicada partira do retorno do factorBalancing, dicidindo assim se
*  ocorrera uma rotacao simples ou um dupla rotacao. (Funcoes de rotacoes listadas abaixo LL, RR, RL, LR)  
*  Por fim, retorna o no da sub-arvore balanceado.
*/
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


/*    Insert: Primeiro é verificado se o endereço do nodo passado não é NULLO, isso servira para identificar se a árvore esta
* vazia ou então como é utilizado a recursão serve para identificar se já estamos em um nó folha. Caso se encaixe, é alocado
  um novo nodo e setamos seus valores, e retorna o nodo criado para fazer a ligação entre nodos através da recursão.
*     Caso a árvore não esteja vazia, verificamos se a key(valor que vamos inserir) é menor que a key do nodo atual, se sim,
* temos que percorrer atráves da recursão para a sub-árvore da esquerda.  Se a key é maior que a key do nodo atual, temos
* que percorrer através da recursão para a sub-ávore da direita. Esse processo se repete por recursão até que um novo nodo,
* o nodo folha, seja criado. Na volta das recursões é calculado seu fator de balanceamos através de uma função auxiliar, caso
* seja maior que 2, há uma verificação em seguida para saber se a key foi adicionada na árvore da esquerda ou da direita, com
* base nisso é feita as rotações para balancear a árvore. Caso também que estamos tentando inserir já existe, é printado uma
* mensagem de aviso e retornado NULL.
*   Por fim é atualizado a altura do atual nodo e retornamos ele.    
*
*/
Nodo_AVL *avl_insert(Nodo_AVL *current, int key){
    if(current == NULL){
        Nodo_AVL *newNodo;
        if((newNodo = (Nodo_AVL *) malloc(sizeof(Nodo_AVL))) == NULL){
            printf("Nao foi possivel alocar um novo nodo ao inserir!\n");
            return NULL;
        }
        newNodo->key = key;
        newNodo->height = 0;
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



/* Delete: Primeiro verificamos se à arvorenão está vazia. Após, verificamos se o valor que estamos tentando deletar
* esta na sub-árvore à esquerda ou à direita do nodo atual. Com isso vamos percorrendo a árvore até encontrar o valor
* desejado. Ao encontrar, primeiro verificamos se ele possui nenhum ou um filho e tratamos para esses casos. Após,
* caso tenha dois filhos, procuramos o menor valor da sub-árvore a direita(o sucessor), colocamos ele em um nodo temporário,
* atualiamos os valores, deletamos o nodo com a key passada por parâmetro. Após, calculamos o fator de balanceamento, se for
* maior ou igual a 2, verificamos se foi adicionado na sub-árvore da esquerda ou direita e rotacionamos conforme necessário.
*   E por fim, e verificado o fator de balanceamento nas voltas das recursões, rotacionando e necessário e balanceando.
*/
Nodo_AVL *avl_delete(Nodo_AVL *current, int key){
    if(current == NULL){
        printf("Não existe o valor!\n");
        return NULL;
    }

    Nodo_AVL * atual = current;
    
    if(key < atual->key){ 
            atual->left = avl_delete((atual->left), key);
            if(factorBalancing(atual) >= 2){
                if(avl_height(atual->right->left) <= avl_height(atual->right->right)){
                    atual = rotation_RR(atual);
                } else {
                    atual = rotation_RL(atual);
                }
            }
    } else{
        if(key > atual->key){ 
            if((atual->right = avl_delete((atual->right), key)) != NULL){
                if(factorBalancing(atual) >= 2){
                    if(avl_height(atual->left->right) <= avl_height(atual->left->left)){
                        atual = rotation_LL(atual);
                    } else {
                        atual = rotation_LR(atual);
                    }
                }
             }
        } else {
            if(key == atual->key){
                if(atual->left == NULL || atual->right == NULL){ 
                    Nodo_AVL *oldNode = atual;
                    if(atual->left != NULL){
                        atual = atual->left;
                    } else {
                        atual = atual->right;
                    }
                    free(oldNode);
                } else {    
                    Nodo_AVL *temp = searchLess(atual->right);
                    atual->key = temp->key;
                    atual->right = avl_delete(atual->right, atual->key);
                    if(factorBalancing(atual) >= 2) {
                        if(avl_height(atual->left->right) <= avl_height(atual->left->left)){
                            atual = rotation_LL(atual);
                        } else {
                            atual = rotation_LR(atual);
                        }
                    }
                }
                // 
                return atual;
            }
        }
    }
    
    atual->height = maior(avl_height(atual->left), avl_height(atual->right)) +1;
    return atual;

}

/*  Print InOrder: Printa os elementos da árvore(left, root, right)... 
*   Key impresso entre chaves separados por espaco.
*/
void print_inOrder(Nodo_AVL *current){
	if (current == NULL){
		return;
	}
	print_inOrder(current->left);
	printf("{%d} ",current->key);
	print_inOrder(current->right);
}


/* Para remover todos os elementos da árvore é utilizado recursão, percorremos a árvore até encontrar o menor valor, damos um free
*    após os da direita, e por fim a raiz.
*/
void avl_destroy(Nodo_AVL *current){
    if(current != NULL){
        avl_destroy(current->left);
        avl_destroy(current->right);
        free(current);
        current = NULL;
    }
 
    current = NULL;
}



/*  Verificamos se o nodo é nulo, caso seja retornando null. Após, verificamos enquanto esse nodo for diferente de null
* percorremos a árvore com base se a key é maior, menor ou igual ao do atual nodo. Se a key maior, vamos para a sub-árvore
* da direita, se menor para sub-árvore da esquerda, e por fim se igual retornamos o elemento indicando que está na árvore.
*    Caso não seja encontrado, é retornado NULL.S
*/
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


/* Height: Verificamos se o nodo passado parâmetro é nulo, caso seja, indica que á árvore está vazia e retorna como altura -1.
*   Caso retorna a altura do nodo que já foi calculado/reajustado nas funções insert, delete.
*/
int avl_height(Nodo_AVL *current){
  if(current == NULL){
    return -1; 
  }
  return current->height;
}


