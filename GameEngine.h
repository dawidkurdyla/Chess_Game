/*---------------------------------------------------------------------------------------------------
		Ten plik jest czêœci¹ projektu z przedmiotu Jêzyki programowania obiektowego
---------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------
		Plik zawiera deklaracjê klasy GameEngine
		Klasa obs³uguje ca³¹ mechanikê programu, oraz zarz¹dza wyœwietlaniem wszystkiego na ekranie przy pomocy biblioteki SFML
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

	//Obiekt klasy Event z biblioteki SFML obs³uguj¹cu zdarzenia jak nacisniêcie myszy 
	sf::Event Event;

	Board board;

	//Macierz pozycjonuj¹ca wszystkie figury na planszy do gry
	Figure* arena[8][8];

	//Kopia planszy do cofania ruchu 
	Figure* arenaBackup[8][8];

	//Konstruktor
	GameEngine();

	//Destruktor
	~GameEngine();

	//Funkcja wykonywuj¹ca ruch
	void Move(Figure* figure, Figure::MoveInfo move, Figure* arena[8][8]);

	//Funkcja przestawiaj¹ca turê
	void SwitchTurn();

	//Funkcja cofaj¹ca wykonany ruch (maksymalnie 1 ostatni)
	void UndoMove(Figure* clicked);

	//Funkcja kontroluj¹ca stan gry, szachy danych królów, zwyciêstwo jednej ze stron, remis itd
	void CheckGameState();

	//Funkcja zapisuj¹ca stan planszy przed wykonaniem ruchu
	void setArenaBackup(Figure* arena[8][8]);

	void setArena(Figure* arenaBackup[8][8]);

	Figure::Team getTurn() const { return m_turn; }

	//Funkcja obliczaj¹ca wszystkie mo¿liwe ruchy dla ka¿dej figury na planszy
	void allPossibleMoves();

	//Funkcja wyœwietlaj¹ca wszystko co oczekuje do wyrenderowania na ekranie
	void RenderAll(Figure* clicked, sf::Vector2i mousePos);

	//Funkcja renderuj¹ca wszystkie mo¿liwe ruchy dla naciœniêtej figury
	void RenderPossibleMoves(sf::RenderTarget& target, Figure* Figure);

	//Funkcja renderuj¹ca czerwony kwadrat wokó³ szachowanego króla
	void RednerCheckAlert(sf::RenderTarget& target, King* king);

	//Funkcja renderuj¹ca ostatni wykonany ruch
	void RenderLastMove(sf::RenderTarget& target, Figure* Figure);

private:

	//Funkcja zwracaj¹cego króla danej dru¿yny
	King* getKing(Figure::Team team);

	//Funkcja wykonuj¹ca ruch typu NONE -> "pusty" ruch, cofniêcie piona na swoj¹ pozycjê
	void None(Figure* figure, Figure::MoveInfo move, Figure* arena[8][8]);

	//Funkcja wykonuj¹ca tradycjny ruch
	void Normal(Figure* figure, Figure::MoveInfo move, Figure* arena[8][8]);

	//Funkcja wykonuj¹ca wymianê piona na wybran¹ figurê po dojœciu do krawêdzi panszy
	void Exchange(Figure* figure, Figure::MoveInfo move, Figure* arena[8][8]);

	//Ekran z rezultatem gry
	void ResultScreen(std::string result);

	//Zmienna zawieraj¹ca informajcê która strona wykonuje ruch
	Figure::Team m_turn;

	//Tabica figur do wymiany przez piona
	Figure* m_exchangableFigures[4];
};

