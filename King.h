/*-------------------------------------------------------------------------------------------
		Ten plik jest cz�ci� projektu z przedmiotu J�zyki programowania obiektowego
-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------
		Plik zawiera deklaracj� klasy King, dziedzicz�cej po Figure
-------------------------------------------------------------------------------------------*/

#pragma once
#include "Figure.h"
#include "Pawn.h"
#include <array>

class King : public Figure
{
public:
	King(Team team, Position pos);

	King(const King& king);

	void calculatePossibleMoves(Figure* arena[8][8], bool testCheck);

	//Funkcja sprawdzj�ca szacha, na podstawie podanej pozycji badanego kr�la
	void tryCheck(Figure* arena[8][8], Position pos);

	void set_check(bool check);

	bool get_check() const { return m_check; }
private:

	//True, je�li kt�l znajduje si� na polu obj�ty w "PossibleMoves" kt�rejkolwiek z figur
	bool m_check;
};

