/*-------------------------------------------------------------------------------------------
		Ten plik jest czêœci¹ projektu z przedmiotu Jêzyki programowania obiektowego
-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------
		Plik zawiera deklaracjê klasy Rook, dziedzicz¹cej po Figure
-------------------------------------------------------------------------------------------*/


#pragma once
#include "Figure.h"
#include <array>

class Rook : public Figure
{
public:
	Rook(Team team, Position pos);

	void calculatePossibleMoves(Figure* arena[8][8], bool testCheck);
};

