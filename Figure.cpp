/*-------------------------------------------------------------------------------------------
		Ten plik jest czêœci¹ projektu z przedmiotu Jêzyki programowania obiektowego
-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------
		Plik zawiera definicje funkcji klasy Figure
-------------------------------------------------------------------------------------------*/

#include "Figure.h"
#include "King.h"
#include <vector>




Figure::Figure(Team team, Position pos, Piece_Type type) :m_team(team), m_pos(pos), m_type(type), m_firstMove(true), m_firstMoveCopy(true),
m_oldPos(m_pos), m_currentMove({ 0,0,Figure::Move_Type::NORMAL })
{
	isMoving = false;
	MoveIsDone = false;
}

Figure::Figure(const Figure& figure)
	: m_figure(figure.m_texture), m_texture(figure.m_texture), m_team(figure.m_team), m_pos(figure.m_pos),
	isMoving(false), MoveIsDone(false), m_type(figure.m_type), m_oldPos(m_pos), m_firstMove(true), m_firstMoveCopy(true), m_currentMove({ 0,0,Figure::Move_Type::NORMAL })
{
}

void Figure::set_Pos(Position pos)
{
	m_pos = pos;
	m_figure.setPosition(m_pos.X * 100, m_pos.Y * 100);
}

void Figure::set_oldPos(Position oldPos)
{
	m_oldPos = oldPos;
}

void Figure::set_SpritePos(Position pos)
{
	m_figure.setPosition(pos.X, pos.Y);
}

void Figure::set_firstMove(bool firstMove)
{
	m_firstMove = firstMove;
}

void Figure::set_firstMoveCopy(bool firstMove)
{
	m_firstMoveCopy = firstMove;
}

void Figure::set_PossibleMoves(std::vector<MoveInfo> PossibleMoves)
{
	m_PossibleMoves = PossibleMoves;
}

void Figure::set_scale(int scale)
{
	m_figure.setScale(scale, scale);
}

King* Figure::findMyKing(Figure* arena[8][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (arena[i][j] != nullptr)
			{
				if (arena[i][j]->get_Type() == Figure::Piece_Type::KING && arena[i][j]->get_Team() == m_team)
				{
					King* result = reinterpret_cast<King*> (arena[i][j]);
					return result;
				}
			}
		}
	}
}

void Figure::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->m_figure);
}

bool Figure::moveIsPossible(Position movePos)
{
	bool result = false;
	for (auto PossibleMove : m_PossibleMoves)
	{
		if (PossibleMove.X == movePos.X && PossibleMove.Y == movePos.Y)
		{
			//Przypisanie zatwierdzonego ruchu do zmiennej przechowuj¹cej aktualny ruch
			m_currentMove = PossibleMove;
			result = true;
		}
	}
	return result;
}

void Figure::clearPossibleMoves()
{
	m_PossibleMoves.clear();
}

std::vector<Figure::MoveInfo> Figure::acceptMove(std::vector<MoveInfo> possibleMoves,
	MoveInfo move,
	Figure* arena[8][8],
	King* king,
	bool testCheck)
{
	if (!testCheck)
		possibleMoves.push_back(move);

	else if (testCheck)
	{
		//Zmienna sygnaluzuj¹ca czy miejsce wykonanego ruchu by³o zajête
		bool empty = true;

		//Obiekt przechowuj¹cy tymczasowo figurê która mog³a zajmow¹c pole ruchy
		Figure* temp = &(*arena[move.X][move.Y]);

		//Pocz¹tkowy stan szachowania 
		king->tryCheck(arena, king->get_Pos());

		//Symulacja ruchu
		//
		//Jeœli pole by³o zajmowane -> czyszczenie 
		if (arena[move.X][move.Y] != nullptr)
		{
			empty = false;
			arena[move.X][move.Y] = nullptr;

		}

		//Przesuniêcie figury o symulowany ruch (zamiana z jej aktualna lokacja)
		std::swap(arena[move.X][move.Y], arena[m_pos.X][m_pos.Y]);

		//Sprawdzenie czy po ruchu wyst¹pi szach
		//
		//Jeœli testowana figura to król, sprawdzenie szacha na "nowej" pozycji króla
		if (m_type == Piece_Type::KING)
		{
			king->tryCheck(arena, { move.X, move.Y });
		}
		else
		{
			king->tryCheck(arena, king->get_Pos());
		}

		//Przywrócenie porzedniego stanu planszy
		//
		std::swap(arena[move.X][move.Y], arena[m_pos.X][m_pos.Y]);

		if (!empty)
			arena[move.X][move.Y] = temp;

		//Jeœli po symulacji ruchu król nie by³ szachowany ruch zostaje zatwierdzony
		if (!king->get_check())
			possibleMoves.push_back(move);

		//Przywrócenie pocz¹tkowego stanu szacha
		king->tryCheck(arena, king->get_Pos());
	}
	return possibleMoves;
}