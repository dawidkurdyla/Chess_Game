/*-------------------------------------------------------------------------------------------
		Ten plik jest czêœci¹ projektu z przedmiotu Jêzyki programowania obiektowego
-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------
		Plik zawiera definicje metod klasy King
-------------------------------------------------------------------------------------------*/


#include "King.h"
#include <iostream>

King::King(Team team, Position pos) : Figure(team, pos, Piece_Type::KING), m_check(false)
{
	std::string filepath;

	if (team == Team::WHITE)
		filepath = "images/W_King.png";

	else if (team == Team::BLACK)
		filepath = "images/B_King.png";

	m_texture.loadFromFile(filepath);
	m_figure.setTexture(m_texture);
	m_figure.setPosition(m_pos.X * 100, m_pos.Y * 100);

}

void King::tryCheck(Figure* arena[8][8], Position KingPos)
{
	bool check = false;
	std::vector<Figure::MoveInfo> PossibleMovesCopy;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (arena[i][j] != nullptr)
			{
				if (arena[i][j]->get_Team() != m_team)
				{
					//W celu poprawy wydajnoœci, szach od Króla i Piona liczony jest bez funkcji CallPossibleMoves()
					if (arena[i][j]->get_Type() == Figure::Piece_Type::KING)
					{
						if (abs(arena[i][j]->get_Pos().X - KingPos.X) <= 1 && abs(arena[i][j]->get_Pos().Y - KingPos.Y) <= 1)
						{
							check = true;
						}

					}
					else if (arena[i][j]->get_Type() == Figure::Piece_Type::PAWN)
					{

						if ((KingPos.X == arena[i][j]->get_Pos().X + 1 || KingPos.X == arena[i][j]->get_Pos().X - 1)
							&& (KingPos.Y == arena[i][j]->get_Pos().Y + (reinterpret_cast<Pawn*> (arena[i][j]))->m_dY))
						{
							check = true;
						}
					}
					else
					{
						PossibleMovesCopy = arena[i][j]->get_PossibleMoves();
						arena[i][j]->calculatePossibleMoves(arena, false);
						std::vector<MoveInfo> PossibleMove = arena[i][j]->get_PossibleMoves();
						for (const auto& move : PossibleMove)
						{
							//Jeœli pozycja mo¿liwego ruchu, równa siê pozycji króla -> szach
							if (move.X == KingPos.X && move.Y == KingPos.Y)
							{
								check = true;
							}
						}
						//Przywrócenie listy mo¿liwych ruchów danej figury przed symulacj¹ ruchu
						arena[i][j]->set_PossibleMoves(PossibleMovesCopy);
					}
				}
			}
		}
	}

	m_check = check;
}

King::King(const King& king) : Figure(king), m_check(king.m_check)
{
}

void King::calculatePossibleMoves(Figure* arena[8][8], bool testCheck)
{
	std::vector<Figure::MoveInfo> possibleMoves;

	//Tablica ze wszystkimi mo¿liwymi ruchami i typem ruchu
	std::array<MoveInfo, 8> possibleJump =
	{
		MoveInfo{0,1, Figure::Move_Type::NORMAL},
		MoveInfo{1,1, Figure::Move_Type::NORMAL},
		MoveInfo{1,0,Figure::Move_Type::NORMAL},
		MoveInfo{1,-1,Figure::Move_Type::NORMAL},
		MoveInfo{0,-1,Figure::Move_Type::NORMAL},
		MoveInfo{-1,-1,Figure::Move_Type::NORMAL},
		MoveInfo{-1,0,Figure::Move_Type::NORMAL},
		MoveInfo{-1, 1,Figure::Move_Type::NORMAL},
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

//Ustawienie zmiennej sygnalizuj¹cej o istnieniu szacha
void King::set_check(bool check) { m_check = check; }

