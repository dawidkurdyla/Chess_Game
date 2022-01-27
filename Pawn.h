/*-------------------------------------------------------------------------------------------
		Ten plik jest cz�ci� projektu z przedmiotu J�zyki programowania obiektowego
-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------
		Plik zawiera deklaracj� klasy Pawn, dziedzicz�cej po Figure
-------------------------------------------------------------------------------------------*/

#pragma once
#include "Figure.h"
class Pawn : public Figure
{
public:
	Pawn(Team team, Position pos);

	//Konstruktor kopiuj�cy
	Pawn(const Pawn& pawn);

	void calculatePossibleMoves(Figure* arena[8][8], bool testCheck);

	//Ustawia zmienn� FirstMove na "false" co oznacza �e pion wykona� ju� ruch
	void set_FirstMove() { m_firstMove = false; }

	//Zwraca warto�� zmiennej firstMove
	bool get_FirstMove() const { return m_firstMove; }

	//Okre�la kierunek ruchu piona w zale�no�ci od zespo�u
	int m_dY;
};

