/*-------------------------------------------------------------------------------------------
		Ten plik jest czêœci¹ projektu z przedmiotu Jêzyki programowania obiektowego
-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------
		Plik zawiera definicjê metod klasy Pawn
-------------------------------------------------------------------------------------------*/

#include "Pawn.h"
#include <iostream>

Pawn::Pawn(Team team, Position pos) : Figure(team, pos, Piece_Type::PAWN)
{
	std::string filepath;

	if (team == Team::WHITE)
		filepath = "images/W_Pawn.png";

	else if (team == Team::BLACK)
		filepath = "images/B_Pawn.png";

	m_texture.loadFromFile(filepath);
	m_figure.setTexture(m_texture);
	m_figure.setPosition(m_pos.X * 100, m_pos.Y * 100);

	//Kierunek ruchu piona zale¿y od dru¿yny
	if (team == Figure::Team::WHITE)
		m_dY = -1;
	else
		m_dY = 1;

}
Pawn::Pawn(const Pawn& pawn) : Figure(pawn), m_dY(pawn.m_dY)
{
}
void Pawn::calculatePossibleMoves(Figure* arena[8][8], bool testCheck)
{

	std::vector<Figure::MoveInfo> possibleMoves;

	int dY_copy = m_dY;

	//Dopóki pion mieœci siê w planszy oraz nie stoi przed nim inna figura
	while ((m_pos.Y + dY_copy >= 0) && (m_pos.Y + dY_copy < 8)
		&& (arena[m_pos.X][m_pos.Y + dY_copy] == nullptr)
		&& (abs(dY_copy) < 3))
	{
		if ((m_pos.Y + dY_copy >= 1) && (m_pos.Y + dY_copy <= 6))
			possibleMoves = acceptMove(possibleMoves, { m_pos.X, m_pos.Y + dY_copy, Figure::Move_Type::NORMAL }, arena, findMyKing(arena), testCheck);

		else if ((m_pos.Y + dY_copy == 0) || (m_pos.Y + dY_copy == 7))
			possibleMoves = acceptMove(possibleMoves, { m_pos.X, m_pos.Y + dY_copy, Figure::Move_Type::EXCHANGE }, arena, findMyKing(arena), testCheck);

		if (!m_firstMove)
			break;

		//Jeœli pion wykonuje swój pierwszy ruch, mo¿e poruszaæ siê o 2 pola
		else if (m_firstMove)
		{
			if (m_dY < 0)
				--dY_copy;

			else if (m_dY > 0)
				++dY_copy;
		}

	}
	//Atak piona po skosie w lew¹ stronê planszy
	if (m_pos.X - 1 >= 0)
	{
		//Wykrywanie ruchów na zajête miejsce
		if (arena[m_pos.X - 1][m_pos.Y + m_dY] != nullptr)
		{
			//Atak na przeciwnika
			if (arena[m_pos.X - 1][m_pos.Y + m_dY]->get_Team() != m_team)
			{
				possibleMoves = acceptMove(possibleMoves, { m_pos.X - 1, m_pos.Y + m_dY, Figure::Move_Type::NORMAL }, arena, findMyKing(arena), testCheck);

				if ((m_pos.Y + m_dY == 0) || (m_pos.Y + m_dY == 7))
					possibleMoves = acceptMove(possibleMoves, { m_pos.X - 1, m_pos.Y + m_dY, Figure::Move_Type::EXCHANGE }, arena, findMyKing(arena), testCheck);
			}
		}
	}

	//Atak piona po skosie w praw¹ stronê planszy
	if (m_pos.X + 1 <= 7)
	{
		//Wykrywanie ruchów na zajête miejsce
		if (arena[m_pos.X + 1][m_pos.Y + m_dY] != nullptr)
		{
			//Atak na przeciwnika
			if (arena[m_pos.X + 1][m_pos.Y + m_dY]->get_Team() != m_team)
			{
				possibleMoves = acceptMove(possibleMoves, { m_pos.X + 1, m_pos.Y + m_dY, Figure::Move_Type::NORMAL }, arena, findMyKing(arena), testCheck);

				if ((m_pos.Y + m_dY == 0) || (m_pos.Y + m_dY == 7))
					possibleMoves = acceptMove(possibleMoves, { m_pos.X + 1, m_pos.Y + m_dY, Figure::Move_Type::EXCHANGE }, arena, findMyKing(arena), testCheck);
			}
		}
	}

	m_PossibleMoves = possibleMoves;
}