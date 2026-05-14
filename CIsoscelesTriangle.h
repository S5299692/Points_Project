/*! \file CIsoscelesTriangle.h
    \brief Declaration of the class IsoscelesTriangle
    \author Paolo Gastaldo
*/

#ifndef IsoscelesTriangle_H
#define IsoscelesTriangle_H

#include "CShape.h"

/// @class IsoscelesTriangle
/// @brief to manage an object with the shape of a IsoscelesTriangle
class IsoscelesTriangle : public Shape
{
public:

    /// @name CONSTRUCTORS / DESTRUCTOR
    /// @{
    IsoscelesTriangle();
    IsoscelesTriangle(float px, float py, float w, float h);
    IsoscelesTriangle(const IsoscelesTriangle &r);

    ~IsoscelesTriangle();
    /// @}

    /// @name OPERATORS
    /// @{
    IsoscelesTriangle& operator=(const IsoscelesTriangle &r);
    bool operator==(const IsoscelesTriangle &r);
    /// @}

    /// @name BASIC HANDLING
    /// @{
    void Init();
    void Init(const IsoscelesTriangle &r);
    void Reset();
    /// @}
	
	/// @name GETTERS
    /// @{
	float GetBase();
	float GetHeight();
    float GetSide();
    
    float GetArea();
    float GetPerimeter();
    /// @}

    /// @name DEBUG and SERIALIZATION
    /// @{
    void Dump();
    /// @}
};

#endif