#include <iostream>
#include <cmath>

#include "CShape.h"
#include "CRectangle.h"
#include "CRhombus.h"
#include "CIsoscelesTriangle.h"
#include "LogicManager.h"


using namespace std;




 
void printMenu();
void menuSelector(int selector, LogicManager myLogicManager);

int main()
{
    LogicManager myLogicManager;

    printMenu();

    int selector = -1;

    while(selector != 0){
    cout << "Inserire un numero : " ;
    
    try {
            cin >> selector;

            if(cin.fail() == true){
                throw "Il carattere inserito non e' un numero!"; 
            }

            if(selector < 0 || selector >6){
                throw selector;
            }
        }
    catch(const char* error){
        cout << error << endl;
        cin.clear();

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        selector = -1;

        printMenu();
    }
    catch(int error){
        cout << "Inserire un numero intero compreso tra 0 e 6!" << endl;
        selector = -1;

        printMenu();
    }
    
    menuSelector(selector,myLogicManager);

    }

    cout << endl << "===== FINE TEST =====" << endl;

}

void printMenu(){
    cout << "1-Visualizza tutti i  poligoni" << endl;
    cout << "2-Modifica le proprietà di un poligono" << endl;
    cout << "3-Sposta un poligono sulla griglia" << endl;
    cout << "4-Inserisci un nuovo poligono" << endl;
    cout << "5-Cancella un poligono" << endl;
    cout << "6-Cancella tutti i poligono" << endl;
    cout << "0-Esci" << endl;
}


void menuSelector(int selector,LogicManager myLogicManager){
    switch (selector)
    {
    case 1:
        myLogicManager.printPolygonList();
        break;
    case 2:
        myLogicManager.modifyPolygon();
        break;
    case 3:
        myLogicManager.movePolygon();
        break;
    case 4:
        myLogicManager.newPolygon();
        break;
    case 5:
        myLogicManager.deletePolygon();
        break;
    case 6: 
        myLogicManager.deleteAllPolygon();
        break;
    default:
        //selector = 0 -> Exit
        break;
    }
}