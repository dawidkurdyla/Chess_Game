/*-------------------------------------------------------------------------------------------
		Ten plik jest czêœci¹ projektu z przedmiotu Jêzyki programowania obiektowego
-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------
		Plik zawiera deklaracjê klasy Pawn, dziedzicz¹cej po Figure
-------------------------------------------------------------------------------------------*/

#pragma once
#include "Figure.h"
class Pawn : public Figure
{
public:
	Pawn(Team team, Position pos);

	//Konstruktor kopiuj¹cy
	Pawn(const Pawn& pawn);

	void calculatePossibleMoves(Figure* arena[8][8], bool testCheck);

	//Ustawia zmienn¹ FirstMove na "false" co oznacza ¿e pion wykona³ ju¿ ruch
	void set_FirstMove() { m_firstMove = false; }

	//Zwraca wartoœæ zmiennej firstMove
	bool get_FirstMove() const { return m_firstMove; }

	//Okreœla kierunek ruchu piona w zale¿noœci od zespo³u
	int m_dY;
};

