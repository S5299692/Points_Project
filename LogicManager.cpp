/*! \file LogicManager.h
    \brief Declaration of the base class LogicManager
	\author Nicolò Forciniti
*/

#include "LogicManager.h"
#include "CShape.h"
#include "iostream"
#include "limits"

LogicManager::LogicManager(){

}

void LogicManager::printPolygonList(){
    if(shapes.size() == 0){
        std::cout << "Non ci sono Shapes nella Lista!" << std::endl;
    }
    else
    { 
        for(int i = 0; i<shapes.size(); i++){
            std::cout << "Indice Shape["<< i<<"]"<< std::endl; 
            shapes[i]->boxDump();    
        }
    }

    std::cout << "Si vuole ottenere informazioni maggiori su un Poligono? \n1 : Index of the Polygon \n-1 : No "<< std::endl;
    int index = -1;
    while(true){
        try{
            std::cin >> index;

            if(std::cin.fail()){
                throw "Non è stato inserito un numero!";
            }
            if(index == -1){
                std::cout << "Uscito!"<< std::endl;
                break;
            }
            if(index < 0  || index >= shapes.size()){
                throw index; 
            }
            
            shapes[index]->Dump();
        }
        catch(int index){
           std::cout<<"L'indice inserito non è presente!" << std::endl;
        }
        catch(const char* error){
            std::cout << error << std::endl;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void LogicManager::modifyPoligon(){
    if(getPolygonList()==0){
    }
    else{
        std::cout << "Inserire il numero del Poligono che si vuole modificare: ";
        int index = -1;
        while(true){       
        try{
            std::cin >> index;
            if(index < 0 || index > shapes.size()){
                throw index; 
            }
            if(std::cin.fail()){
                throw "Non è stato inserito un numero!";
            }
            break;
        }
        catch(int index){
            std::cout<<"L'indice inserito non è presente!" << std::endl;
        }
        catch(const char* error){
            std::cout << error << std::endl;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    }
}

int LogicManager::getPolygonList(){
    if(shapes.size() == 0){
        std::cout << "Non ci sono Shapes nella Lista!" << std::endl;
        return 0;
    }
    else
    { 
        return 1;
    }
}



