#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <chrono>
#include <vector>
#include "animation.hpp"

#define NULLVAL -666

using namespace std;

typedef struct Node {
    int iData;
    Node *ptrLeft, *ptrRight;
} Node;

Node **ptrAllTree;
int iTreeCount = 0;

Node **ptrAllLinkedList;
int iListCount = 0;

void getTimeLapse(auto start) {
    auto end = chrono::steady_clock::now();

    auto diff = end - start;
    cout << "\n\e[1;42mTempo de execucao:  "<<  chrono::duration <double, milli> (diff).count() << " ms\e[0m" << endl;
}

void printLinkedList(Node *ptrHead) {
    if(!ptrHead) {
        cout << "end" <<  endl;
        return ;
    }
    cout << ptrHead -> iData << " -> ";
    printLinkedList(ptrHead -> ptrRight);
}

/**
 * Cria um novo noh
 * 
 * @param iValue valor inteiro que será o número do novo noh
 * @return O endereço do novo noh que foi criado
 */
Node *createNode(int iValue) {
    Node *ptrNewNode = (Node *) malloc(sizeof(Node));
    ptrNewNode -> ptrLeft = nullptr;
    ptrNewNode -> ptrRight = nullptr;
    ptrNewNode -> iData = iValue;
    return ptrNewNode;
}

/**
 * Deleta determinada arvore
 * 
 * @param ptrNoh endereco da raiz da arvore
 * @return quantidade de nohs deletados
 */
int deleteTree(Node *ptrNoh) {
    if(!ptrNoh) return  0;
    int iQtdNoh = 0;
    iQtdNoh += deleteTree(ptrNoh -> ptrLeft);
    iQtdNoh += deleteTree(ptrNoh -> ptrRight);
    free(ptrNoh);
    return iQtdNoh + 1;
}

/**
 * Dado um endereço que guarda a raiz da arvore, insere um elemento
 * 
 * @param ptrRoot endereço que guarda a variável de endereço da raiz
 * @param iValue valor para ser inserido na arvore
 * @note caso ptrRoot não tenha sido inicializado como null, haverá erro de segmentation fault
 */
void insertNode(Node **ptrRoot, int iValue) {
    if(!(*ptrRoot)){
        *ptrRoot = createNode(iValue);
        return;
    }
    if(iValue < (*ptrRoot) -> iData){
        insertNode(&((*ptrRoot) -> ptrLeft), iValue);
        return;
    } 
    else insertNode(&((*ptrRoot) -> ptrRight), iValue);
}

/**
 * Dado um endereço, acha a altura da arvore
 * 
 * @param ptrRoot endereço de um noh que guarda a raiz
 * @return inteiro que representa a atlura da arvore
 */
int getHeight(Node *ptrRoot) {
    if(!ptrRoot) return 0;
    int iHeightLft = getHeight(ptrRoot -> ptrLeft), iHeightRgt = getHeight(ptrRoot -> ptrRight);
    
    return (iHeightLft > iHeightRgt) ? iHeightLft + 1 : iHeightRgt + 1;
}

/**
 * Função auxiliar para pegar input com cin.
 * 
 * @return numero inteiro digitado pelo usuario.
 */
int get_int(){
    int iGetInput;
    cin >> iGetInput;
    while (cin.fail())
    {
        cout << "Error: numero invalido. -> DIGITE:  ";
        cin.clear(); 
        cin.ignore(1000, '\n');
        cin >> iGetInput;
        system("cls || clear");
    }

    return iGetInput;
}


/**
 * Função auxiliar para verificar extensao do arquivo passado.
 * 
 * @param cFileName vetor de caracteres que indica qual o nome do arquivo passado.
 * @return booleano que indca se e .txt ou nao
 */
bool verifyExtensao(const char *cFileName) {
    int i = 0;
    while(cFileName[i] != '\0'){
        i++;
    } 

    return (cFileName[i - 1] != 't' || cFileName[i - 1] != 't' || cFileName[i - 1] != 't') ? false : true;
}

/**
 * Função auxiliar para printar arvore, vai cuidar da tabulação para facilitar visualização
 * 
 * @param iTotalTabs inteiro que diz a quantidade de espaços necessários para printar
 */
static void printGalho(int iTotalTabs) {
    if(iTotalTabs == 0) return;
    for(int i = iTotalTabs - 1; i > 0; i--)
        cout << "\t";
    cout << "+" << "---  ";
}


int tamanho(Node *ptrInicio){
    int iCont = 0;
    while(ptrInicio != nullptr){
        ptrInicio = ptrInicio->ptrRight;
        iCont ++;
    }
    return iCont;
};

int *convertArray(Node *ptrHead){
    int itamanho = tamanho(ptrHead);
    int *iLista = (int *) malloc(sizeof(int) * itamanho);
    int i = 0;
    while(i < itamanho){
        iLista[i] = ptrHead->iData;
        ptrHead = ptrHead->ptrRight;
    }

    return iLista;
}

/**
 * Dado um endereço printa a arvore que parte dele
 * 
 * @param ptrRoot endereço que guarda a raiz
 * @param iTabulation inteiro que diz a quantidade de espaços necessários entre a base e o elemento
 */
void printTreeHorizontal(Node *ptrRoot, int iTabulation, bool bollOrderControle) {
    if(!ptrRoot){
        printGalho(iTabulation);
        cout << "\b\b|" << endl;
        return;  
    }
    if(bollOrderControle){
        printTreeHorizontal(ptrRoot -> ptrLeft, iTabulation + 1, bollOrderControle);
        printGalho(iTabulation);
        cout << ptrRoot -> iData << endl;
        printTreeHorizontal(ptrRoot -> ptrRight, iTabulation + 1, bollOrderControle);
    }
    else{
        printGalho(iTabulation);
        cout << ptrRoot -> iData << endl;
        printTreeHorizontal(ptrRoot -> ptrLeft, iTabulation + 1, bollOrderControle);
        printTreeHorizontal(ptrRoot -> ptrRight, iTabulation + 1, bollOrderControle);
    }
}

/**
 * Dado um endereço, acha a quantidade de nohs que tem nessa arvore
 * 
 * @param ptrRoot endereço que guarda a raiz
 * @return inteiro que representa a quantidade de nohs que tem a arovre
 */
int getSize(Node *ptrRoot) {
    if(!ptrRoot) return 0;
    return getSize(ptrRoot -> ptrLeft) + getSize(ptrRoot -> ptrRight) + 1;
}

/**
 * Dado o endereço da raiz e o valor desejado, retorna o endereço do valor procurado ou null
 * caso ele não seja encontrado
 * 
 * @param ptrRoot endereço que guarda a raiz
 * @param iValue inteiro procurado
 * @return endereço de onde esta o valor procurado ou null
 */
Node *searchValue(Node *ptrRoot, int iValue) {
    if(!ptrRoot) return nullptr;
    if(ptrRoot -> iData == iValue) return ptrRoot;
    if(ptrRoot -> iData > iValue) return searchValue(ptrRoot -> ptrLeft, iValue);
    return searchValue(ptrRoot -> ptrRight, iValue);
}

/**
 * Dado o endereço da raiz, diz se a arvore é completa
 * 
 * @param ptrRoot endereço que guarda a raiz
 * @return booleano que indica se é ou nao completa
 */
bool isComplete(Node *ptrRoot) {
    if(!ptrRoot) return true;
    if((!(ptrRoot -> ptrLeft) && (ptrRoot -> ptrRight)) || (ptrRoot -> ptrLeft) && !(ptrRoot -> ptrRight)) return false;
    if(!isComplete(ptrRoot -> ptrLeft) || !isComplete(ptrRoot -> ptrRight)) return false;
    return true;
}

/**
 * Dado o endereço da raiz, diz se a arvore é perfeita
 * 
 * @param ptrRoot endereço que guarda a raiz
 * @return booleano que indica se é ou nao perfeita
 */
bool isPerfect(Node *ptrRoot){
    if(!ptrRoot) return 0;
    int iHeightLft = getHeight(ptrRoot -> ptrLeft), iHeightRgt = getHeight(ptrRoot -> ptrRight);
    bool bTestComplete = isComplete(ptrRoot);
    return (iHeightLft == iHeightRgt && bTestComplete) ? true : false;
}

/**
 * Dado o endereço da raiz, escreve os valores da arvore em um arquivo
 * 
 * @param ptrRoot endereço que guarda a raiz
 * @param ptrOutFile ponteiro para o arquivo
 * @return inteiro que indica a quantidade de elementos escritos
 */
int writingComplete(Node *ptrRoot, FILE *ptrOutFile) {
    int iCountNohs = 0;
    if(!ptrRoot){
        fprintf(ptrOutFile, "%i ", NULLVAL);
        return iCountNohs;
    }

    fprintf(ptrOutFile, "%i ", ptrRoot -> iData);
    iCountNohs += writingComplete(ptrRoot -> ptrLeft, ptrOutFile);
    iCountNohs += writingComplete(ptrRoot -> ptrRight, ptrOutFile);
    return iCountNohs;
}

/**
 * Dado o endereço da raiz, escreve os valores da arvore em um arquivo in order
 * 
 * @param ptrRoot endereço que guarda a raiz
 * @param ptrOutFile ponteiro para o arquivo
 * @return inteiro que indica a quantidade de elementos escritos
 */
static int writeAuxiliar(Node *ptrRoot, FILE *ptrOutFile) {
    if(!ptrOutFile || !ptrRoot) return 0;
    fprintf(ptrOutFile, "%i ", ptrRoot -> iData);
    return 1 + writeAuxiliar(ptrRoot -> ptrLeft, ptrOutFile) + writeAuxiliar(ptrRoot -> ptrRight, ptrOutFile);
}

/**
 * Dado o endereço da raiz, escreve os valores da arvore em um arquivo in order
 * 
 * @param ptrRoot endereço que guarda a raiz
 * @param sFileName nome do arquivo para ser aberto
 * @param iFormat2Write inteiro que indica o formato de escrita, sendo 0(in order) ou 1(complete)
 * @return inteiro que indica a quantidade de elementos escritos
 */
int writeFile(Node *ptrRoot, const char *sFileName, int iFormat2Write){
    FILE *ptrOutFile = fopen(sFileName, "w");
    if(!ptrOutFile){
        cout << "\e[1;41mError: nao foi possivel abrir o arquivo: [" << sFileName << "] para escrever tree.\e[0m\n";
        return -1; 
    }
    int iQtdWrited = -2;
    if(iFormat2Write == 0) 
        iQtdWrited = writeAuxiliar(ptrRoot, ptrOutFile);
    else
        iQtdWrited = writingComplete(ptrRoot, ptrOutFile);

    fclose(ptrOutFile);
    return iQtdWrited;
}

/**
 * Lê arquivo no modo completo
 * 
 * @param ptrRoot endereço que guarda determinado noh de uma arvore
 * @param ptrInpFile ponteiro para o arquivo sendo lido
 * @return noh gerado da arvore
 */
Node *readingComplete(Node *ptrRoot, FILE *ptrInpFile) {
    int iNumberAtual;
    if(fscanf(ptrInpFile, "%i ", &iNumberAtual) < 1 || iNumberAtual == NULLVAL) return nullptr;
    ptrRoot = createNode(iNumberAtual);
    ptrRoot -> ptrLeft = readingComplete(ptrRoot -> ptrLeft, ptrInpFile);
    ptrRoot -> ptrRight = readingComplete(ptrRoot -> ptrLeft, ptrInpFile);
    return ptrRoot;
}

/**
 * Lê arquivo e retornar uma arvore
 * 
 * @param sFileName nome do arquivo a ser lido
 * @param iFormat2Read forma de ler o arquivo, 0(in order) ou 1(complete)
 * @return root de uma nova arvore
 */
Node *openFile(const char *sFileName, int iFormat2Read) {
    FILE *ptrInpFile = fopen(sFileName, "r");
    if(!ptrInpFile){
        cout << "\e[1;41mError: nao foi possivel abrir o arquivo: [" << sFileName << "] para ler tree.\e[0m\n\n";
        return nullptr;
    }
    Node *ptrNewRoot = nullptr;
    int iNumberAtual;

    switch(iFormat2Read) {
        case 0:
            while(fscanf(ptrInpFile, "%i ", &iNumberAtual) > 0) {
                if(iNumberAtual == NULLVAL) continue;
                insertNode(&ptrNewRoot, iNumberAtual);
            }
            break;
        case 1:
            ptrNewRoot = readingComplete(ptrNewRoot, ptrInpFile);
            break;
        default:
            break;
    }
    cout << "\n\e[1;42mArvore carregada, raiz em :" << ptrNewRoot;
    fclose(ptrInpFile);
    return ptrNewRoot;
}

// Função que converte uma árvore para lista duplamente encadeada
void convertToLL(Node* ptrRoot, Node** ptrHead, Node** ptrTail) {
    if (ptrRoot == nullptr) {
        return;
    }

    // Converter a subárvore esquerda em uma lista duplamente encadeada
    convertToLL(ptrRoot->ptrLeft, ptrHead, ptrTail);

    // Conectar a raiz à lista duplamente encadeada
    if (*ptrHead == nullptr) {
        *ptrHead = ptrRoot;
    } else {
        (*ptrTail)->ptrRight = ptrRoot;
        ptrRoot->ptrLeft = *ptrTail;
    }

    *ptrTail = ptrRoot;

    // Converter a subárvore direita em uma lista duplamente encadeada
    convertToLL(ptrRoot->ptrRight, ptrHead, ptrTail);
}
// A função convertToLL é usada para realizar a conversão da árvore para a lista duplamente encadeada
// A função recebe três argumentos: o ponteiro para a raiz da árvore (root), o ponteiro para o 
// ponteiro para a cabeça da lista (head), e o ponteiro para o ponteiro para o final da lista (tail).

//FUNÇÃO PARA TROCAR ELEMENTOS
Node *troca(Node *ptrInicio, Node *ptrItem1, Node *ptrItem2){
    Node *ptrAux;
    // ptrInicio = ptrItem2;
    if(ptrItem1->ptrLeft == nullptr) ptrInicio = ptrItem2;
    if(ptrItem2->ptrLeft == nullptr) ptrInicio = ptrItem1;
    if(ptrItem2->ptrLeft == ptrItem1){
        if(ptrItem1->ptrLeft != nullptr) ptrItem1->ptrLeft->ptrRight = ptrItem2;
        if(ptrItem2->ptrRight != nullptr) ptrItem2->ptrRight->ptrLeft = ptrItem1;
        ptrItem1->ptrRight = ptrItem2->ptrRight;
        ptrItem2->ptrLeft = ptrItem1->ptrLeft;
        ptrItem2->ptrRight = ptrItem1;
        ptrItem1->ptrLeft = ptrItem2;
    }

    else if(ptrItem1->ptrLeft == ptrItem2){
        if(ptrItem1->ptrRight != nullptr) ptrItem1->ptrRight->ptrLeft = ptrItem2;
        if(ptrItem2->ptrLeft != nullptr) ptrItem2->ptrLeft->ptrRight = ptrItem1;
        ptrItem2->ptrRight = ptrItem1->ptrRight;
        ptrItem1->ptrLeft = ptrItem2->ptrLeft;
        ptrItem1->ptrRight = ptrItem2;
        ptrItem2->ptrLeft = ptrItem1;
    }
    else{
        if(ptrItem1->ptrLeft != nullptr) ptrItem1->ptrLeft->ptrRight = ptrItem2;
        if(ptrItem2->ptrRight != nullptr) ptrItem2->ptrRight->ptrLeft = ptrItem1;
        if(ptrItem1->ptrRight != nullptr) ptrItem1->ptrRight->ptrLeft = ptrItem2;
        if(ptrItem2->ptrLeft != nullptr) ptrItem2->ptrLeft->ptrRight = ptrItem1;
        ptrAux = ptrItem1->ptrLeft;
        ptrItem1->ptrLeft = ptrItem2->ptrLeft;
        ptrItem2->ptrLeft = ptrAux;
        ptrAux = ptrItem1->ptrRight;
        ptrItem1->ptrRight = ptrItem2->ptrRight;
        ptrItem2->ptrRight = ptrAux;
    }
    
    return ptrInicio;
};

Node* b_sort(Node **ptrItem1){
    bool bTeste = true;
    Node* ptrItem2 = (*ptrItem1)->ptrRight;
    Node* ptrInicio = *ptrItem1;

    while(bTeste == true){
        bTeste = false;

        while((*ptrItem1)->ptrRight != nullptr){
            ptrItem2 = (*ptrItem1)->ptrRight;

            if(ptrItem2->iData < (*ptrItem1)->iData){
                ptrInicio = troca(ptrInicio, *ptrItem1, ptrItem2);
                bTeste = true;

            }
            else{
                *ptrItem1 = (*ptrItem1)->ptrRight;
            }
        }
        *ptrItem1 = ptrInicio;
    }
    return ptrInicio;
};

Node* bb_sort(Node *ptrRoot){
    Node *ptrHead = nullptr;
    Node *ptrTail = nullptr;
    convertToLL(ptrRoot, &ptrHead, &ptrTail);
    b_sort(&ptrHead);
    return ptrHead;
}

//FUNÇÃO PARA POSICIONAR ELEMENTO DE ACORDO COM IDATA
void posiciona(Node **ptrInicio, Node *ptrItem){
    Node *ptrAux = ptrItem;
    int dat = ptrItem->iData;
    
    if(ptrItem->ptrLeft == nullptr) return;

    while(ptrItem->ptrLeft != nullptr && ptrItem->ptrLeft->iData > dat){
        ptrItem = ptrItem->ptrLeft;
    }

    if(ptrItem->iData <= dat) return;

    if(ptrItem->ptrRight != ptrAux){
        if(ptrItem->ptrLeft != nullptr) ptrItem->ptrLeft->ptrRight = ptrAux;
        else{
            *ptrInicio = ptrAux;
        }
        if(ptrAux->ptrRight != nullptr) ptrAux->ptrRight->ptrLeft = ptrAux->ptrLeft;
        if(ptrAux->ptrLeft != nullptr) ptrAux->ptrLeft->ptrRight = ptrAux->ptrRight;
        ptrAux->ptrRight = ptrItem;
        ptrAux->ptrLeft = ptrItem->ptrLeft;
        ptrItem->ptrLeft = ptrAux;
    }

    else if(ptrItem->ptrRight == ptrAux){
        *ptrInicio = troca(*ptrInicio, ptrItem, ptrAux); 
    }
    
};

void i_sort(Node **ptrInicio){
    Node *ptrAux = *ptrInicio, *ptrAux2;
    
    while(ptrAux != nullptr){
        ptrAux2 = ptrAux->ptrRight;
        posiciona(ptrInicio, ptrAux);
        ptrAux = ptrAux2;
    }
};

Node* ii_sort(Node *ptrRoot){
    Node *ptrHead = nullptr;
    Node *ptrTail = nullptr;
    convertToLL(ptrRoot, &ptrHead, &ptrTail);
    i_sort(&ptrHead);
    return ptrHead;
}

void shell_sort(Node **ptrInicio){
    Node *ptrAux = *ptrInicio, *ptrDivide_lista;
    int itamanho = tamanho(ptrAux), i = 0;
    
    while(i < itamanho/2){
        ptrAux = ptrAux->ptrRight;
        i++;
    }
    if(itamanho % 2 == 0) ptrDivide_lista = ptrAux;
    else ptrDivide_lista = ptrAux->ptrRight;
    ptrAux = *ptrInicio;

    Node *ptrTmp, *ptrTmp2, *ptrAux2;
    
    if(ptrAux->iData > ptrDivide_lista->iData){
        *ptrInicio = troca(*ptrInicio, ptrAux, ptrDivide_lista);
        ptrDivide_lista = ptrAux;
    } 

    while(ptrDivide_lista != nullptr){
        ptrTmp = ptrDivide_lista->ptrRight;
        ptrTmp2 = ptrAux->ptrRight;
        if(ptrDivide_lista->iData < ptrAux->iData){
            *ptrInicio = troca(*ptrInicio, ptrAux, ptrDivide_lista);
        }

        ptrDivide_lista = ptrTmp;
        ptrAux = ptrTmp2;
    }
    if(itamanho <= 3) return i_sort(ptrInicio);
    i = 0;
    ptrAux = *ptrInicio;

    while(i < (itamanho/2) - 1){
        ptrAux = ptrAux->ptrRight;
        i++;
    }

    ptrDivide_lista = ptrAux;
    ptrAux = ptrDivide_lista->ptrLeft->ptrLeft;

    while(ptrDivide_lista != nullptr){
        ptrTmp = ptrDivide_lista->ptrRight;
        ptrTmp2 = ptrDivide_lista->ptrLeft;
        
        while(ptrAux != nullptr){

            if(ptrDivide_lista->iData < ptrAux->iData){
                *ptrInicio = troca(*ptrInicio, ptrAux, ptrDivide_lista);
                if(ptrDivide_lista->ptrLeft != nullptr) ptrAux = (ptrDivide_lista->ptrLeft)->ptrLeft;
                else ptrAux = nullptr;
            }
            else ptrAux = nullptr;

        }
        ptrDivide_lista = ptrTmp;
        ptrAux = ptrTmp2;
    }

    i_sort(ptrInicio);

};
Node* sshell_sort(Node *ptrRoot){
    Node *ptrHead = nullptr;
    Node *ptrTail = nullptr;
    convertToLL(ptrRoot, &ptrHead, &ptrTail);
    shell_sort(&ptrHead);
    return ptrHead;
};


void s_sort_ptrAux(Node **ptrInicio){
    Node *ptrAux = *ptrInicio, *ptrMenor = *ptrInicio;

    while(ptrAux->ptrRight != nullptr){
        if((ptrAux->ptrRight)->iData <= ptrMenor->iData){
            ptrMenor = ptrAux->ptrRight;
        }
        ptrAux = ptrAux->ptrRight;
    }

    *ptrInicio = troca(*ptrInicio, *ptrInicio, ptrMenor);
};

void s_sort(Node **ptrInicio){
    s_sort_ptrAux(ptrInicio);
    Node *ptrAux = (*ptrInicio)->ptrRight, *ptrAux2;
    while(ptrAux->ptrRight != nullptr){
        ptrAux2 = ptrAux->ptrRight;
        s_sort_ptrAux(&ptrAux);
        ptrAux = ptrAux2;
    }
};
Node* ss_sort(Node *ptrRoot){
    Node *ptrHead = nullptr;
    Node *ptrTail = nullptr;
    convertToLL(ptrRoot, &ptrHead, &ptrTail);
    s_sort(&ptrHead);
    return ptrHead;
};

//FUNÇÕES PARA PRINTAR LINKED LIST
void printList(Node *ptrHead) {
    Node *ptrCurrent = ptrHead;
    while (ptrCurrent != nullptr) {
        std::cout << ptrCurrent->iData << " "  ;
        ptrCurrent = ptrCurrent->ptrRight;
    }
    std::cout << std::endl;
};

Node *ultimo(Node *ptrInicio){
    Node *ptrAux = ptrInicio;
    while(ptrAux->ptrRight != nullptr){
        ptrAux = ptrAux->ptrRight;
    }
    return ptrAux;
}

void printReverso(Node *ptrInicio){
    while(ptrInicio != nullptr){
        cout << ptrInicio->iData << " ";
        ptrInicio = ptrInicio->ptrRight;
    }
};


// Sorts extras 

// Merge 

// Função para dividir a lista ligada em duas partes iguais
Node* split(Node* head) {
    Node *fast = head, *slow = head;
    // Usamos o método do coelho e da tartaruga para encontrar o meio da lista
    while (fast->ptrRight && fast->ptrRight->ptrRight) {
        fast = fast->ptrRight->ptrRight;
        slow = slow->ptrRight;
    }
    // Dividindo a lista em duas partes
    Node* temp = slow->ptrRight;
    slow->ptrRight = nullptr;
    return temp;
}

// Função para mesclar duas listas ligadas
Node* merge(Node* first, Node* second) {
    // Se a primeira lista estiver vazia, retornamos a segunda lista
    if (!first)
        return second;

    // Se a segunda lista estiver vazia, retornamos a primeira lista
    if (!second)
        return first;

    // Comparamos os primeiros elementos de ambas as listas e colocamos o menor deles na lista resultante
    if (first->iData < second->iData) {
        first->ptrRight = merge(first->ptrRight, second);
        first->ptrRight->ptrLeft = first;
        first->ptrLeft = nullptr;
        return first;
    } else {
        second->ptrRight = merge(first, second->ptrRight);
        second->ptrRight->ptrLeft = second;
        second->ptrLeft = nullptr;
        return second;
    }
}

// Função para classificar a lista ligada usando Merge Sort
Node* mergeSort(Node* node) {
    // Se a lista estiver vazia ou houver apenas um elemento, não há necessidade de classificar
    if (!node || !node->ptrRight)
        return node;

    // Dividimos a lista em duas partes
    Node* second = split(node);

    // Classificamos as duas listas divididas
    node = mergeSort(node);
    second = mergeSort(second);

    // Mesclamos as duas listas classificadas
    return merge(node, second);
}


// Quicksort 

// Função para trocar dois elementos
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Função para obter o último nó da lista
Node *lastNode(Node *root) {
    // Percorre a lista até o fim
    while (root && root->ptrRight)
        root = root->ptrRight;
    return root;
}

// Função para encontrar a posição do pivô
Node* partition(Node *l, Node *h) {
    // Define o valor do pivô
    int x  = h->iData;

    // Inicializa as posições
    Node *i = l->ptrLeft;

    // Percorre cada nó
    for (Node *j = l; j != h; j = j->ptrRight) {
        // Se o valor do nó atual for menor ou igual ao pivô, troca as posições
        if (j->iData <= x) {
            i = (i == nullptr)? l : i->ptrRight;
            swap(&(i->iData), &(j->iData));
        }
    }
    // Troca a posição do pivô
    i = (i == nullptr)? l : i->ptrRight;
    swap(&(i->iData), &(h->iData));

    // Retorna a posição do pivô
    return i;
}

// Função auxiliar para aplicar a ordenação rápida
void _quickSort(Node* l, Node *h) {
    // Se o intervalo é válido
    if (h != nullptr && l != h && l != h->ptrRight) {
        // Particiona a listaa
        Node *p = partition(l, h);
        
        // Ordena as duas metades
        _quickSort(l, p->ptrLeft);
        _quickSort(p->ptrRight, h);
    }
}

// Função principal para aplicar a ordenação rápida na lista ligada
void quickSort(Node *head) {
    // Encontra o último nó
    Node *h = lastNode(head);
    
    // Chama a função auxiliar para ordenar a lista
    _quickSort(head, h);
}

/*
// Radixsort 

// Função de contagem utilizada no Radix Sort
void countSort(vector<int>& arr, int exp) {
    int n = arr.size();
    
    // Cria vetores de saída e contagem
    vector<int> output(n);  
    vector<int> count(10, 0);  // Temos 10 dígitos, de 0 a 9
    
    // Conta o número de ocorrências de cada dígito na posição indicada por exp
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    
    // Acumula as contagens para que count[i] indique a posição do dígito i no vetor de saída
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    
    // Constrói o vetor de saída
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    
    // Copia o vetor de saída para o vetor original, de modo que os números originais estejam agora ordenados de acordo com o dígito atual
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// Função principal para realizar o Radix Sort
void radixSort(vector<int>& arr) {
    // Encontra o número máximo para saber o número de dígitos que ele possui
    int max = *max_element(arr.begin(), arr.end());
    
    // Realiza o Count Sort para cada dígito. Note que, em vez de passar o número de dígitos, exp é passado. exp é 10^i, onde i é o dígito atual
    for (int exp = 1; max / exp > 0; exp *= 10)
        countSort(arr, exp);
}


// Heapsort 

// Função para ajustar um heap
void heapify(vector<int>& arr, int n, int i) {
    // Assume-se inicialmente que o maior elemento é a raiz (i)
    int largest = i; 
    
    // Calcula os índices dos filhos esquerdo e direito
    int left = 2 * i + 1; 
    int right = 2 * i + 2;
  
    // Verifica se o filho esquerdo existe e é maior que a raiz
    if (left < n && arr[left] > arr[largest])
        largest = left;
  
    // Verifica se o filho direito existe e é maior que a maior elemento encontrado até agora
    if (right < n && arr[right] > arr[largest])
        largest = right;
  
    // Se o maior elemento não é mais a raiz
    if (largest != i) {
        // Troca a raiz com o maior elemento
        swap(arr[i], arr[largest]);
        
        // Chama recursivamente heapify para o novo sub-heap
        heapify(arr, n, largest);
    }
}

// Função para realizar um heap sort em um vetor
void heapSort(vector<int>& arr) {
    // Obtem o tamanho do vetor
    int n = arr.size();
  
    // Constrói um heap máximo a partir do vetor
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
  
    // Um por um extrai o elemento do heap
    for (int i = n - 1; i > 0; i--) {
        // Move o elemento raiz atual para o final
        swap(arr[0], arr[i]);
        
        // Chama heapify na nova raiz do heap reduzido
        heapify(arr, i, 0);
    }
}

// Coutingsort 

// Função para ordenar um vetor utilizando o algoritmo de ordenação Count Sort
void countSort(vector<int>& arr) {
    
    // Encontra o valor máximo e mínimo no vetor original
    int max = *max_element(arr.begin(), arr.end());
    int min = *min_element(arr.begin(), arr.end());

    // Calcula o intervalo dos valores (max - min + 1)
    int range = max - min + 1;
  
    // Cria um vetor "count" para contar a ocorrência dos elementos e um vetor "output" para o vetor ordenado
    vector<int> count(range), output(arr.size());

    // Conta a ocorrência de cada elemento no vetor original
    for(int i = 0; i < arr.size(); i++)
        count[arr[i]-min]++;
    
    // Altera o vetor "count" para que cada elemento em uma posição i seja a soma de todos os elementos em posições menores ou iguais a i
    for(int i = 1; i < count.size(); i++)
        count[i] += count[i-1];
    
    // Constrói o vetor "output" com os elementos ordenados
    for(int i = arr.size()-1; i >= 0; i--) {
        output[count[arr[i]-min]-1] = arr[i]; // O "-1" é necessário porque os índices de array começam em 0
        count[arr[i]-min]--;
    }
    
    // Copia o vetor "output" ordenado de volta para o vetor original
    for(int i = 0; i < arr.size(); i++)
        arr[i] = output[i];
}


// BucketSort

// Função para ordenar um vetor utilizando o algoritmo de ordenação bucket sort
void bucketSort(vector<float>& arr) {
    
    // Obtem o tamanho do vetor
    int n = arr.size();

    // Cria um vetor de listas para armazenar os buckets
    vector<list<float>> buckets(n);

    // Distribui os elementos do vetor original pelos buckets
    for (int i = 0; i < n; i++) {
        // O índice do bucket é calculado como n vezes o valor do elemento. 
        // Isso é válido porque estamos assumindo que os elementos estão uniformemente distribuídos no intervalo [0, 1)
        int bucketIndex = n * arr[i];

        // Adiciona o elemento atual ao seu respectivo bucket
        buckets[bucketIndex].push_back(arr[i]);
    }

    // Ordena individualmente cada bucket
    for (int i = 0; i < n; i++) 
        buckets[i].sort();
    
    // Índice para iterar sobre o vetor original
    int index = 0;
    
    // Concatena os buckets no vetor original, efetivamente o ordenando
    for (int i = 0; i < n; i++) {
        // Remove os elementos do bucket e coloca-os de volta no vetor original
        while (!buckets[i].empty()) {
            // Coloca o primeiro elemento do bucket no vetor
            arr[index++] = *(buckets[i].begin());
            
            // Remove o primeiro elemento do bucket
            buckets[i].erase(buckets[i].begin());
        }
    }
}

// Função para converter um vetor em uma lista duplamente ligada
Node* arrayToList(vector<int>& arr) {
    
    // Inicializa um ponteiro de nó como nullptr
    Node* node = nullptr;
    
    // Ponteiro para ponteiro para o começo da lista ligada
    Node** head_ref = &node;
    
    // Loop sobre o vetor
    for (int i : arr) {
        
        // Cria um novo nó e atribui o valor do elemento atual do vetor
        Node* new_node = new Node;
        new_node->iData = i;
        
        // Configura o ponteiro 'ptrRight' do novo nó para apontar para o nó atual no início da lista
        new_node->ptrRight = (*head_ref);
        
        // Como este é um novo nó, seu 'ptrLeft' apontará para nullptr
        new_node->ptrLeft = nullptr;

        // Se a lista não estiver vazia, então faz o 'ptrLeft' do antigo primeiro nó apontar para o novo nó
        if ((*head_ref) != nullptr) 
            (*head_ref)->ptrLeft = new_node ;

        // Faz o novo nó ser o novo primeiro nó da lista
        (*head_ref) = new_node;
    }
    
    // Retorna o ponteiro para o início da lista ligada
    return node;
}
// Por isso na main tem q estar 'vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};' ( um exemplo ) 
// Mas apenas na Radix, Heap. Couting, Bucket 
*/
// FUNÇÕES PARA REMOVER NO DE ACORDO COM O VALOR INTEIRO SOLICITADO
Node* remove(Node *ptrAtual){
    Node *ptrNo1, *ptrNo2;
    if(ptrAtual->ptrLeft == NULL){
        ptrNo2 = ptrAtual->ptrRight;
        free(ptrAtual);
        return ptrNo2;
    }
    ptrNo1 = ptrAtual;
    ptrNo2 = ptrAtual->ptrLeft;
    while(ptrNo2->ptrRight != NULL){
        ptrNo1 = ptrNo2;
        ptrNo2 = ptrNo2->ptrRight;
    }

    if(ptrNo1 != ptrAtual){
        ptrNo1->ptrRight = ptrNo2->ptrLeft;
        ptrNo2->ptrLeft = ptrAtual->ptrLeft;
    }

    ptrNo2->ptrRight = ptrAtual->ptrRight;
    free(ptrAtual);
    return ptrNo2;
};

int remove_final(Node **ptrRoot, int iValor){
    if(ptrRoot == NULL) return 0;
    Node *ptrAnt = NULL;
    Node *ptrAtual = *ptrRoot;
    while(ptrAtual != NULL){
        if(iValor == ptrAtual->iData){
            if(ptrAtual == *ptrRoot) *ptrRoot = remove(ptrAtual);
            else{
                if(ptrAnt->ptrRight == ptrAtual) ptrAnt->ptrRight = remove(ptrAtual);
                else ptrAnt->ptrLeft = remove(ptrAtual);
            }
            return 1;
        }
        ptrAnt = ptrAtual;
        if(iValor > ptrAtual->iData) ptrAtual = ptrAtual->ptrRight;
        else ptrAtual = ptrAtual->ptrLeft;
    }
}

/**
 * Desenha o menu principal
 * 
 */
void drawMenu() {
    cout << "\t\t \e[1;45m-MENU-\e[0m \n" << endl;
    cout << "- Criar nova arvore: \t\t\t DIGITE 2" << endl;
    cout << "- Obter dados de uma arvore: \t\t DIGITE 3 " << endl;
    cout << "- Alterar uma arvore: \t\t\t DIGITE 4" << endl;
    cout << "- Visualizar uma arvore: \t\t DIGITE 5" << endl;
    cout << "- Converter em lista e ordenar: \t DIGITE 6" << endl;
    cout << "- Para sair: \t\t\t\t DIGITE 0\n" << endl;
    cout << "DIGITE UM NUMERO: ";
}

/**
 * Desenha o menu para insercao de arvores na memoria
 * 
 * @return inteiro usado para dizer se voltar para o menu principal ou sai do programa
 */
int drawMenuInsert() {
    while(1){
        int controle;   
        cout << "\t\t \e[1;45m-MENU-\e[0m \n" << endl;
        cout << "- Inserir via arquivo: \t\tDIGITE 1" << endl;
        cout << "- Inserir via terminal: \tDIGITE 2" << endl;
        cout << "- Voltar no menu anterior: \tDIGITE 3" << endl;
        cout << "- Para sair do programa: \tDIGITE 0" << endl;
        cout << "\nDIGITE UM NUMERO: ";
        controle = get_int();
        system("cls || clear");
        
        if(controle == 1){
            auto start = chrono::steady_clock::now();
            string sFileName;
            cout << "Digite o nome do arquivo: ";
            cin >> sFileName;
            if(!verifyExtensao(sFileName.c_str())){
                cout << "\e[1;41mError: O arquivo [" << sFileName << "] nao possui a estensao [.txt].\e[0m\n\n";
                continue;
            }
            system("cls || clear");
            int iReadModo = 2;
            while(iReadModo != 1 && iReadModo != 0){
                cout << "Digite o modo de leitura:" << endl;
                cout << "\t - 0 - para ler numero por numero e usar a funcao insert." << endl;
                cout << "\t - 1 - para ler um arquivo in order completo com NULVAL." << endl << "DIGITE:  ";
                iReadModo = get_int(); 
                
                system("cls || clear");
            }
            Node *ptrNewRoot = openFile(sFileName.c_str(), iReadModo);
            if(!ptrNewRoot) continue;
            ptrAllTree =(Node **) realloc(ptrAllTree, ++iTreeCount);
            *(ptrAllTree + iTreeCount - 1) = ptrNewRoot;
            getTimeLapse(start);
        }
        else if(controle == 2) {
            auto start = chrono::steady_clock::now();
            Node *ptrNewRoot = nullptr;
            int iGetInput;
            while(true){
                printTreeHorizontal(ptrNewRoot, 0, 1);
                cout << "\nDigite um numero para inserir na arvore:  ";
                iGetInput = get_int();
                cout << endl;
                insertNode(&ptrNewRoot, iGetInput);
                printTreeHorizontal(ptrNewRoot, 0, 1);
                char controle;
                do{
                    cout << "Deseja inserir outro numero?(Y/N)  ";
                    cin >> controle;
                    system("cls || clear");
                }while(controle != 'N' && controle != 'n' && controle != 'Y' && controle != 'y');

                if(controle == 'N' || controle == 'n') break;
            }

            ptrAllTree = (Node **) realloc(ptrAllTree, ++iTreeCount);
            *(ptrAllTree + iTreeCount - 1) = ptrNewRoot;
            cout << "\n\e[1;42mArvore carregada, raiz em :" << ptrNewRoot;
            getTimeLapse(start);
        }
        if(controle == 3) break;
        if(controle == 0) return 0;
    }
    return 1;
}

/**
 * Descobre qual arvore trabalhar
 * 
 * @return inteiro usado para dizer em qual posição da memória a arvore está
 */
int chooseTree(){
    int iChooseTree;
    do{
        cout << "\nCom qual arvore deseja trabalhar? { ";
        for(int i = 0; i < iTreeCount; i++) cout << i+1 << " ";
        cout << "}\nDIGITE: ";
        iChooseTree = get_int();
        system("cls || clear");
    }while(iChooseTree < 1 || iChooseTree > iTreeCount);

    return iChooseTree;
}

/**
 * Desenha o menu para ver dados de uma arvore
 * 
 * @return inteiro usado para controle entre menu principal e sair do programa
 */
int drawMenuShow() {
    system("cls || clear");
    if(iTreeCount == 0) {
        cout << "\n\e[1;41mTemos atualmente -> " << iTreeCount << " <- arvores carregadas. ";
        cout << "Por favor, volte ao menu anterior e insira alguma arvore.\e[0m\n" << endl;
        return 1;
    }

    system("cls || clear");
    cout << endl << endl;
    for(int i = 0; i < iTreeCount; i++) {
        cout << "\n\t \e[1;43mArvore " << i + 1 << "\e[0m" << endl;
        printTreeHorizontal(ptrAllTree[i], 0, 0);
        cout << endl;
    }

    int iChooseTree = chooseTree();

    while(1){
        int controle;   
        cout << "\t\t \e[1;45m- ARVORE " << iChooseTree << " - \e[0m\n" << endl;
        cout << "- Ver altura da arvore: \t\tDIGITE 1" << endl;
        cout << "- Ver tamanho da arvore: \t\tDIGITE 2" << endl;
        cout << "- Buscar endereco de um elemento: \tDIGITE 3" << endl;
        cout << "- Ver se a arvore e completa: \t\tDIGITE 4" << endl;
        cout << "- Ver se a arvore e perfeita: \t\tDIGITE 5" << endl;
        cout << "- Exibir arvore: \t\t\tDIGITE 6" << endl;
        cout << "- Deseja voltar ao menu anterior: \tDIGITE 7" << endl;
        cout << "- Deseja trocar a arvore: \t\tDIGITE 8" << endl;
        cout << "- Sair do programa: \t\t\tDIGITE 0" << endl;
        cout << "\nDIGITE: ";
        controle = get_int();
        system("cls || clear");
        if(controle > 8 || controle < 0) continue;
        if(controle == 0) return 0;
        if(controle == 7) return 1;

        cout << endl;
        if(controle == 8){
            iChooseTree = chooseTree();
            continue;
        }
        if(controle == 1) {
            auto start = chrono::steady_clock::now();
            cout << "A altura da arvore e: " << getHeight(ptrAllTree[iChooseTree - 1]) << endl;
            getTimeLapse(start);
        }
        else if(controle == 2) {
            auto start = chrono::steady_clock::now();
            cout << "O tamanho da arvore e: " << getSize(ptrAllTree[iChooseTree - 1]) << endl;
            getTimeLapse(start);
        }
        else if(controle == 3) {
            auto start = chrono::steady_clock::now();
            int iValue2Search;
            cout << "Digite um valor para ser procurado:  ";
            iValue2Search = get_int();
            system("cls || clear");
            
            Node *ptrValue = searchValue(ptrAllTree[iChooseTree - 1], iValue2Search);

            if(!ptrValue) 
                cout << "O valor que voce procurava nao foi encontrado." << endl;
            else
                cout << "O valor que voce procurava esta em: " << ptrValue << endl;
            getTimeLapse(start);
        }
        else if(controle == 4) {
            auto start = chrono::steady_clock::now();
            isComplete(ptrAllTree[iChooseTree - 1]) ? cout << "A arvore e completa" << endl : cout << "A arvore e incompleta" << endl;
            getTimeLapse(start);
        }
        else if(controle == 5) {
            auto start = chrono::steady_clock::now();
            isPerfect(ptrAllTree[iChooseTree - 1]) ? cout << "A arvore e perfeita" << endl : cout << "A arvore e imperfeita" << endl;
            getTimeLapse(start);
        }
        else if(controle == 6) {
            cout << "\n\t \e[1;43mArvore " << iChooseTree << "\e[0m" << endl;
            printTreeHorizontal(ptrAllTree[iChooseTree - 1], 0, 1);
        }

        int iContinue;
        do{
            cout << "\n\n- Deseja continuar explorando a arvore: \tDIGITE 1" << endl;
            cout << "- Deseja voltar ao menu inicial: \t\tDIGITE 2" << endl;
            cout << "- Deseja trocar a arvore: \t\t\tDIGITE 3" << endl;
            cout << "- Deseja encerrar o programa: \t\t\tDIGITE 0" << endl;
            cout << "DIGITE:  ";
            iContinue = get_int();
            system("cls || clear");
        }while(iContinue > 3 && iContinue < 0);

        if(iContinue == 0) return 0;
        if(iContinue == 2) return 1;
        if(iContinue == 3) iChooseTree = chooseTree();;
        system("cls || clear");
    }
}

/**
 * Desenha o menu para alterar uma arvore
 * 
 * @return inteiro usado para controle entre menu principal e sair do programa
 */
int drawMenuChange() {
    system("cls || clear");
    
    if(iTreeCount == 0) {
        cout << "\n\e[1;41mTemos atualmente -> " << iTreeCount << " <- arvores carregadas. ";
        cout << "Por favor, volte ao menu anterior e insira alguma arvore.\e[0m\n" << endl;
        return 1;
    }

    system("cls || clear");
    cout << endl << endl;
    for(int i = 0; i < iTreeCount; i++) {
        cout << "\n\t \e[1;43mArvore " << i + 1 << "\e[0m" << endl;
        printTreeHorizontal(ptrAllTree[i], 0, 0);
        cout << endl;
    }

    int iChooseTree = chooseTree();
    while(1){
        int controle;   
        cout << "\t\t \e[1;45m- ARVORE " << iChooseTree << " - \e[0m\n" << endl;
        cout << "- Inserir elemento: \t\t\tDIGITE 1" << endl;
        cout << "- Remover elemento: \t\t\tDIGITE 2" << endl;
        cout << "- Escrever em arquivo: \t\t\tDIGITE 3" << endl;
        cout << "- Deseja voltar ao menu anterior: \tDIGITE 4" << endl;
        cout << "- Deseja trocar a arvore: \t\tDIGITE 5" << endl;
        cout << "- Sair do programa: \t\t\tDIGITE 0" << endl;
        cout << "\nDIGITE: ";
        controle = get_int();
        system("cls || clear");
        if(controle > 4 || controle < 0) continue;
        if(controle == 1) {
            int iGetInput;
            
            auto start = chrono::steady_clock::now();
            while(true){
                printTreeHorizontal(ptrAllTree[iChooseTree - 1], 0, 1);
                cout << "\nDigite um numero para inserir na arvore:  ";
                iGetInput = get_int();
                cout << endl;
                insertNode(&(ptrAllTree[iChooseTree - 1]), iGetInput);
                printTreeHorizontal(ptrAllTree[iChooseTree - 1], 0, 1);
                char controle = 'N';
                do{
                    cout << "Deseja inserir outro numero?(Y/N)  ";
                    cin >> controle;
                    cout << controle;
                    system("cls || clear");
                }while(controle != 'N' && controle != 'Y');
                if(controle == 'N') break;
            }
            getTimeLapse(start);
        }
        else if(controle == 2) {
            cout << "Erique's working hard" << endl;
        }
        else if(controle == 3){
            string sFileName;
            cout << "Digite o nome do arquivo: ";
            cin >> sFileName;
            
            if(!verifyExtensao(sFileName.c_str())){
                cout << "\e[1;41mError: O arquivo [" << sFileName << "] nao possui a estensao [.txt].\e[0m\n\n";
                continue;
            }
            system("cls || clear");
            int iWriteModo;
            do{
                cout << "Digite o modo de escrita:" << endl;
                cout << "\t - 0 - para ler numero por numero e usar a funcao insert." << endl;
                cout << "\t - 1 - para ler um arquivo in order completo com NULVAL." << endl << "DIGITE:  ";
                iWriteModo = get_int(); 
                
                system("cls || clear");
            }while(iWriteModo > 1 || iWriteModo < 0);
            auto start = chrono::steady_clock::now();
            int iQtdWrited = writeFile(ptrAllTree[iChooseTree - 1], sFileName.c_str(), iWriteModo);
            cout << iQtdWrited << " nohs foram escritos no arquivo [" << sFileName << "] no modo " << iWriteModo << endl;
            getTimeLapse(start);
        }   
        else if(controle == 4) return 1;
        else if(controle == 5) { 
            iChooseTree = chooseTree();
            continue;
        }
        else if(controle == 0) return 0;
    }
}

/**
 * Desenha o menu para visualizr uma arvore
 * 
 * @return inteiro usado para controle entre menu principal e sair do programa
 */
int drawMenuVisualization() {
    system("cls || clear");
    
    if(iTreeCount == 0) {
        cout << "\n\e[1;41mTemos atualmente -> " << iTreeCount << " <- arvores carregadas. ";
        cout << "Por favor, volte ao menu anterior e insira alguma arvore.\e[0m\n" << endl;
        return 1;
    }

    system("cls || clear");
    cout << endl << endl;
    for(int i = 0; i < iTreeCount; i++) {
        cout << "\n\t \e[1;43mArvore " << i + 1 << "\e[0m" << endl;
        printTreeHorizontal(ptrAllTree[i], 0, 0);
        cout << endl;
    }

    int iChooseTree = chooseTree();
    while(1){
        int controle;   
        cout << "\t\t \e[1;45m- ARVORE " << iChooseTree << " - \e[0m\n" << endl;
        cout << "- Ver na vertical com raiz no meio: \tDIGITE 1" << endl;
        cout << "- Ver na vertical in order: \t\tDIGITE 2" << endl;
        cout << "- Ver na horizontal com raiz no meio: \tDIGITE 3" << endl;
        cout << "- Deseja trocar a arvore: \t\tDIGITE 4" << endl;
        cout << "- Voltar para o menu anterior: \t\tDIGITE 5" << endl;
        cout << "- Sair do programa: \t\t\tDIGITE 0" << endl;
        cout << "\nDIGITE UM NUMERO: ";
        controle = get_int();
        system("cls || clear");
        if(controle > 5 || controle < 0) continue;
        if(controle == 1){
            cout << "--vertical root meio--\n\n";
            auto start = chrono::steady_clock::now();
            //TreePrinter(ptrAllTree[iChooseTree - 1]);
            getTimeLapse(start);
            int iGetInput;
            do{
                cout << " - Voltar no menu anterior: \tDIGITE 1" << endl;
                cout << " - Sair do programa: \t\tDIGITE 0" << endl;
                iGetInput = get_int();
                system("cls || clear");
            }while(iGetInput > 1 || iGetInput < 0);
            if(iGetInput == 0) return 0;
        }
        if(controle == 2) {
            cout << "--vertical in order--\n\n";
            auto start = chrono::steady_clock::now();
            printTreeHorizontal(ptrAllTree[iChooseTree - 1], 0, 0);
            getTimeLapse(start);
            int iGetInput;
            do{
                cout << " - Voltar no menu anterior: \tDIGITE 1" << endl;
                cout << " - Sair do programa: \t\tDIGITE 0" << endl;
                iGetInput = get_int();
                system("cls || clear");
            }while(iGetInput > 1 || iGetInput < 0);
            if(iGetInput == 0) return 0;
        }
        if(controle == 3) {
            cout << "--horizontal com raiz no meio--\n\n";
            auto start = chrono::steady_clock::now();
            printTreeHorizontal(ptrAllTree[iChooseTree - 1], 0, 1);
            getTimeLapse(start);
            int iGetInput;
            do{
                cout << " - Voltar no menu anterior: \tDIGITE 1" << endl;
                cout << " - Sair do programa: \t\tDIGITE 0" << endl;
                cout << "DIGITE:  ";
                iGetInput = get_int();
                system("cls || clear");
            }while(iGetInput > 1 || iGetInput < 0);
            if(iGetInput == 0) return 0;
        }
        else if(controle == 4) { 
            iChooseTree = chooseTree();
            continue;
        }
        else if(controle == 5) return 1;
        else if(controle == 0) return 0;
    }
}

/**
 * Desenha o menu para alterar uma arvore
 * 
 * @return inteiro usado para controle entre menu principal e sair do programa
 */
int drawMenuOrdenacao() {
    system("cls || clear");
    
    if(iTreeCount == 0 && iListCount == 0) {
        cout << "\n\e[1;41mTemos atualmente -> " << iTreeCount << " <- arvores e listas carregadas ";
        cout << "Por favor, volte ao menu anterior e insira alguma arvore.\e[0m\n" << endl;
        return 1;
    }

    while(1){
        int controle;   
        cout << "\t\t \e[1;45m- MENU ORDENACAO- \e[0m\n" << endl;
        cout << "- Converter arvore em linked list: \tDIGITE 1" << endl;
        cout << "- Ordenar lista: \t\t\tDIGITE 2" << endl;
        cout << "- Voltar ao menu anterior: \t\tDIGITE 3" << endl;
        cout << "- Sair do programa: \t\t\tDIGITE 0" << endl;
        cout << "\nDIGITE UM NUMERO: ";
        controle = get_int();
        system("cls || clear");
        if(controle == 1){
            auto start = chrono::steady_clock::now();
            Node *ptrHead = nullptr;
            Node *ptrTail = nullptr;
            for(int i = 0; i < iTreeCount; i++) {
                cout << "\n\t \e[1;43mArvore " << i + 1 << "\e[0m" << endl;
                printTreeHorizontal(ptrAllTree[i], 0, 0);
                cout << endl;
            }
            int iChooseTree = chooseTree();
            convertToLL(ptrAllTree[iChooseTree - 1], &ptrHead, &ptrTail);
            ptrAllTree[iChooseTree - 1] = nullptr;
            ptrAllLinkedList =(Node **) realloc(ptrAllLinkedList, ++iListCount);
            *(ptrAllLinkedList + iListCount - 1) = ptrHead;
            cout << "Linked list salva em: " << ptrHead << endl;
            getTimeLapse(start);
            ptrAllTree =(Node **) realloc(ptrAllTree, --iTreeCount);
        }
        else if(controle == 2) {
            if(iListCount == 0) {
                cout << "\n\e[1;41mTemos atualmente -> " << iListCount << " <- linked list carregadas. ";
                cout << "Por favor, volte ao menu anterior e converta uma arvore em linked list.\e[0m\n" << endl;
                continue;
            }

            for(int i = 0; i < iListCount; i++) {
                cout << "\n\t \e[1;43mLinked list " << i + 1 << "\e[0m" << endl;
                printLinkedList(ptrAllLinkedList[i]);
            }
            int iChooseList;
            do{
                cout << "\nCom qual lista deseja trabalhar? { ";
                for(int i = 0; i < iListCount; i++) cout << i+1 << " ";
                cout << "}\nDIGITE: ";
                iChooseList = get_int();
                system("cls || clear");
            }while(iChooseList < 1 || iChooseList > iListCount);

            while(1) {
                int iGetInput;
                cout << "Escolha metodo de ordenacao: " << endl;
                cout << "1 -> selection sort" << endl;
                cout << "2 -> bubble sort" << endl;
                cout << "3 -> insertion sort" << endl;
                cout << "4 -> shell sort" << endl;
                cout << "5 -> merge sort" << endl;
                cout << "6 -> menu anterior" << endl;
                cout << "0 -> sair do programa" << endl;
                iGetInput = get_int();
                if(iGetInput == 1) {
                    auto start = chrono::steady_clock::now();
                    int *v = convertArray(ptrAllLinkedList[iChooseList - 1]);
                    selectionSortAnimation(v, tamanho(ptrAllLinkedList[iChooseList - 1]));
                    s_sort(&(ptrAllLinkedList[iChooseList - 1]));                    
                    printLinkedList(ptrAllLinkedList[iChooseList - 1]);
                    getTimeLapse(start);
                }
                else if(iGetInput == 2) {
                    auto start = chrono::steady_clock::now();
                    int *v = convertArray(ptrAllLinkedList[iChooseList - 1]);
                    bubbleSortAnimation(v, tamanho(ptrAllLinkedList[iChooseList - 1]));
                    ptrAllLinkedList[iChooseList - 1] = b_sort(&(ptrAllLinkedList[iChooseList - 1]));
                    printLinkedList(ptrAllLinkedList[iChooseList - 1]);
                    getTimeLapse(start);
                }
                else if(iGetInput == 3) {
                    auto start = chrono::steady_clock::now();
                    int *v = convertArray(ptrAllLinkedList[iChooseList - 1]);
                    selectionSortAnimation(v, tamanho(ptrAllLinkedList[iChooseList - 1]));
                    i_sort(&(ptrAllLinkedList[iChooseList - 1]));
                    printLinkedList(ptrAllLinkedList[iChooseList - 1]);
                    getTimeLapse(start);
                }
                else if(iGetInput == 4) {
                    auto start = chrono::steady_clock::now();
                    int *v = convertArray(ptrAllLinkedList[iChooseList - 1]);
                    shellSortAnimation(v, tamanho(ptrAllLinkedList[iChooseList - 1]));
                    shell_sort(&(ptrAllLinkedList[iChooseList - 1]));
                    printLinkedList(ptrAllLinkedList[iChooseList - 1]);
                    getTimeLapse(start);
                }
                else if(iGetInput == 5) {
                    auto start = chrono::steady_clock::now();
                    ptrAllLinkedList[iChooseList - 1] = mergeSort(ptrAllLinkedList[iChooseList - 1]);

                    printLinkedList(ptrAllLinkedList[iChooseList - 1]);
                    getTimeLapse(start);
                }
                else if(iGetInput == 6) break;
                else if(iGetInput == 0) return 0;
                cout << "Deseja continuar -> 1" << endl;
                cout << "Encerrar programa -> 0" << endl;
                int iContinue = get_int();
                if(iContinue == 0) return 0;
            }
        }
        else if(controle == 3) return 1;
        else if(controle == 0) return 0;
    }
}