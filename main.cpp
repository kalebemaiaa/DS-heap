#include "auxiliar_functions.hpp"

Node **ptrAllTree;
int iTreeCount = 0;

/*
    ITEM 1
    ITEM 2
    ITEM 8
    ITEM 11 - 17
    MAIORES PROBLEMAS:
    -> PRINTAR NA VERTICAL
    -> FAZER UM MENU LEGAL E EFICIENTE COM INTERAÇÃO
    -> FAZER FILA DEVE SER UTIL PARA VERIFICAR SE E PERFEITA E PRINTAR NA VERTICAL
        POIS TEREMOS A QTD DE NOH.
*/

void drawMenu(int iMenuAtual) {
    switch(iMenuAtual) {
        case 1:
            printf("\e[1;45m");
            cout << "\t\t -MENU- \n" << endl;
            printf("\e[0m");
            cout << "- Criar nova arvore: \t\t\t DIGITE 2" << endl;
            cout << "- Obter dados de uma arvore: \t\t DIGITE 3 " << endl;
            cout << "- Alterar uma arvore: \t\t\t DIGITE 4" << endl;
            cout << "- Visualizar uma arvore: \t\t DIGITE 5" << endl;
            cout << "- Converter em lista e ordenar: \t DIGITE 6" << endl;
            cout << "- Para sair: \t\t\t\t DIGITE 0\n" << endl;
            cout << "DIGITE UM NUMERO: ";
            break;
        default:
            break;
    }
}

int drawMenuInsert() {
    while(1){
        int controle;   
        printf("\e[1;45m");
        cout << "\t\t -MENU- \n" << endl;
        printf("\e[0m");
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
                cout << "\t - 0 - para trabalhar com a funcao insert." << endl;
                cout << "\t - 1 - para ler um arquivo in order completo com NULVAL." << endl << "DIGITE:  ";
                cin >> iReadModo; 
                
                system("cls || clear");
            }while(iReadModo > 1 || iReadModo < 0);

            Node *ptrNewRoot = openFile(sFileName.c_str(), iReadModo);
            if(!ptrNewRoot) continue;

            ptrAllTree =(Node **) realloc(ptrAllTree, ++iTreeCount);
            *(ptrAllTree + iTreeCount - 1) = ptrNewRoot;
        }
        if(controle == 2) {
            Node *ptrNewRoot = nullptr;
            int iGetInput;
            while(true){
                printTree(ptrNewRoot, 0, ' ');
                cout << "\nDigite um numero para inserir na arvore:  ";
                cin >> iGetInput;
                cout << endl;
                insertNode(&ptrNewRoot, iGetInput);
                printTree(ptrNewRoot, 0, ' ');
                char controle = 'N';
                do{
                    cout << "Deseja inserir outro numero?(Y/N)  ";
                    cin >> controle;
                    cout << controle;
                    system("clear || cls");
                }while(controle != 'N' && controle != 'Y');
                if(controle == 'N') break;
            }

            ptrAllTree = (Node **) realloc(ptrAllTree, ++iTreeCount);
            *(ptrAllTree + iTreeCount - 1) = ptrNewRoot;
        }
        if(controle == 3) break;
        if(controle == 0) return 0;
    }
    return 1;
}

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

int drawMenuShow() {
    system("clear || cls");
    cout << "Temos atualmente -> " << iTreeCount << " <- arvores carregadas" << endl;
    if(iTreeCount == 0) {
        cout << "Porfavor, volte ao menu anterior e insira alguma arvore." << endl;
        return 1;
    }

    system("clear || cls");
    cout << endl << endl;
    for(int i = 0; i < iTreeCount; i++) {
        cout << "\n\t Arvore " << i + 1 << endl;
        printTree(ptrAllTree[i], 0 , ' ');
        cout << endl;
    }

    int iChooseTree = chooseTree();

    while(1){
        int controle;   
        printf("\e[1;45m");
        cout << "\t\t - ARVORE " << iChooseTree << " - \n" << endl;
        printf("\e[0m");
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

        cout << endl;
        if(controle == 7) return 1;
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
            cout << "\n\t Arvore " << iChooseTree << endl << endl;
            printTree(ptrAllTree[iChooseTree - 1], 0, ' ');
        }

        int iContinue;
        do{
            cout << "\n\n- Deseja continuar explorando a arvore: \tDIGITE 1" << endl;
            cout << "- Deseja voltar ao menu inicial: \t\tDIGITE 2" << endl;
            cout << "- Deseja trocar a arvore: \t\t\tDIGITE 3" << endl;
            cout << "- Deseja encerrar o programa: \t\t\tDIGITE 0" << endl;
            cin >> iContinue;
            system("cls || clear");
        }while(iContinue > 2 && iContinue < 0);

        if(iContinue == 0) return 0;
        if(iContinue == 2) return 1;
        if(iContinue == 3) iChooseTree = chooseTree();;
        system("cls || clear");
    }
}

int drawMenuChange() {
    system("clear || cls");
    cout << "Temos atualmente -> " << iTreeCount << " <- arvores carregadas" << endl;
    if(iTreeCount == 0) {
        cout << "Porfavor, volte ao menu anterior e insira alguma arvore." << endl;
        return 1;
    }

    system("clear || cls");
    cout << endl << endl;
    for(int i = 0; i < iTreeCount; i++) {
        cout << "\n\t Arvore " << i + 1 << endl;
        printTree(ptrAllTree[i], 0 , ' ');
        cout << endl;
    }

    int iChooseTree = chooseTree();
    while(1){
        int controle;   
        printf("\e[1;45m");
        cout << "\t\t - ARVORE " << iChooseTree << " - \n" << endl;
        printf("\e[0m");
        cout << "- Inserir elemento: \t\t\tDIGITE 1" << endl;
        cout << "- Remover elemento: \t\t\tDIGITE 2" << endl;
        cout << "- Deseja voltar ao menu anterior: \tDIGITE 3" << endl;
        cout << "- Deseja trocar a arvore: \t\tDIGITE 4" << endl;
        cout << "- Sair do programa: \t\t\tDIGITE 0" << endl;
        cout << "\nDIGITE UM NUMERO: ";
        cin >> controle;
        system("cls || clear");
        if(controle > 4 || controle < 0) continue;
        if(controle == 1) {
            int iGetInput;
            while(true){
                printTree(ptrAllTree[iChooseTree - 1], 0, ' ');
                cout << "\nDigite um numero para inserir na arvore:  ";
                cin >> iGetInput;
                cout << endl;
                insertNode(&(ptrAllTree[iChooseTree - 1]), iGetInput);
                printTree(ptrAllTree[iChooseTree - 1], 0, ' ');
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
        else if(controle == 3) return 1;
        else if(controle == 4) { 
            iChooseTree = chooseTree();
            continue;
        }
        else if(controle == 0) return 0;
    }
}

int main() {
    int controle = 1;
    while(controle){
        drawMenu(controle);
        cin >> controle;
        system("cls || clear");
        if(controle < 0 || controle > 6){
            controle = 1;
            continue;
        }
        if(controle == 2) controle = drawMenuInsert();
        if(controle == 3) controle = drawMenuShow();
        if(controle == 4) controle = drawMenuChange();
    };
    /*
    Node *root = nullptr;
    root = openFile("t.txt", 0) ;
    printVertical(root, 1, 1);
    */
    return 0;
}

