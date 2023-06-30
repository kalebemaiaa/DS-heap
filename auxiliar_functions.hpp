#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <chrono>

#define NULLVAL -666

using namespace std;

typedef struct Node {
    int iData;
    Node *ptrLeft, *ptrRight;
} Node;

Node **ptrAllTree;
int iTreeCount = 0;

double measure_execution_time() {
    chrono::high_resolution_clock::time_point start_time = chrono::high_resolution_clock::now();

    // CHAMAR A FUNCAO QUE QUERO MEDIR AQUI
    //funcao();  // Chama a função que você deseja medir

    chrono::high_resolution_clock::time_point end_time = chrono::high_resolution_clock::now();

    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(end_time - start_time);

   return time_span.count();
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
 * Deleta determinado noh
 * 
 * @param ptrNoh endereco do noh a ser deletado
 * @return interio que o noh armazenava
 */
int deleteNode(Node *ptrNoh) {
    if(!ptrNoh) return NULLVAL;
    int iAux = ptrNoh -> iData;
    free(ptrNoh);
    return iAux;
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


bool isPerfect(Node *ptrRoot) {
    return true;
}

/**
 * Dado o endereço da raiz, diz se a arvore é completa
 * 
 * @param ptrRoot endereço que guarda a raiz
 * @return booleano que indica se é ou nao perfeita
 */
bool isComplete(Node *ptrRoot) {
    if(!ptrRoot) return true;
    if((!(ptrRoot -> ptrLeft) && (ptrRoot -> ptrRight)) || (ptrRoot -> ptrLeft) && !(ptrRoot -> ptrRight)) return false;
    if(!isComplete(ptrRoot -> ptrLeft) || !isComplete(ptrRoot -> ptrRight)) return false;
    return true;
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
    cout << "\n\e[1;42mArvore carregada, raiz em :" << ptrNewRoot << "  \e[0m" << endl << endl;
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


/*
// FUNÇÕES INCREMENTADAS PARA ORDENAÇÃO DE LISTA ENCADEADA DUPLA:
Node *troca(Node *ptrInicio, Node *ptrHead1, Node *ptrHead2){
    Node *aux;
    // ptrInicio = ptrHead2;
    if(ptrHead1->prev == nullptr) ptrInicio = ptrHead2;
    if(ptrHead2->prev == nullptr) ptrInicio = ptrHead1;
    if(ptrHead2->prev == ptrHead1){
        if(ptrHead1->prev != nullptr) ptrHead1->prev->next = ptrHead2;
        if(ptrHead2->next != nullptr) ptrHead2->next->prev = ptrHead1;
        ptrHead1->next = ptrHead2->next;
        ptrHead2->prev = ptrHead1->prev;
        ptrHead2->next = ptrHead1;
        ptrHead1->prev = ptrHead2;
    }

    else if(ptrHead1->prev == ptrHead2){
        if(ptrHead1->next != nullptr) ptrHead1->next->prev = ptrHead2;
        if(ptrHead2->prev != nullptr) ptrHead2->prev->next = ptrHead1;
        ptrHead2->next = ptrHead1->next;
        ptrHead1->prev = ptrHead2->prev;
        ptrHead1->next = ptrHead2;
        ptrHead2->prev = ptrHead1;
    }
    else{
        if(ptrHead1->prev != nullptr) ptrHead1->prev->next = ptrHead2;
        if(ptrHead2->next != nullptr) ptrHead2->next->prev = ptrHead1;
        if(ptrHead1->next != nullptr) ptrHead1->next->prev = ptrHead2;
        if(ptrHead2->prev != nullptr) ptrHead2->prev->next = ptrHead1;
        aux = ptrHead1->prev;
        ptrHead1->prev = ptrHead2->prev;
        ptrHead2->prev = aux;
        aux = ptrHead1->next;
        ptrHead1->next = ptrHead2->next;
        ptrHead2->next = aux;
    }
    
    return ptrInicio;
};

Node* b_sort(Node **ptrHead1){
    bool bTeste = true;
    Node* ptrHead2 = (*ptrHead1)->next;
    Node* ptrNewHead = *ptrHead1;

    while(bTeste == true){
        bTeste = false;

        while((*ptrHead1)->next != nullptr){
            ptrHead2 = (*ptrHead1)->next;

            if(ptrHead2->data < (*ptrHead1)->data){
                ptrNewHead = troca(ptrNewHead, *ptrHead1, ptrHead2);
                bTeste = true;

            }
            else{
                *ptrHead1 = (*ptrHead1)->next;
            }
        }
        *ptrHead1 = ptrNewHead;
    }
    return ptrNewHead;
};

void posiciona(Node **inicio, Node *item){
    Node *aux = item;
    int dat = item->data;
    
    if(item->prev == nullptr) return;

    while(item->prev != nullptr && item->prev->data > dat){
        item = item->prev;
    }

    if(item->data <= dat) return;

    if(item->next != aux){
        if(item->prev != nullptr) item->prev->next = aux;
        else{
            *inicio = aux;
        }
        if(aux->next != nullptr) aux->next->prev = aux->prev;
        if(aux->prev != nullptr) aux->prev->next = aux->next;
        aux->next = item;
        aux->prev = item->prev;
        item->prev = aux;
    }

    else if(item->next == aux){
        *inicio = troca(*inicio, item, aux); 
        // if(item->prev != nullptr) item->prev->next = aux;
        // else{
        //     *inicio = aux;
        // }
        // if(aux->next != nullptr) aux->next->prev = item;
        // aux->prev = item->prev;
        // item->prev = aux;
        // item->next = aux->next;
        // aux->next = item;
    }
    
};

void i_sort(Node **inicio){
    Node *aux = *inicio, *aux2;
    
    while(aux != nullptr){
        aux2 = aux->next;
        posiciona(inicio, aux);
        aux = aux2;
    }
};

int tamanho(Node *inicio){
    int cont = 0;
    while(inicio != nullptr){
        inicio = inicio->next;
        cont ++;
    }
    return cont;
};

void shell_sort(Node **inicio){
    Node *aux = *inicio, *lista1, *lista2, *idivide_lista;
    int itamanho = tamanho(aux), i = 0;
    
    while(i < itamanho/2){
        aux = aux->next;
        i++;
    }
    if(itamanho % 2 == 0) idivide_lista = aux;
    else idivide_lista = aux->next;
    aux = *inicio;

    Node *tmp, *tmp2, *aux2;
    
    if(aux->data > idivide_lista->data){
        *inicio = troca(*inicio, aux, idivide_lista);
        idivide_lista = aux;
    } 

    while(idivide_lista != nullptr){
        tmp = idivide_lista->next;
        tmp2 = aux->next;
        if(idivide_lista->data < aux->data){
            *inicio = troca(*inicio, aux, idivide_lista);
        }

        idivide_lista = tmp;
        aux = tmp2;
    }

    i = 0;
    aux = *inicio;

    while(i < (itamanho/2) - 1){
        aux = aux->next;
        i++;
    }

    idivide_lista = aux;
    aux = idivide_lista->prev->prev;

    while(idivide_lista != nullptr){
        tmp = idivide_lista->next;
        tmp2 = idivide_lista->prev;
        
        while(aux != nullptr){

            if(idivide_lista->data < aux->data){
                *inicio = troca(*inicio, aux, idivide_lista);
                if(idivide_lista->prev != nullptr) aux = (idivide_lista->prev)->prev;
                else aux = nullptr;
            }
            else aux = nullptr;

        }
        idivide_lista = tmp;
        aux = tmp2;
    }

    i_sort(inicio);

};

void s_sort_aux(Node **inicio){
    Node *aux = *inicio, *menor = *inicio;

    while(aux->next != nullptr){
        if((aux->next)->data <= menor->data){
            menor = aux->next;
        }
        aux = aux->next;
    }

    *inicio = troca(*inicio, *inicio, menor);
};

void s_sort(Node **inicio){
    s_sort_aux(inicio);
    Node *aux = (*inicio)->next, *aux2;
    while(aux->next != nullptr){
        aux2 = aux->next;
        s_sort_aux(&aux);
        aux = aux2;
    }
};
*/


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
        }
        else if(controle == 2) {
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
            cout << "\n\e[1;42mArvore carregada, raiz em :" << ptrNewRoot << "  \e[0m" << endl << endl;
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
            cout << "A altura da arvore e: " << getHeight(ptrAllTree[iChooseTree - 1]) << endl;
        }
        else if(controle == 2) {
            cout << "O tamanho da arvore e: " << getSize(ptrAllTree[iChooseTree - 1]) << endl;
        }
        else if(controle == 3) {
            int iValue2Search;
            cout << "Digite um valor para ser procurado:  ";
            iValue2Search = get_int();
            system("cls || clear");
            Node *ptrValue = searchValue(ptrAllTree[iChooseTree - 1], iValue2Search);

            if(!ptrValue) 
                cout << "O valor que voce procurava nao foi encontrado." << endl;
            else
                cout << "O valor que voce procurava esta em: " << ptrValue << endl;
        }
        else if(controle == 4) {
            isComplete(ptrAllTree[iChooseTree - 1]) ? cout << "A arvore e completa" << endl : cout << "A arvore e incompleta" << endl;
        }
        else if(controle == 5) {
            isPerfect(ptrAllTree[iChooseTree - 1]) ? cout << "A arvore e perfeita" << endl : cout << "A arvore e imperfeita" << endl;
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
            int iQtdWrited = writeFile(ptrAllTree[iChooseTree - 1], sFileName.c_str(), iWriteModo);
            cout << iQtdWrited << " nohs foram escritos no arquivo [" << sFileName << "] no modo " << iWriteModo << endl;
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
 * Desenha o menu para alterar uma arvore
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
        cout << "- Sair do programa: \t\t\tDIGITE 0" << endl;
        cout << "\nDIGITE UM NUMERO: ";
        controle = get_int();
        system("cls || clear");
        if(controle > 4 || controle < 0) continue;

        if(controle == 2) {
            cout << "--vertical in order--\n\n";
            printTreeHorizontal(ptrAllTree[iChooseTree - 1], 0, 0);
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
            printTreeHorizontal(ptrAllTree[iChooseTree - 1], 0, 1);
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
        else if(controle == 2) {
            cout << "Erique's working hard" << endl;
        }
        else if(controle == 3) return 1;
        else if(controle == 4) { 
            iChooseTree = chooseTree();
            continue;
        }
        else if(controle == 0) return 0;
    }
}
