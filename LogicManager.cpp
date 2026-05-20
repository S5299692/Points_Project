/*! \file LogicManager.h
    \brief Declaration of the base class LogicManager
	\author Nicolò Forciniti
*/

#include "LogicManager.h"
#include "CShape.h"
#include "CRectangle.h"
#include "CRhombus.h"
#include "CIsoscelesTriangle.h"
#include "iostream"
#include "limits"


/* ----------------------------
   CONSTRUCTORS / DESTRUCTOR
   ---------------------------- */
LogicManager::LogicManager(){

}

LogicManager::~LogicManager(){
    deleteAllPolygon();
}

/* ----------------------------
   OPERATORS
   ---------------------------- */


/* ----------------------------
   BASIC HANDLING
   ---------------------------- */
/// @brief Print the List of Shapes currently present in @p shapes .
/// @return 0 when empty 1 when populated
void LogicManager::printPolygonList(){
    if(shapes.size() == 0){
        std::cout << "Non ci sono Shapes nella Lista!" << std::endl;
        return;
    }
    else
    {
        for (int i = 0; i < (int)shapes.size(); i++)
        {
            std::cout << "============Indice Shape[" << i << "]============" << std::endl;
            shapes[i]->boxDump();
            std::cout << "=======================================" << std::endl;
        }
    }

    std::cout << "Si vuole ottenere informazioni maggiori su un Poligono? \n1 : Index of the Polygon \n-1 : No "<< std::endl;
    int index = -1;
    while(true){
        try{
            std::cin >> index;

            if(std::cin.fail()){
                throw "Non e' stato inserito un numero!";
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if(index == -1){
                std::cout << "Uscito!"<< std::endl;
                break;
            }
            if(index < 0  || index >= shapes.size()){
                throw index; 
            }
            
            shapes[index]->Dump();
            break;
        }
        catch(int index){
           std::cout<<"L'indice inserito non e' presente!" << std::endl;
        }
        catch(const char* error){
            std::cout << error << std::endl;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

/// @brief Modify a Polygon present in the @p shapes list.
void LogicManager::modifyPolygon(){
    int index = getValidIndex(shapes.size() ,"Inserire il numero del Poligono che si vuole modificare :");
    if(index == -1)return;

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

            if(posX + (newDimX/2.0) > 100 || posX -(newDimX/2.0) < 0 || posY + (newDimY/2.0) > 100 || posY -(newDimY/2.0) < 0 ){
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

/// @brief Move a Polygon inside the bounding box.
void LogicManager::movePolygon(){

    printPolygonListIdex();

    int index = getValidIndex(shapes.size() ,"Inserire il numero del Poligono che si vuole muovere : ");
    if(index == -1)return;

    while(true){
        std::cout << "Inserire le nuove X e Y separate da una virgola (vuoto se non si vuole modificare): " << std::endl;
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

            int newPosX = std::stoi(firstPart, &pos1);
            int newPosY = std::stoi(secondPart, &pos2);

            if(pos1 != firstPart.size() || pos2 != secondPart.size()){
                throw std::invalid_argument("Input non valido");
            }

            int dimX = shapes[index]->GetWidth();
            int dimY = shapes[index]->GetHeight();

            if(newPosX + (dimX/2.0) > 100 || newPosX -(dimX/2.0) < 0 || newPosY + (dimY/2.0) > 100 || newPosY -(dimY/2.0) < 0 ){
                throw "Le dimensioni inserite fanno uscire la figura dalla Bounding Box (100x100)";
            }

            shapes[index]->SetPosition(newPosX, newPosY);
            
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

/// @brief Create a new Polygon inside the bounding box.
void LogicManager::newPolygon(){
    std::cout << "Selezionare il tipo di poligono che si vuole aggiungere" << std::endl;
    std::cout << "1 - Rettangolo"<< std::endl;
    std::cout << "2 - Rombo"<< std::endl;
    std::cout << "3 - Triangolo Isoscele"<< std::endl;
    int selector = -1;

    while(true){
        std::cin >> selector;
        
        if (std::cin.fail())
        {
            std::cout << "Non e' stato inserito un numero!" << std::endl;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue;
        }

        if (selector != 1 && selector != 2 && selector != 3 )
        {
            std::cout << "L'indice della funzione inserito non e' presente!" << std::endl;

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        break;
    }

    int x,y,width,height;

    while (true)
    {
        std::cout << "Inserire X,Y,Width,Height separati da virgole: " << std::endl;

        std::string input;
        std::getline(std::cin, input);

        if(input.empty())
        {
            std::cout << "Input vuoto!" << std::endl;
            continue;
        }

        size_t firstComma = input.find(',');
        size_t secondComma = input.find(',', firstComma + 1);
        size_t thirdComma = input.find(',', secondComma + 1);

        if(firstComma == std::string::npos || secondComma == std::string::npos ||thirdComma == std::string::npos)
        {
            std::cout << "Formato non valido!" << std::endl;
            continue;
        }

        try
        {
            std::string xStr = input.substr(0, firstComma);

            std::string yStr = input.substr(firstComma + 1,secondComma - firstComma - 1);

            std::string widthStr = input.substr(secondComma + 1,thirdComma - secondComma - 1);

            std::string heightStr = input.substr(thirdComma + 1);

            size_t pos1, pos2, pos3, pos4;

            x = std::stoi(xStr, &pos1);
            y = std::stoi(yStr, &pos2);
            width = std::stoi(widthStr, &pos3);
            height = std::stoi(heightStr, &pos4);

            if(pos1 != xStr.size() || pos2 != yStr.size() || pos3 != widthStr.size() || pos4 != heightStr.size())
            {
                throw std::invalid_argument("Input non valido");
            }

            if(width <= 0 || height <= 0)
            {
                std::cout << "Width e Height devono essere positivi!" << std::endl;
                continue;
            }

            if(x + (width / 2.0) > 100 || x - (width / 2.0) < 0   || y + (height / 2.0) > 100 || y - (height / 2.0) < 0)
            {
                std::cout << "Il poligono esce dalla Bounding Box!" << std::endl;
                continue;
            }
            break;
        }
        catch(const std::exception&)
        {
            std::cout << "Input non valido!" << std::endl;
        }
    }
    

    switch (selector)
    {
    case 1:
        shapes.push_back(new Rectangle(x,y,width,height));
        break;
    
    case 2:
        shapes.push_back(new Rhombus(x,y,width,height));
        break;
    case 3:
        shapes.push_back(new IsoscelesTriangle(x,y,width,height));
        break;
    default:
        std::cout << "Qualcosa e' andato storto!" << std::endl;
        break;
    }

}

/// @brief Delete a Polygon in @p shapes.
void LogicManager::deletePolygon(){
    int index = getValidIndex(shapes.size(), "Inserire l'indice del poligono che si vuole cancellare!");
    if(index == -1)return;

    delete shapes[index];

    shapes.erase(shapes.begin() + index);
}

/// @brief Delete All the Polygon in @p shapes.
void LogicManager::deleteAllPolygon(){
    for(Shape* shape: shapes){
        delete shape;
    }

    shapes.clear();
}

/// @brief Print the List of All Index present in @p shapes .
void LogicManager::printPolygonListIdex()
{
    for (int i = 0; i < (int)shapes.size(); i++)
    {
        std::cout << "Indice Shape[" << i << "]" << std::endl;
    }
}

/* ----------------------------
   GETTERS
   ---------------------------- */
/// @brief Get the list of Polygon of @p shapes .
/// @return 0 when empty and 1 when populated.    
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

/// @brief A function to get a valid Index. 
/// @param maxSize the max sise of the array we want an index for.
/// @param request a string that gets printed to the console for aesthetic purpose.
/// @return an integer that rapresent a Valid Index.
int LogicManager::getValidIndex(size_t maxSize, const char* request)
{
    if(getPolygonList()==0){
        std::cout << "Non ci sono Indici validi nella Lista!"<< std::endl;
        return -1;
    }
    
    int index = -1;

    while (true)
    {
        std::cout << request << std::endl;

        std::cin >> index;

        if (std::cin.fail())
        {
            std::cout << "Non e' stato inserito un numero!" << std::endl;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue;
        }

        if (index < 0 || index >= (int)maxSize)
        {
            std::cout << "L'indice inserito non e' presente!" << std::endl;

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return index;
    }
}

/* ----------------------------
   DEBUG and SERIALIZATION
   ---------------------------- */
