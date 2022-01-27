/*-------------------------------------------------------------------------------------------
		Ten plik jest czêœci¹ projektu z przedmiotu Jêzyki programowania obiektowego
-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------
		Plik zawiera deklaracjê klasy Bishop, dziedzicz¹cej po Figure
-------------------------------------------------------------------------------------------*/


#pragma once
#include "Figure.h"
#include <array>

class Bishop : public Figure
{
public:
	Bishop(Team team, Position pos);

	void calculatePossibleMoves(Figure* arena[8][8], bool testCheck);
};

