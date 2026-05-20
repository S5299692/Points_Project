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
    /// @brief Print the List of Shapes currently present in @p shapes.
    /// @return 0 when empty 1 when populated
    void printPolygonList();

    void printPolygonListIdex();

    /// @brief Modify a Polygon present in the @p shapes list.
    void modifyPolygon();

    /// @brief Move a Polygon inside the bounding box.
    void movePolygon();

    /// @brief Create a new Polygon inside the bounding box.
    void newPolygon();

    /// @brief Delete a Polygon in @p shapes.
    void deletePolygon();

    /// @brief Delete All the Polygon in @p shapes.
    void deleteAllPolygon();  
    /// @}

    /// @name GETTERS / SETTERS
    /// @{
    
    /// @brief Get the max dimension of @p shapes . 
    /// @return an integer that is the max dimension of @p shapes .
    int getShapesSize();

    /// @brief Get the list of Polygon of @p shapes .
    /// @return 0 when empty and 1 when populated.
    int getPolygonList();

    int getValidIndex(size_t maxSize, const char* request);
   /// @}


    /// @name DEBUG and SERIALIZATION
    /// @{
    
    /// @}

};

#endif