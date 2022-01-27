/*-------------------------------------------------------------------------------------------
		Ten plik jest czêœci¹ projektu z przedmiotu Jêzyki programowania obiektowego
-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------
		Plik zawiera deklaracjê klasy macierzystej Figure:
		Klasa ta zawiera pola i metody wspólne dla wszystkich figur
-------------------------------------------------------------------------------------------*/
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class King;


class Figure : public sf::Drawable
{
public:

	enum class Team { WHITE = 0, BLACK };
	enum class Piece_Type { EMPTY = 0, PAWN, ROOK, KNIGHT, BISHOP, KING, QUEEN };
	enum class Move_Type { NONE = 0, NORMAL, EXCHANGE };

	//Struktury okreœlaj¹ce po³o¿enie figur oraz dopuszczalnych ruchów oraz jego typu
	struct Position
	{
		int X, Y;
	};

	//Struktura okreœlaj¹ca wykonany ruch, jego pozycjê oraz Typ
	struct MoveInfo
	{
		int X, Y;
		enum class Figure::Move_Type Type;
	};

	//Zmienna zawieraj¹ca informacjê czy figura jest w trakcie poruszania siê "1" czy nie "0"
	bool isMoving;

	//Informacja czy ruch zosta³ zakoñczony
	bool MoveIsDone;

	//Konstruktor
	Figure(Team team, Position pos, Piece_Type type);

	//Konstruktor Kopiuj¹cy
	Figure(const Figure& figure);

	//Destruktor
	~Figure() = default;

	//////////////////////////////////////////////////////////////////////////////////
	// Settery oraz gettery potrzebnych pól 
	//
	Team get_Team(void) const { return m_team; }

	Piece_Type get_Type(void) const { return m_type; }

	Position get_Pos(void) const { return m_pos; }

	Position get_oldPos(void) const { return m_oldPos; }

	void set_Pos(Position pos);

	void set_oldPos(Position oldPos);

	void set_SpritePos(Position Pos);

	void set_firstMove(bool firstMove);

	void set_firstMoveCopy(bool firstMove);

	bool get_firstMove(void) const { return m_firstMove; }

	bool get_firstMoveCopy(void) const { return m_firstMoveCopy; }

	MoveInfo get_currentMove(void) const { return m_currentMove; }

	std::vector<MoveInfo> get_PossibleMoves() const { return m_PossibleMoves; }

	void set_PossibleMoves(std::vector<MoveInfo> PossibleMoves);

	//
	///////////////////////////////////////////////////////////////////////////////////

	//Sprawdzenie czy dany ruch znajduje siê w liœcie dozwolonych ruchów danej figury
	//Oraz wprowadzenie tego ruchu do zmiennej przechowuj¹cej aktualnie wykonywany ruch
	bool moveIsPossible(Position MovePos);

	//Wyczysczenie tablicy mo¿liwych ruchów danej figury
	void clearPossibleMoves();

	//Ustawienie sklai wyœwietlanej figury
	void set_scale(int scale);

	//Przeci¹¿ona funkcja z biblioteki SFML pozwalaj¹ca na rysowanie obiektów na ekranie
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

	//Funkcja obliczaj¹ca wszystkie mo¿liwe do wykonania ruchy przez dan¹ figurê
	virtual void calculatePossibleMoves(Figure* arena[8][8], bool testCheck) = 0;

protected:

	//Obiekt zawieraj¹cy teksturê danej figury
	sf::Texture m_texture;

	//Obiekt rysowalny danej figury
	sf::Sprite m_figure;

	//Zespó³ do którego nale¿y dana figura
	Team m_team;

	//Typ figury
	Piece_Type m_type;

	//Pozycja na planszy (pozycja w macierzy figur)
	Position m_pos;

	//Zmienna przechowuj¹ca poprzedni¹ pozycjê, wykorzystywane w cofaniu ruchów
	Position m_oldPos;

	//Zmienna przechowuj¹ca informajcê o tym czy figura wykona³a ju¿ swój 1 ruch
	bool m_firstMove;

	//Kopia firstMove, s³u¿y do cofania ruchu
	bool m_firstMoveCopy;

	//Macierz mo¿liwych do wykonania przez dan¹ figurê ruchów
	std::vector<MoveInfo> m_PossibleMoves;

	//Aktualnie wykonywany ruch
	MoveInfo m_currentMove;

	//Funkcja zwracaj¹ca obiekt króla w³asnej dru¿yny -> wykorzystywana w acceptMove()
	King* findMyKing(Figure* arena[8][8]);


	/*Funkcja symuluj¹ca wykonanie ruchu i sprawdzaj¹ca mo¿liwoœæ jego wykonania
	* W funkcji wykonywany jest testowany ruch, poprzez przesuniêcie figury na pozycjê ruchu
	* Nastêpnie jeœli po zasymulowanym ruchu król koloru badanej figury nie jest szachowany,
	* ruch ten jest akceptowany i przypisywny do dozwolonych ruchów, a nastêpnie ruch jest cofany
	* Zmienna testCheck, s³u¿y do zapobiegania wpadania programu w nieskoñczon¹ pêtlê podczas symulacji ruchu,
	* gdy jest równa false, (tylko przy symulacji ruchu) to szach nie jest ju¿ sprawdzany.
	*/
	std::vector<MoveInfo> acceptMove(std::vector<MoveInfo> possibleMoves,
		MoveInfo move,
		Figure* arena[8][8],
		King* king,
		bool testCheck);


};

