#include "auxiliar_functions.hpp"

/*
    ITEM 2
    ITEM 8
    ITEM 11 - 17
    MAIORES PROBLEMAS:
    -> PRINTAR NA VERTICAL
    -> FAZER UM MENU LEGAL E EFICIENTE COM INTERAÇÃO
    -> FAZER FILA DEVE SER UTIL PARA VERIFICAR SE E PERFEITA E PRINTAR NA VERTICAL
        POIS TEREMOS A QTD DE NOH.
*/

int main() {
    int controle = 1;
    while(controle){
        drawMenu();
        cin >> controle;
        system("cls || clear");
        if(controle < 0 || controle > 6){
            controle = 1;
            continue;
        }
        if(controle == 2) controle = drawMenuInsert();
        else if(controle == 3) controle = drawMenuShow();
        else if(controle == 4) controle = drawMenuChange();
        else if(controle == 5) controle = drawMenuVisualization();
    };
    return 0;
}
