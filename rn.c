#include"rn.h"
#include<math.h>
#include<string.h>

void help(){

	printf("-h			: mostra o help\n");
	printf("-o <arquivo>		: redireciona a saida para o ‘‘arquivo’’\n");
	printf("-f <arquivo>		: indica o ‘‘arquivo’’ que contém os dados a serem adicionados na Rubro Negra\n");
	printf("-m			: imprime o menor elemento da AVL\n");
	printf("-M			: imprime o maior elemento da AVL\n");
	printf("-a <elemento>		: imprime o antecessor na AVL do ‘‘elemento’’ ou caso contrário imprime -1\n");
	printf("-s <elemento>		: imprime o sucessor na AVL do ‘‘elemento’’ ou caso contrário imprime -1\n");
};

no_rn* treeMax(no_rn* raiz){
	if(raiz->dir != NULL && raiz != NULL){
		treeMax(raiz->dir);
	}else{
		return raiz;
	}
};

no_rn* treeMin(no_rn* raiz){
	if(raiz->esq != NULL && raiz != NULL){
		treeMin(raiz->esq);
		
	}else{
		return raiz;
	}
};

no_rn* treeSuc(no_rn* raiz, no_rn* dado){
	no_rn* aux;
	aux = treeBusca(raiz, dado);
	
	if(aux != NULL){
	
		if(aux->dir != NULL && raiz != NULL)
			return treeMin(aux->dir);
		
		no_rn* y = aux->pai;
		while(y != NULL && aux == y->dir){
			aux = y;
			y = y->pai;	
		}
		return y;
		
	}
	
	return NULL;
	
};

no_rn* treeAnt(no_rn* raiz, no_rn* dado){
	no_rn* aux;
	aux = treeBusca(raiz, dado);
	
	if(aux != NULL){
	
		if(aux->esq != NULL && raiz != NULL)
			return treeMax(aux->esq);
	
		no_rn* y = aux->pai;
		while(y != NULL && aux == y->esq){
			aux = y;
			y = y->pai;	
		}
		return y;
	}
	return NULL;		
};

no_rn* treeBusca(no_rn* raiz, no_rn* dado){
	if(raiz != NULL){
		if(raiz->chave == dado->chave){
			return raiz;		
		}else{	
			if(dado->chave > raiz->chave){
				return treeBusca(raiz->dir, dado);
			}else{
				return treeBusca(raiz->esq, dado);
			}
		}
	}
};


void trocarCor(no_rn* x){

	x->cor = !x->cor;
	if(x->esq != NULL){
		x->esq->cor = !x->cor;
	}
	if(x->dir != NULL){
		x->dir->cor = !x->cor;
	}
};





no_rn* lerNo(int valor){
	no_rn* novo = (no_rn*)malloc(sizeof(no_rn));
	novo->esq = NULL;
	novo->dir = NULL;
	novo->pai = NULL;
	novo->cor = 1;
	novo->chave = valor;
	
	return novo;
	
};


int cor(no_rn*  x){
	if(x == NULL){
		return 0;
	}else{
		return x->cor;
	}
};

int treeInserir(RN* rn, no_rn* z){
	no_rn* ant = NULL;
	no_rn* atual = rn->raiz;
	while(atual != NULL){
		ant = atual;
		if(atual->chave == z->chave){
		        //printf("Duplicado\n");
			free(z);
			return 0;	
		}		
		if(z->chave > atual->chave){
			atual = atual->dir;		
		}else{
			atual = atual->esq;
		}
	}
	z->pai = ant;
	if(ant == NULL){
		rn->raiz = z;
		z->cor = 0;
	}else{ 
		if( z->chave > ant->chave)
			ant->dir = z;	
		else
			ant->esq = z;
	}
	
	treeBalancear(rn, z);
	
	return 1;	
	
};

void treeBalancear(RN* rn, no_rn* z){
	no_rn* aux1 = z;
	while(cor(aux1->pai) == 1){
	
		no_rn* aux = z->pai;	
		if(cor(z->pai) == 1 && cor(z->pai->pai->esq) == 0){
			if(z->chave > aux->chave){//no vermelho inserido esta a direira do pai vermelho
				z = rotacaoEsq(aux->pai);//erro esta aqui
				if(z->pai == NULL){
					rn->raiz = z;
					trocarCor(z);
				}else{
					trocarCor(z);
					z = z->pai;
				}
				
			}else{//senao esta a esquerda		
				if(cor(z->pai) == 1 && cor(z->pai->pai->esq) == 0){
					z = rotacaoDuplaEsq(aux->pai);										
					if(z->pai == NULL){
						trocarCor(z);
						rn->raiz = z;
					}else{
						trocarCor(z);
							
					}				
				}
			}			
		}else{
			aux = z->pai;
			if(cor(z->pai) == 1 && cor(z->pai->pai->dir) == 1){
				trocarCor(z->pai->pai);
				z = z->pai->pai;
				
			}else{
					
				if(cor(z->pai) == 1 && cor(z->pai->pai->dir) == 0){
					if(z->chave > aux->chave){//no vermelho inserido esta a dir do pai vermelho
						z = rotacaoDuplaDir(aux->pai);
						if(z->pai == NULL){
							trocarCor(z);
							rn->raiz = z;
						}else{
							trocarCor(z);
							
						}		
					}else{//senao esta a esquerda
						if(cor(z->pai) == 1 && cor(z->pai->pai->dir) == 0){
							z = rotacaoDir(aux->pai);
							if(z->pai == NULL){
								trocarCor(z);
								rn->raiz = z;
							}else{
								trocarCor(z);
								
							}	
						}
					}			
				}else{
					if(cor(z->pai) == 1 && cor(z->pai->pai->dir) == 1){
						trocarCor(z->pai->pai);
						z = z->pai->pai;
					}		
				}			
			}		
		}
		
		aux1 = z;
	}
	
	//rn->raiz = aux1;
	rn->raiz->cor = 0;
};

no_rn* rotacaoDir(no_rn* raiz){
	no_rn* temp1 = raiz;
	no_rn* temp2 = temp1->esq;	
	
	raiz->esq = temp2->dir;		
	
	if(temp2->dir != NULL){	
		temp2->dir->pai = raiz;	
	}
	temp2->dir = raiz;
	
	if(raiz->pai != NULL){
		
		if(raiz->pai->dir == temp2->pai){			
			raiz->pai->dir = temp2;
		}
		if(raiz->pai->esq == temp2->pai){			
			raiz->pai->esq = temp2;
		}		
	}
	temp2->pai = temp1->pai;
	temp1->pai = temp2;		
	temp1 = temp2;
	return temp1;
	
};
no_rn* rotacaoEsq(no_rn* raiz){
	no_rn* temp1 = raiz;
	no_rn* temp2 = temp1->dir;
	
	raiz->dir = temp2->esq;
	
	if(temp2->esq != NULL){	
		temp2->esq->pai = raiz;	
	}
	
	temp2->esq = raiz;	
	
	if(raiz->pai != NULL){
		
		if(raiz->pai->dir == temp2->pai){			
			raiz->pai->dir = temp2;
		}
		if(raiz->pai->esq == temp2->pai){			
			raiz->pai->esq = temp2;
		}		
					
	}
	temp2->pai = temp1->pai;
	temp1->pai = temp2;	
	temp1 = temp2;		
	return temp1;		
		
};
no_rn* rotacaoDuplaDir(no_rn* raiz){
	raiz = rotacaoEsq(raiz->esq);
	raiz = rotacaoDir(raiz->pai);	
	return raiz;
};
no_rn* rotacaoDuplaEsq(no_rn* raiz){	
	raiz = rotacaoDir(raiz->dir);	
	raiz = rotacaoEsq(raiz->pai);
	return raiz;
};

void lerArquivo(RN* rn, char *argv){
	FILE *fp;	
	int dado = 0;
	no_rn* dado1 = (no_rn*) malloc(sizeof(no_rn));	
	int cont = 0;
	int i;
	for(i = strlen(argv) - 3; i < strlen(argv);i++){
		if(argv[i] == 'b' ^ argv[i] == 'i' ^ argv[i] == 'n'){
			cont++;
		}	
	}
	if(cont == 3){
		fp = (FILE *) fopen(argv, "rb");	
		if(fp != NULL){			
			while((fread(dado1, sizeof(no_rn), 1, fp))){
				treeInserir(rn, lerNo(dado1->chave));
			}		
			fclose(fp);		
		}else{
			printf("Erro na abertura do arquivo!\n");
		}
	
	}else{
		fp = (FILE *) fopen(argv, "r");	
		if(fp != NULL) {
			while(fscanf(fp, "%i\n", &dado) != EOF){
					treeInserir(rn, lerNo(dado));
			}		
			fclose(fp);		
		}else{
			printf("Erro na abertura do arquivo!\n");
		}
	
	
	}
	

};
void treeSalvar(RN* rn, char *argv){
	FILE *fp;	
	no_rn *dado = (no_rn *) malloc(sizeof(no_rn));	
	fp = (FILE *) fopen(argv, "wb");	
	if(fp != NULL) {
		lerTree(rn->raiz, fp);
		fclose(fp);		
	}else{
		printf("Erro na abertura do arquivo!\n");
	}
};

void lerTree(no_rn* raiz, FILE *fp){
	if(raiz != NULL){
		fprintf (fp, " (");
		if((raiz)->cor == 0){
			fprintf (fp, "%dN", (raiz)->chave);			
		}else{
			fprintf (fp, "%dR", (raiz)->chave);
		}	
		lerTree(raiz->esq, fp);
		lerTree(raiz->dir, fp);
		if(raiz->esq == NULL ^ raiz->dir == NULL){
			fprintf (fp, "(x)");
		}		
		fprintf (fp, ")");
	}

};

void exibirEmOrdem(no_rn* raiz){
	if(raiz != NULL){
		exibirEmOrdem(&(*(raiz->esq)));
		printf("%d\n", (raiz)->chave);
		exibirEmOrdem(&(*(raiz->dir)));
	}
};

void exibirPreOrdem(no_rn* raiz){
	if(raiz != NULL){
		fprintf (stdout, " (");		
		if((raiz)->cor == 0){
			fprintf (stdout, "%dN", (raiz)->chave);			
		}else{
			fprintf (stdout, "%dR", (raiz)->chave);
		}	
		exibirPreOrdem(&(*(raiz->esq)));
		exibirPreOrdem(&(*(raiz->dir)));
		if(raiz->esq == NULL ^ raiz->dir == NULL){
			fprintf (stdout, "(x)");
		}		
		fprintf (stdout, ")");
	}
};

void exibirPosOrdem(no_rn* raiz){
	if(raiz != NULL){
		exibirPosOrdem(&(*(raiz->esq)));
		exibirPosOrdem(&(*(raiz->dir)));
		printf("%d\n", (raiz)->chave);
	}
};


