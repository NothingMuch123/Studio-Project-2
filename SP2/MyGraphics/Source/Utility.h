/******************************************************************************/
/*!
\file	Utility.h
\author Team 8
\par	
\brief
Header file for Utility 
*/
/******************************************************************************/
#ifndef UTILITY_H
#define UTILITY_H

#include "Vertex.h"
#include "Mtx44.h"

Position operator*(const Mtx44& lhs, const Position& rhs);

#endif