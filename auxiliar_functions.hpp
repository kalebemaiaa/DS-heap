#include <iostream>
#include <stdlib.h>
#include <cmath>

#define NULLVAL -666

using namespace std;

typedef struct Node {
    int iData;
    Node *ptrLeft, *ptrRight;
} Node;

Node **ptrAllTree;
int iTreeCount = 0;

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
    int aux = ptrNoh -> iData;
    free(ptrNoh);
    return aux;
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

bool isPerfect(Node *root) {
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
 * @param out ponteiro para o arquivo
 * @return inteiro que indica a quantidade de elementos escritos
 */
int writingComplete(Node *ptrRoot, FILE *ptrOut) {
    int iCountNohs = 0;
    if(!ptrRoot){
        fprintf(ptrOut, "%i ", NULLVAL);
        return iCountNohs;
    }

    fprintf(ptrOut, "%i ", ptrRoot -> iData);
    iCountNohs += writingComplete(ptrRoot -> ptrLeft, ptrOut);
    iCountNohs += writingComplete(ptrRoot -> ptrRight, ptrOut);
    return iCountNohs;
}

static int writeAuxiliar(Node *ptrRoot, FILE *out) {
    if(!out || !ptrRoot) return 0;
    fprintf(out, "%i ", ptrRoot -> iData);
    return 1 + writeAuxiliar(ptrRoot -> ptrLeft, out) + writeAuxiliar(ptrRoot -> ptrRight, out);
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
    int iQtdWrited = -2;
    if(iFormat2Write == 0) 
        iQtdWrited = writeAuxiliar(root, out);
    else
        iQtdWrited = writingComplete(root, out);

    fclose(out);
    return iQtdWrited;
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
    return root;
}

// Função que converte uma árvore para lista duplamente encadeada
void convertToLL(Node* root, Node** head, Node** tail) {
    if (root == nullptr) {
        return;
    }

    // Converter a subárvore esquerda em uma lista duplamente encadeada
    convertToLL(root->ptrLeft, head, tail);

    // Conectar a raiz à lista duplamente encadeada
    if (*head == nullptr) {
        *head = root;
    } else {
        (*tail)->ptrRight = root;
        root->ptrLeft = *tail;
    }

    *tail = root;

    // Converter a subárvore direita em uma lista duplamente encadeada
    convertToLL(root->ptrRight, head, tail);
}

// FUNÇÕES INCREMENTADAS PARA ORDENAÇÃO DE LISTA ENCADEADA DUPLA:
Node *troca(Node *inicio, Node *item1, Node *item2){
    Node *aux;
    // inicio = item2;
    if(item1->prev == nullptr) inicio = item2;
    if(item2->prev == nullptr) inicio = item1;
    if(item2->prev == item1){
        if(item1->prev != nullptr) item1->prev->next = item2;
        if(item2->next != nullptr) item2->next->prev = item1;
        item1->next = item2->next;
        item2->prev = item1->prev;
        item2->next = item1;
        item1->prev = item2;
    }

    else if(item1->prev == item2){
        if(item1->next != nullptr) item1->next->prev = item2;
        if(item2->prev != nullptr) item2->prev->next = item1;
        item2->next = item1->next;
        item1->prev = item2->prev;
        item1->next = item2;
        item2->prev = item1;
    }
    else{
        if(item1->prev != nullptr) item1->prev->next = item2;
        if(item2->next != nullptr) item2->next->prev = item1;
        if(item1->next != nullptr) item1->next->prev = item2;
        if(item2->prev != nullptr) item2->prev->next = item1;
        aux = item1->prev;
        item1->prev = item2->prev;
        item2->prev = aux;
        aux = item1->next;
        item1->next = item2->next;
        item2->next = aux;
    }
    
    return inicio;
};

Node* b_sort(Node **item1){
    bool teste = true;
    Node* item2 = (*item1)->next;
    Node* inicio = *item1;

    while(teste == true){
        teste = false;

        while((*item1)->next != nullptr){
            item2 = (*item1)->next;

            if(item2->data < (*item1)->data){
                inicio = troca(inicio, *item1, item2);
                teste = true;

            }
            else{
                *item1 = (*item1)->next;
            }
        }
        *item1 = inicio;
    }
    return inicio;
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

// A função convertToLL é usada para realizar a conversão da árvore para a lista duplamente encadeada
// A função recebe três argumentos: o ponteiro para a raiz da árvore (root), o ponteiro para o 
// ponteiro para a cabeça da lista (head), e o ponteiro para o ponteiro para o final da lista (tail).

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
        cin >> controle;
        system("cls || clear");
        
        if(controle == 1){
            string sFileName;
            cout << "Digite o nome do arquivo: ";
            cin >> sFileName;
            system("cls || clear");
            int iReadModo;
            do{
                cout << "Digite o modo de leitura:" << endl;
                cout << "\t - 0 - para ler numero por numero e usar a funcao insert." << endl;
                cout << "\t - 1 - para ler um arquivo in order completo com NULVAL." << endl << "DIGITE:  ";
                cin >> iReadModo; 
                
                system("cls || clear");
            }while(iReadModo > 1 || iReadModo < 0);

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
                cin >> iGetInput;
                cout << endl;
                insertNode(&ptrNewRoot, iGetInput);
                printTreeHorizontal(ptrNewRoot, 0, 1);
                char controle;
                do{
                    cout << "Deseja inserir outro numero?(Y/N)  ";
                    cin >> controle;
                    cout << controle;
                    system("clear || cls");
                }while(controle != 'N' && controle != 'n' && controle != 'Y' && controle != 'y');

                if(controle == 'N' || controle == 'n') break;
            }

            ptrAllTree = (Node **) realloc(ptrAllTree, ++iTreeCount);
            *(ptrAllTree + iTreeCount - 1) = ptrNewRoot;
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
        cin >> iChooseTree;
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
    system("clear || cls");
    if(iTreeCount == 0) {
        cout << "\n\e[1;41mTemos atualmente -> " << iTreeCount << " <- arvores carregadas. ";
        cout << "Por favor, volte ao menu anterior e insira alguma arvore.\e[0m\n" << endl;
        return 1;
    }

    system("clear || cls");
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
        cout << "- Buscar endereço de um elemento: \tDIGITE 3" << endl;
        cout << "- Ver se a arvore e completa: \t\tDIGITE 4" << endl;
        cout << "- Ver se a arvore e perfeita: \t\tDIGITE 5" << endl;
        cout << "- Exibir arvore: \t\t\tDIGITE 6" << endl;
        cout << "- Deseja voltar ao menu anterior: \tDIGITE 7" << endl;
        cout << "- Deseja trocar a arvore: \t\tDIGITE 8" << endl;
        cout << "- Sair do programa: \t\t\tDIGITE 0" << endl;
        cout << "\nDIGITE UM NUMERO: ";
        cin >> controle;
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
            cin >> iValue2Search;
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
            cin >> iContinue;
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
    system("clear || cls");
    
    if(iTreeCount == 0) {
        cout << "\n\e[1;41mTemos atualmente -> " << iTreeCount << " <- arvores carregadas. ";
        cout << "Por favor, volte ao menu anterior e insira alguma arvore.\e[0m\n" << endl;
        return 1;
    }

    system("clear || cls");
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
        cout << "\nDIGITE UM NUMERO: ";
        cin >> controle;
        system("cls || clear");
        if(controle > 4 || controle < 0) continue;
        if(controle == 1) {
            int iGetInput;
            while(true){
                printTreeHorizontal(ptrAllTree[iChooseTree - 1], 0, 1);
                cout << "\nDigite um numero para inserir na arvore:  ";
                cin >> iGetInput;
                cout << endl;
                insertNode(&(ptrAllTree[iChooseTree - 1]), iGetInput);
                printTreeHorizontal(ptrAllTree[iChooseTree - 1], 0, 1);
                char controle = 'N';
                do{
                    cout << "Deseja inserir outro numero?(Y/N)  ";
                    cin >> controle;
                    cout << controle;
                    system("clear || cls");
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
            system("cls || clear");
            int iWriteModo;
            do{
                cout << "Digite o modo de escrita:" << endl;
                cout << "\t - 0 - para ler numero por numero e usar a funcao insert." << endl;
                cout << "\t - 1 - para ler um arquivo in order completo com NULVAL." << endl << "DIGITE:  ";
                cin >> iWriteModo; 
                
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
    system("clear || cls");
    
    if(iTreeCount == 0) {
        cout << "\n\e[1;41mTemos atualmente -> " << iTreeCount << " <- arvores carregadas. ";
        cout << "Por favor, volte ao menu anterior e insira alguma arvore.\e[0m\n" << endl;
        return 1;
    }

    system("clear || cls");
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
        cin >> controle;
        system("cls || clear");
        if(controle > 4 || controle < 0) continue;

        if(controle == 2) {
            cout << "--vertical in order--\n\n";
            printTreeHorizontal(ptrAllTree[iChooseTree - 1], 0, 0);
            int iGetInput;
            do{
                cout << " - Voltar no menu anterior: DIGITE 1" << endl;
                cout << " - Sair do programa: \tDIGITE 0" << endl;
                cin >> iGetInput;
                system("clear || cls");
            }while(iGetInput > 1 || iGetInput < 0);
            if(iGetInput == 0) return 0;
        }
        if(controle == 3) {
            cout << "--horizontal com raiz no meio--\n\n";
            printTreeHorizontal(ptrAllTree[iChooseTree - 1], 0, 1);
            int iGetInput;
            do{
                cout << " - Voltar no menu anterior: \tDIGITE 1" << endl;
                cout << " - Sair do programa: \tDIGITE 0" << endl;
                cin >> iGetInput;
                system("clear || cls");
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


