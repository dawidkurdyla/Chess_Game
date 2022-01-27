/*-------------------------------------------------------------------------------------------
		Ten plik jest cz�ci� projektu z przedmiotu J�zyki programowania obiektowego
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
					//W celu poprawy wydajno�ci, szach od Kr�la i Piona liczony jest bez funkcji CallPossibleMoves()
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
							//Je�li pozycja mo�liwego ruchu, r�wna si� pozycji kr�la -> szach
							if (move.X == KingPos.X && move.Y == KingPos.Y)
							{
								check = true;
							}
						}
						//Przywr�cenie listy mo�liwych ruch�w danej figury przed symulacj� ruchu
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

	//Tablica ze wszystkimi mo�liwymi ruchami i typem ruchu
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

	//Iteracja po tablicy ruch�w
	for (auto& move : possibleJump)
	{
		//Ograniczanie ruch�w poza plansze
		if ((m_pos.X + move.X >= 0) && (m_pos.X + move.X <= 7) && (m_pos.Y + move.Y >= 0) && (m_pos.Y + move.Y <= 7))
		{
			//Wykrywanie ruch�w na zaj�te miejsce 
			if (arena[m_pos.X + move.X][m_pos.Y + move.Y] != nullptr)
			{
				//Atak na przeciwnika
				if (arena[m_pos.X + move.X][m_pos.Y + move.Y]->get_Team() != m_team)
				{
					possibleMoves = acceptMove(possibleMoves, { m_pos.X + move.X, m_pos.Y + move.Y, Figure::Move_Type::NORMAL }, arena, findMyKing(arena), testCheck);
				}
			}
			//Je�li pozycja nie jest zaj�ta normalny ruch
			else
			{
				possibleMoves = acceptMove(possibleMoves, { m_pos.X + move.X, m_pos.Y + move.Y, Figure::Move_Type::NORMAL }, arena, findMyKing(arena), testCheck);
			}
		}
	}

	m_PossibleMoves = possibleMoves;
}

//Ustawienie zmiennej sygnalizuj�cej o istnieniu szacha
void King::set_check(bool check) { m_check = check; }

