/*-------------------------------------------------------------------------------------------
		Ten plik jest czêœci¹ projektu z przedmiotu Jêzyki programowania obiektowego
-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------
		Plik zawiera definicjê metod klasy Knight
-------------------------------------------------------------------------------------------*/

#include "Knight.h"

Knight::Knight(Team team, Position pos) : Figure(team, pos, Piece_Type::KNIGHT)
{
	std::string filepath;

	if (team == Team::WHITE)
		filepath = "images/W_Knight.png";

	else if (team == Team::BLACK)
		filepath = "images/B_Knight.png";

	m_texture.loadFromFile(filepath);
	m_figure.setTexture(m_texture);
	m_figure.setPosition(m_pos.X * 100, m_pos.Y * 100);
}

void Knight::calculatePossibleMoves(Figure* arena[8][8], bool testCheck)
{
	std::vector<Figure::MoveInfo> possibleMoves;

	//Tablica ze wszystkimi mo¿liwymi ruchami i typem ruchu
	std::array<MoveInfo, 8> possibleJump =
	{
		MoveInfo{-2,-1, Figure::Move_Type::NORMAL},
		MoveInfo{-2,1, Figure::Move_Type::NORMAL},
		MoveInfo{2,-1,Figure::Move_Type::NORMAL},
		MoveInfo{2, 1,Figure::Move_Type::NORMAL},
		MoveInfo{-1,-2,Figure::Move_Type::NORMAL},
		MoveInfo{-1,2,Figure::Move_Type::NORMAL},
		MoveInfo{1,-2,Figure::Move_Type::NORMAL},
		MoveInfo{1, 2,Figure::Move_Type::NORMAL},
	};

	//Iteracja po tablicy ruchów
	for (auto& move : possibleJump)
	{
		//Ograniczanie ruchów poza plansze
		if ((m_pos.X + move.X >= 0) && (m_pos.X + move.X <= 7) && (m_pos.Y + move.Y >= 0) && (m_pos.Y + move.Y <= 7))
		{
			//Wykrywanie ruchów na zajête miejsce 
			if (arena[m_pos.X + move.X][m_pos.Y + move.Y] != nullptr)
			{
				//Atak na przeciwnika
				if (arena[m_pos.X + move.X][m_pos.Y + move.Y]->get_Team() != m_team)
				{
					possibleMoves = acceptMove(possibleMoves, { m_pos.X + move.X, m_pos.Y + move.Y, Figure::Move_Type::NORMAL }, arena, findMyKing(arena), testCheck);
				}
			}
			//Jeœli pozycja nie jest zajêta normalny ruch
			else
			{
				possibleMoves = acceptMove(possibleMoves, { m_pos.X + move.X, m_pos.Y + move.Y, Figure::Move_Type::NORMAL }, arena, findMyKing(arena), testCheck);
			}

		}
	}
	m_PossibleMoves = possibleMoves;
}
