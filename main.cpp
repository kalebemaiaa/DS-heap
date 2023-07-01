#include "auxiliar_functions.hpp"

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
        else if(controle == 6) controle = drawMenuOrdenacao();
    };
    return 0;
}
