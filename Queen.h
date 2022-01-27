/*-------------------------------------------------------------------------------------------
		Ten plik jest czêœci¹ projektu z przedmiotu Jêzyki programowania obiektowego
-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------
		Plik zawiera deklaracjê klasy Queen, dziedzicz¹cej po Figure
-------------------------------------------------------------------------------------------*/

#pragma once
#include "Figure.h"
#include <array>

class Queen : public Figure
{
public:
	Queen(Team team, Position pos);

	void calculatePossibleMoves(Figure* arena[8][8], bool testCheck);
};