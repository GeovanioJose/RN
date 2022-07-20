#ifndef __RN_H__
#define __RN_H__

#include<stdio.h>
#include<stdlib.h>

typedef struct NO{
	int chave;
	int cor; //0 ou 1 
	struct NO* esq;
	struct NO* dir;
	struct NO* pai;
}no_rn;

typedef struct rn RN; 

struct rn{
	struct NO* raiz;
};

no_rn* lerNo(int valor);

void treeBalancear(RN* rn, no_rn* dado);
void treeSalvar(RN* rn, char *argv);
void lerTree(no_rn* raiz, FILE *fp);
void lerArquivo(RN* rn, char *argv);
no_rn* treeMax(no_rn* raiz);
no_rn* treeMin(no_rn* raiz);
no_rn* treeAnt(no_rn* raiz, no_rn* dado);
no_rn* treeSuc(no_rn* raiz, no_rn* dado);
no_rn* treeBusca(no_rn* raiz, no_rn* dado);
int treeInserir(RN* rn, no_rn* dado);
int treefator(no_rn* raiz);
void exibirPreOrdem(no_rn* raiz);
void exibirPosOrdem(no_rn* raiz);
void exibirEmOrdem(no_rn* raiz);
int cor(no_rn*  x);
void trocarCor(no_rn* x);
no_rn* rotacaoEsq(no_rn* raiz);
no_rn* rotacaoDir(no_rn* raiz);
no_rn* rotacaoDuplaEsq(no_rn* raiz);
no_rn* rotacaoDuplaDir(no_rn* raiz);
void help();

#endif
