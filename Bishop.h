/*-------------------------------------------------------------------------------------------
		Ten plik jest cz�ci� projektu z przedmiotu J�zyki programowania obiektowego
-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------
		Plik zawiera deklaracj� klasy Bishop, dziedzicz�cej po Figure
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

