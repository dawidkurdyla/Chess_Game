/*-------------------------------------------------------------------------------------------
		Ten plik jest cz�ci� projektu z przedmiotu J�zyki programowania obiektowego
-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------
		Plik zawiera deklaracj� klasy Rook, dziedzicz�cej po Figure
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

