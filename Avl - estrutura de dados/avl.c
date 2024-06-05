#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct No {
    int info, altura;
    struct No *esquerdo;
    struct No *direito;
} tipoAVL;

// Function prototypes
tipoAVL* criaAVL(int x);
int altura(tipoAVL* raiz);
int fatorBal(tipoAVL* raiz);
tipoAVL* rotaDDir(tipoAVL* raiz);
tipoAVL* rotaDirEsq(tipoAVL* raiz);
tipoAVL* rotaDEsq(tipoAVL* raiz);
tipoAVL* rotaEsqDir(tipoAVL* raiz);
tipoAVL* insere(tipoAVL* raiz, int x);
void inOrdem(tipoAVL* raiz);

// Function definitions

tipoAVL* criaAVL(int x) {
    tipoAVL* novo = (tipoAVL*)malloc(sizeof(tipoAVL));
    novo->info = x;
    novo->altura = 1;
    novo->esquerdo = NULL;
    novo->direito = NULL;
    return novo;
}

int altura(tipoAVL* raiz) {
    if (raiz == NULL)
        return 0;
    return raiz->altura;
}

int fatorBal(tipoAVL* raiz) {
    if (raiz == NULL)
        return 0;
    int alt_esq = altura(raiz->esquerdo);
    int alt_dir = altura(raiz->direito);
    return alt_esq - alt_dir;
}

tipoAVL* rotaDDir(tipoAVL* raiz) {
    tipoAVL* novo = raiz->direito;
    raiz->direito = novo->esquerdo;
    novo->esquerdo = raiz;
    raiz->altura = altura(raiz);
    novo->altura = altura(novo);
    return novo;
}

tipoAVL* rotaDirEsq(tipoAVL* raiz) {
    raiz->direito = rotaDEsq(raiz->direito);
    return rotaDDir(raiz);
}

tipoAVL* rotaDEsq(tipoAVL* raiz) {
    tipoAVL* novo = raiz->esquerdo;
    raiz->esquerdo = novo->direito;
    novo->direito = raiz;
    raiz->altura = altura(raiz);
    novo->altura = altura(novo);
    return novo;
}

tipoAVL* rotaEsqDir(tipoAVL* raiz) {
    raiz->esquerdo = rotaDDir(raiz->esquerdo);
    return rotaDEsq(raiz);
}

tipoAVL* insere(tipoAVL* raiz, int x) {
    if (raiz == NULL) {
        raiz = criaAVL(x);
    } else {
        if (x > raiz->info) {
            raiz->direito = insere(raiz->direito, x);
            if (fatorBal(raiz) == -2) {
                if (x > raiz->direito->info) {
                    raiz = rotaDDir(raiz);
                } else {
                    raiz = rotaDirEsq(raiz);
                }
            }
        } else {
            if (x < raiz->info) {
                raiz->esquerdo = insere(raiz->esquerdo, x);
                if (fatorBal(raiz) == 2) {
                    if (x < raiz->esquerdo->info) {
                        raiz = rotaDEsq(raiz);
                    } else {
                        raiz = rotaEsqDir(raiz);
                    }
                }
            }
        }
    }
    raiz->altura = altura(raiz);
    return raiz;
}

void inOrdem(tipoAVL* raiz) {
    if (raiz != NULL) {
        inOrdem(raiz->esquerdo);
        printf(" %d (%d)\n", raiz->info, fatorBal(raiz));
        inOrdem(raiz->direito);
    }
}

int main() {
    printf("\n-------------------------------");
    printf("\nExemplo Árvores Binárias AVL");
    printf("\n-------------------------------\n");

    printf(">> EXEMPLO\n");
    printf("a) Mostrar as rotações necessárias para a construção da seguinte árvore AVL: 9, 7, 1, 3, 4 e 8\n");

    printf("\nALV: 9 7 1 3 4  8\n\n");

    tipoAVL* raiz = NULL;
    raiz = insere(raiz, 9);
    raiz = insere(raiz, 7);
    raiz = insere(raiz, 1);
    raiz = insere(raiz, 3);
    raiz = insere(raiz, 4);
    raiz = insere(raiz, 8);

    printf("\nb) Defina em C uma estrutura de dados que possa representar uma árvore AVL\n");
    printf("\ntypedef struct No{\n\tint info, altura;\n\tstruct No *esquerdo;\n\tstruct No *direito;\n} tipoAVL;\n");

    printf("\nc) Implemente procedimento para calcular FB;\n(consta no codigo)\n");

    printf("\nd) Implemente procedimento que percorra a árvore e imprima o fator de balanceamento de cada nó em uma ordem infixada com o seguinte formato:\nn(FB), onde n é uma raiz de subárvore e FB o fator de balanceamento.\n");
    printf("\nExemplo com a arvore 5 4 3 6 7 8\n n(FB):\n----------\n");
    inOrdem(raiz);

    printf("\nf) Implemente os procedimentos de rotação simples (direita e esquerda)\n(consta no codigo)\n");
    return 0;
}
