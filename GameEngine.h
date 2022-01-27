/*---------------------------------------------------------------------------------------------------
		Ten plik jest cz�ci� projektu z przedmiotu J�zyki programowania obiektowego
---------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------
		Plik zawiera deklaracj� klasy GameEngine
		Klasa obs�uguje ca�� mechanik� programu, oraz zarz�dza wy�wietlaniem wszystkiego na ekranie przy pomocy biblioteki SFML
---------------------------------------------------------------------------------------------------*/
#pragma once
#include "Figure.h"
#include "Board.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"
#include "Pawn.h"
#include "Board.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class GameEngine
{
public:

	//Rozmiary ekranu
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 800;

	//Obiekt okna gry
	sf::RenderWindow Window{ sf::VideoMode{unsigned(SCREEN_WIDTH),unsigned(SCREEN_HEIGHT)}, "Chess" };

	//Obiekt klasy Event z biblioteki SFML obs�uguj�cu zdarzenia jak nacisni�cie myszy 
	sf::Event Event;

	Board board;

	//Macierz pozycjonuj�ca wszystkie figury na planszy do gry
	Figure* arena[8][8];

	//Kopia planszy do cofania ruchu 
	Figure* arenaBackup[8][8];

	//Konstruktor
	GameEngine();

	//Destruktor
	~GameEngine();

	//Funkcja wykonywuj�ca ruch
	void Move(Figure* figure, Figure::MoveInfo move, Figure* arena[8][8]);

	//Funkcja przestawiaj�ca tur�
	void SwitchTurn();

	//Funkcja cofaj�ca wykonany ruch (maksymalnie 1 ostatni)
	void UndoMove(Figure* clicked);

	//Funkcja kontroluj�ca stan gry, szachy danych kr�l�w, zwyci�stwo jednej ze stron, remis itd
	void CheckGameState();

	//Funkcja zapisuj�ca stan planszy przed wykonaniem ruchu
	void setArenaBackup(Figure* arena[8][8]);

	void setArena(Figure* arenaBackup[8][8]);

	Figure::Team getTurn() const { return m_turn; }

	//Funkcja obliczaj�ca wszystkie mo�liwe ruchy dla ka�dej figury na planszy
	void allPossibleMoves();

	//Funkcja wy�wietlaj�ca wszystko co oczekuje do wyrenderowania na ekranie
	void RenderAll(Figure* clicked, sf::Vector2i mousePos);

	//Funkcja renderuj�ca wszystkie mo�liwe ruchy dla naci�ni�tej figury
	void RenderPossibleMoves(sf::RenderTarget& target, Figure* Figure);

	//Funkcja renderuj�ca czerwony kwadrat wok� szachowanego kr�la
	void RednerCheckAlert(sf::RenderTarget& target, King* king);

	//Funkcja renderuj�ca ostatni wykonany ruch
	void RenderLastMove(sf::RenderTarget& target, Figure* Figure);

private:

	//Funkcja zwracaj�cego kr�la danej dru�yny
	King* getKing(Figure::Team team);

	//Funkcja wykonuj�ca ruch typu NONE -> "pusty" ruch, cofni�cie piona na swoj� pozycj�
	void None(Figure* figure, Figure::MoveInfo move, Figure* arena[8][8]);

	//Funkcja wykonuj�ca tradycjny ruch
	void Normal(Figure* figure, Figure::MoveInfo move, Figure* arena[8][8]);

	//Funkcja wykonuj�ca wymian� piona na wybran� figur� po doj�ciu do kraw�dzi panszy
	void Exchange(Figure* figure, Figure::MoveInfo move, Figure* arena[8][8]);

	//Ekran z rezultatem gry
	void ResultScreen(std::string result);

	//Zmienna zawieraj�ca informajc� kt�ra strona wykonuje ruch
	Figure::Team m_turn;

	//Tabica figur do wymiany przez piona
	Figure* m_exchangableFigures[4];
};

