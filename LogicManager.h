/*! \file LogicManager.h
    \brief Declaration of the base class LogicManager
	\author Nicolò Forciniti
*/

#ifndef LM_H
#define LM_H

#include "CShape.h"
#include <vector>


/// @class LogicManager
/// @brief to manage a generic object with a LogicManager
class LogicManager
{
protected:
    std::vector<Shape*> shapes;

public:

    /// @name CONSTRUCTORS / DESTRUCTOR
    /// @{
    
    /// @brief Main constructor 
    LogicManager();

    ~LogicManager();
    /// @}


    /// @name OPERATORS
    /// @{
    LogicManager& operator=(const LogicManager &r);
    bool operator==(const LogicManager &r);
    /// @}

    /// @name BASIC HANDLING
    /// @{
    void printPolygonList();

    void modifyPolygon();
    
    void movePolygon();
    
    void newPolygon();
    
    void deletePolygon();
    
    void deleteAllPolygon();  
    
    void printPolygonListIdex();
    /// @}

    /// @name GETTERS / SETTERS
    /// @{
    int getPolygonList();
    int getValidIndex(size_t maxSize, const char* request);
   /// @}


    /// @name DEBUG and SERIALIZATION
    /// @{
    /// @}

};

#endif