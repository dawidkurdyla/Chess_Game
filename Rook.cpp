/*-------------------------------------------------------------------------------------------
		Ten plik jest cz�ci� projektu z przedmiotu J�zyki programowania obiektowego
-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------
		Plik zawiera deklaracj� klasy Rook, dziedzicz�cej po Figure
-------------------------------------------------------------------------------------------*/


#include "Rook.h"

Rook::Rook(Team team, Position pos) : Figure(team, pos, Piece_Type::ROOK)
{
	std::string filepath;

	if (team == Team::WHITE)
		filepath = "images/W_Rook.png";

	else if (team == Team::BLACK)
		filepath = "images/B_Rook.png";

	m_texture.loadFromFile(filepath);
	m_figure.setTexture(m_texture);
	m_figure.setPosition(m_pos.X * 100, m_pos.Y * 100);

}

void Rook::calculatePossibleMoves(Figure* arena[8][8], bool testCheck)
{

	std::vector<Figure::MoveInfo> possibleMoves;

	//Tablica ze wszystkimi mo�liwymi ruchami i typem ruchu
	std::array<MoveInfo, 4> possibleJump =
	{
		MoveInfo{1,0, Figure::Move_Type::NORMAL},
		MoveInfo{-1,0, Figure::Move_Type::NORMAL},
		MoveInfo{0,-1,Figure::Move_Type::NORMAL},
		MoveInfo{0,1,Figure::Move_Type::NORMAL},
	};

	//Iteracja po tablicy ruch�w
	for (auto& move : possibleJump)
	{
		while (m_pos.X + move.X >= 0 && m_pos.X + move.X <= 7 && m_pos.Y + move.Y >= 0 && m_pos.Y + move.Y <= 7
			&& (arena[m_pos.X + move.X][m_pos.Y + move.Y] == nullptr))
		{
			possibleMoves = acceptMove(possibleMoves, { m_pos.X + move.X, m_pos.Y + move.Y, Figure::Move_Type::NORMAL }, arena, findMyKing(arena), testCheck);
			//powi�kszanie ruchu o 1 w poziomie, zal�y czy w lew� czy w praw� stron� planszy
			if (move.X < 0)
				move.X -= 1;

			else if (move.X > 0)
				move.X += 1;

			//powi�kszanie ruchu o 1 w pionie, zal�y czy w g�r� czy w d� planszy
			if (move.Y < 0)
				move.Y -= 1;

			else if (move.Y > 0)
				move.Y += 1;

		}
		//Warto�� move.X i move.Y jest r�wna lokacji gdzie znajduje si� jaka� figura
		//Je�li to figura dru�yny przeciwnej to mo�na wykona� tam ruch
		if (arena[m_pos.X + move.X][m_pos.Y + move.Y] != nullptr
			&& (m_pos.X + move.X >= 0 && m_pos.X + move.X <= 7 && m_pos.Y + move.Y >= 0 && m_pos.Y + move.Y <= 7))
		{
			if (arena[m_pos.X + move.X][m_pos.Y + move.Y]->get_Team() != m_team)
			{
				possibleMoves = acceptMove(possibleMoves, { m_pos.X + move.X, m_pos.Y + move.Y, Figure::Move_Type::NORMAL }, arena, findMyKing(arena), testCheck);
			}
		}
	}

	m_PossibleMoves = possibleMoves;
}
