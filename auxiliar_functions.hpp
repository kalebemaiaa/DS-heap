#include <iostream>
#include <stdlib.h>

#define NULLVAL -2147483647

using namespace std;

typedef struct Node {
    int iData;
    Node *ptrLeft, *ptrRight;
} Node;

Node *createNode(int iValue) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode -> ptrLeft = nullptr;
    newNode -> ptrRight = nullptr;
    newNode -> iData = iValue;
    return newNode;
}

int deleteNode(Node *ptrNoh) {
    int aux = ptrNoh -> iData;
    free(ptrNoh);
    return aux;
}

void insertNode(Node **root, int iValue) {
    if(!(*root)){
        *root = createNode(iValue);
        return;
    }
    if(iValue < (*root) -> iData){
        insertNode(&((*root) -> ptrLeft), iValue);
        return;
    } 
    else insertNode(&((*root) -> ptrRight), iValue);
}

/*
    OTIMIZAR ESSA FUNCAO
*/
void printGalho(int iTotalTabs, char cDirection) {
    for(int i = iTotalTabs - 1; i > 0; i--)
        cout << "\t";
    if(iTotalTabs == 0) return;
    if(cDirection == '/')
        cout << cDirection << "‾‾‾  ";
    else
        cout << cDirection << "___  ";
}

/*
    OTIMIZAR ESSA FUNCAO
*/
void printTree(Node *root, int iTabulation, char cDirection) {
    if(!root){
        printGalho(iTabulation, cDirection);
        cout << "X" << endl;
        return;  
    }
    printTree(root -> ptrLeft, iTabulation + 1, '/');
    printGalho(iTabulation, cDirection);
    cout << root -> iData << endl;
    printTree(root -> ptrRight, iTabulation + 1,'\\');
}

void printVertical(Node *root) {
    if(!root) return;

}

/*
    DEVOLVE O TAMANHO DA ARVORE
*/
int getSize(Node *root) {
    if(!root) return 0;
    return getSize(root -> ptrLeft) + getSize(root -> ptrRight) + 1;
}

/*
    DEVOLVE A ALTURA DE UMA ARVORE
*/
int getHeight(Node *root) {
    if(!root) return 0;
    int iHeightLft = getHeight(root -> ptrLeft), iHeightRgt = getHeight(root -> ptrRight);
    
    if(iHeightLft > iHeightRgt)  
        return iHeightLft + 1;
    return iHeightRgt + 1;
}

Node *searchValue(Node *root, int iValue) {
    if(!root) return nullptr;
    if(root -> iData == iValue) return root;
    if(root -> iData > iValue) return searchValue(root -> ptrLeft, iValue);
    return searchValue(root -> ptrRight, iValue);
}

/*
    FUNCAO AUXILIAR PARA ESCREVER ARQUIVO
*/
int writingComplete(Node *root, FILE *out) {
    int s = 0;
    if(!root){
        fprintf(out, "%i ", NULLVAL);
        return s;
    }

    fprintf(out, "%i ", root -> iData);
    s += writingComplete(root -> ptrLeft, out);
    s += writingComplete(root -> ptrRight, out);
    return s;
}

/*
    FUNCAO PARA ESCREVER ARQUIVO (PRECISA DO NOME E DO FORMATO PARA ESCREVER, ALEM DA RAIZ)
*/
int writeFile(Node *root, const char *sFileName, int iFormat2Write){
    FILE *out = fopen(sFileName, "w");
    if(!out){
        cout << "Error: não foi possível abrir o arquivo: [" << sFileName << "] para escrever tree.\n";
        return -1; 
    }

    if(iFormat2Write == 0) {

    }
    else{
        return writingComplete(root, out);
    }
    return -2;
}

bool isPerfect(Node *root) {
    return true;
}

bool isComplete(Node *root) {
    if(!root) return true;
    if((!(root -> ptrLeft) && (root -> ptrRight)) || (root -> ptrLeft) && !(root -> ptrRight)) return false;
    if(!isComplete(root -> ptrLeft) || !isComplete(root -> ptrRight)) return false;
    return true;
}

/*
    FUNCAO AUXILIAR PARA LER ARQUIVO
*/
Node *readingComplete(Node *root, FILE *inp) {
    int iNumberAtual;
    if(fscanf(inp, "%i ", &iNumberAtual) < 1 || iNumberAtual == NULLVAL) return nullptr;
    root = createNode(iNumberAtual);
    root -> ptrLeft = readingComplete(root -> ptrLeft, inp);
    root -> ptrRight = readingComplete(root -> ptrLeft, inp);
    return root;
}

/*
    FUNCAO PARA LER ARQUIVO E DEVOLVER ARVORE
*/
Node *openFile(const char *sFileName, int iFormat2Read) {
    FILE *inp = fopen(sFileName, "r");
    if(!inp){
        cout << "Error: não foi possível abrir o arquivo: [" << sFileName << "] para ler tree.\n";
        return nullptr;
    }
    Node *root = nullptr;
    int iNumberAtual;

    switch(iFormat2Read) {
        case 0:
            while(fscanf(inp, "%i ", &iNumberAtual) > 0) {
                if(iNumberAtual == NULLVAL) continue;
                insertNode(&root, iNumberAtual);
            }
            break;
        case 1:
            root = readingComplete(root, inp);
            break;
        default:
            break;
    }
    cout << "\nArvore carregada, raiz em :" << root << endl << endl;
    printTree(root, 0, ' ');
    return root;
}
