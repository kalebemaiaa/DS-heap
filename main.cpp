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

int main() {
    /*
    int controle = 1;
    while(controle){
        drawMenu(controle);
        cin >> controle;
        if(controle < 0 || controle > 6)
            controle = 1;
        system("cls || clear");
    };
    */   
    
    while(1){
        int controle;   
        cout << "Menu" << endl;
        cout << "Inserir via arquivo: DIGITE 1" << endl;
        cout << "Inserir via terminal: DIGITE 2" << endl;
        cout << "Voltar no menu anterior: DIGITE 3" << endl;
        cout << "Para sair do programa: DIGITE 0" << endl;
        cin >> controle;
        system("cls || clear");
        switch(controle){
            case(1):
                break;
            case(2):
                Node *ptrNewRoot = nullptr;
                int iGetInput;
                while(true){
                    cout << "Digite um numero para inserir na arvore:  ";
                    cin >> iGetInput;
                    cout << endl;
                    insertNode(&ptrNewRoot, iGetInput);
                    printTree(ptrNewRoot, 0, ' ');

                    char controle;
                    do{
                        cout << "Deseja inserir outro número?(Y/N)  ";
                        cin >> controle;
                        system("clear || cls");
                    }while(controle != 'N' && controle != 'Y');
                    if(controle == 'N') break;
                }

                ptrAllTree =(Node **) realloc(ptrAllTree, ++iTreeCount);
                *(ptrAllTree + iTreeCount - 1) = ptrNewRoot;
                break;
            default:
            break;
        }
        system("clear || cls");
        if(!controle) break;
    }

    for(int i = 0; i < iTreeCount; i++) {
        cout << "\t -Arvore \n" << i + 1 << "-" << endl;
        printTree(ptrAllTree[i], 0 , ' ');
    }
    return 0;
}
