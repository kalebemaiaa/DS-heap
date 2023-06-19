#include "auxiliar_functions.hpp"

/* QUANDO TRABALHAR COM VARIAS ARVORES
Node **ptrAllTree = nullptr;
int iTreeCount = 0;
*/


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
    int controle = 1;
    while(controle){
        drawMenu(controle);
        cin >> controle;
        if(controle < 0 || controle > 6)
            controle = 1;
        system("cls || clear");
    };
    return 0;
}
