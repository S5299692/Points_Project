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
        for(int i = 0; i < (int)shapes.size(); i++){
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

void LogicManager::modifyPolygon(){
    if(getPolygonList()==0){
        std::cout << "Non ci sono Poligoni nella Lista!"<< std::endl;
        return;
    }
    std::cout << "Inserire il numero del Poligono che si vuole modificare: ";
    int index = -1;
    while(true){       
        try{
            std::cin >> index;
            if(std::cin.fail()){
                throw "Non è stato inserito un numero!";
            }
            if(index < 0 || index >= (int)shapes.size()){
                throw index; 
            }
            break;
        }
        catch(int){
            std::cout<<"L'indice inserito non è presente!" << std::endl;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        catch(const char* error){
            std::cout << error << std::endl;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Inserire nuovo testo (vuoto se non si vuole modificare):" << std::endl;
    std::string newText;
    
    std::getline(std::cin, newText);
    
    if (!newText.empty())
    {
        shapes[index] -> SetText(newText.c_str());
    }
    while(true){
        std::cout << "Inserire nuove dimensioni separate da una virgola (vuoto se non si vuole modificare): " << std::endl;
        std::string input;

        std::getline(std::cin,input);
        if(input.empty()){
            break;
        }

        size_t commaPos = input.find(',');

        if (commaPos == std::string::npos) {
            std::cout << "Virgola non trovata!\n";
            continue;
        }

        std::string firstPart = input.substr(0, commaPos);
        std::string secondPart = input.substr(commaPos + 1);

        try {
            size_t pos1,pos2;

            int newDimX = std::stoi(firstPart, &pos1);
            int newDimY = std::stoi(secondPart, &pos2);

            if(pos1 != firstPart.size() || pos2 != secondPart.size()){
                throw std::invalid_argument("Input non valido");
            }

            int posX = shapes[index]->GetX();
            int posY = shapes[index]->GetY();

            if(posX + (newDimX/2) > 100 || posX -(newDimX/2) < 0 || posY + (newDimY/2) > 100 || posY -(newDimY/2) < 0 ){
                throw "Le dimensioni inserite fanno uscire la figura dalla Bounding Box (100x100)";
            }

            shapes[index]->SetWidth(newDimX);
            shapes[index]->SetHeight(newDimY);

            break;

        }
        catch (const char* error){
            std::cout << error << std::endl;
        }
        catch (const std::exception&) {
            std::cout << "Input non valido!\n";
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



