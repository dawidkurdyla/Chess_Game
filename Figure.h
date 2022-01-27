/*-------------------------------------------------------------------------------------------
		Ten plik jest cz�ci� projektu z przedmiotu J�zyki programowania obiektowego
-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------
		Plik zawiera deklaracj� klasy macierzystej Figure:
		Klasa ta zawiera pola i metody wsp�lne dla wszystkich figur
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

	//Struktury okre�laj�ce po�o�enie figur oraz dopuszczalnych ruch�w oraz jego typu
	struct Position
	{
		int X, Y;
	};

	//Struktura okre�laj�ca wykonany ruch, jego pozycj� oraz Typ
	struct MoveInfo
	{
		int X, Y;
		enum class Figure::Move_Type Type;
	};

	//Zmienna zawieraj�ca informacj� czy figura jest w trakcie poruszania si� "1" czy nie "0"
	bool isMoving;

	//Informacja czy ruch zosta� zako�czony
	bool MoveIsDone;

	//Konstruktor
	Figure(Team team, Position pos, Piece_Type type);

	//Konstruktor Kopiuj�cy
	Figure(const Figure& figure);

	//Destruktor
	~Figure() = default;

	//////////////////////////////////////////////////////////////////////////////////
	// Settery oraz gettery potrzebnych p�l 
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

	//Sprawdzenie czy dany ruch znajduje si� w li�cie dozwolonych ruch�w danej figury
	//Oraz wprowadzenie tego ruchu do zmiennej przechowuj�cej aktualnie wykonywany ruch
	bool moveIsPossible(Position MovePos);

	//Wyczysczenie tablicy mo�liwych ruch�w danej figury
	void clearPossibleMoves();

	//Ustawienie sklai wy�wietlanej figury
	void set_scale(int scale);

	//Przeci��ona funkcja z biblioteki SFML pozwalaj�ca na rysowanie obiekt�w na ekranie
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

	//Funkcja obliczaj�ca wszystkie mo�liwe do wykonania ruchy przez dan� figur�
	virtual void calculatePossibleMoves(Figure* arena[8][8], bool testCheck) = 0;

protected:

	//Obiekt zawieraj�cy tekstur� danej figury
	sf::Texture m_texture;

	//Obiekt rysowalny danej figury
	sf::Sprite m_figure;

	//Zesp� do kt�rego nale�y dana figura
	Team m_team;

	//Typ figury
	Piece_Type m_type;

	//Pozycja na planszy (pozycja w macierzy figur)
	Position m_pos;

	//Zmienna przechowuj�ca poprzedni� pozycj�, wykorzystywane w cofaniu ruch�w
	Position m_oldPos;

	//Zmienna przechowuj�ca informajc� o tym czy figura wykona�a ju� sw�j 1 ruch
	bool m_firstMove;

	//Kopia firstMove, s�u�y do cofania ruchu
	bool m_firstMoveCopy;

	//Macierz mo�liwych do wykonania przez dan� figur� ruch�w
	std::vector<MoveInfo> m_PossibleMoves;

	//Aktualnie wykonywany ruch
	MoveInfo m_currentMove;

	//Funkcja zwracaj�ca obiekt kr�la w�asnej dru�yny -> wykorzystywana w acceptMove()
	King* findMyKing(Figure* arena[8][8]);


	/*Funkcja symuluj�ca wykonanie ruchu i sprawdzaj�ca mo�liwo�� jego wykonania
	* W funkcji wykonywany jest testowany ruch, poprzez przesuni�cie figury na pozycj� ruchu
	* Nast�pnie je�li po zasymulowanym ruchu kr�l koloru badanej figury nie jest szachowany,
	* ruch ten jest akceptowany i przypisywny do dozwolonych ruch�w, a nast�pnie ruch jest cofany
	* Zmienna testCheck, s�u�y do zapobiegania wpadania programu w niesko�czon� p�tl� podczas symulacji ruchu,
	* gdy jest r�wna false, (tylko przy symulacji ruchu) to szach nie jest ju� sprawdzany.
	*/
	std::vector<MoveInfo> acceptMove(std::vector<MoveInfo> possibleMoves,
		MoveInfo move,
		Figure* arena[8][8],
		King* king,
		bool testCheck);


};

