/*-------------------------------------------------------------------------------------------
		Ten plik jest czêœci¹ projektu z przedmiotu Jêzyki programowania obiektowego
-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------
		Plik zawiera deklaracjê klasy King, dziedzicz¹cej po Figure
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

	//Funkcja sprawdzj¹ca szacha, na podstawie podanej pozycji badanego króla
	void tryCheck(Figure* arena[8][8], Position pos);

	void set_check(bool check);

	bool get_check() const { return m_check; }
private:

	//True, jeœli któl znajduje siê na polu objêty w "PossibleMoves" którejkolwiek z figur
	bool m_check;
};

