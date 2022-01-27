/*-------------------------------------------------------------------------------------------
		Ten plik jest czêœci¹ projektu z przedmiotu Jêzyki programowania obiektowego
-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------
		Plik zawiera definicje funkcji klasy GameEngine
-------------------------------------------------------------------------------------------*/


#include "GameEngine.h"
#include <iostream>
#include <fstream>

void GameEngine::Move(Figure* figure, Figure::MoveInfo move, Figure* arena[8][8])
{
	switch (move.Type)
	{
	case Figure::Move_Type::NONE:

		GameEngine::None(figure, move, arena);
		break;

	case Figure::Move_Type::NORMAL:

		GameEngine::Normal(figure, move, arena);
		break;

	case Figure::Move_Type::EXCHANGE:

		GameEngine::Exchange(figure, move, arena);
		break;

	}

}
void GameEngine::None(Figure* figure, Figure::MoveInfo move, Figure* arena[8][8])
{
	//Wprowadzenie nowej pozycji do figury
	figure->set_Pos({ move.X, move.Y });

	//Sygnalizacja ¿e ruch zosta³ zakoñczony
	figure->isMoving = false;
}

void GameEngine::Normal(Figure* figure, Figure::MoveInfo move, Figure* arena[8][8])
{
	//Zapis stanu gry sprzed ruchu -> do cofania ruchu
	setArenaBackup(arena);

	//Wyczyszczenie starej pozycji przesuniêtej figury
	arena[figure->get_Pos().X][figure->get_Pos().Y] = nullptr;

	//Wprowadzenie figury na now¹ pozycjê wskazan¹ ruchem 
	arena[move.X][move.Y] = figure;

	//Wprowadzenie nowej pozycji do figury
	figure->set_Pos({ move.X, move.Y });

	//Sygnalizacja ¿e ruch zosta³ zakoñczony
	figure->isMoving = false;

	//Kopia informacji o 1 ruchu figury -> do cofania ruchu
	figure->set_firstMoveCopy(figure->get_firstMove());

	//Sygnalizacja ¿e figura wykona³a swój 1 ruch
	if (figure->get_firstMove() == true)
		figure->set_firstMove(false);

	//Ruch zosta³ wykonany
	figure->MoveIsDone = true;
}

void GameEngine::Exchange(Figure* figure, Figure::MoveInfo move, Figure* arena[8][8])
{
	Figure* clicked = nullptr;

	//Utworzenie figur do wymiany na podstawie piona który jest wymieniany
	m_exchangableFigures[0] = new Queen(figure->get_Team(), { 0 ,3 });
	m_exchangableFigures[1] = new Bishop(figure->get_Team(), { 2, 3 });
	m_exchangableFigures[2] = new Rook(figure->get_Team(), { 4, 3 });
	m_exchangableFigures[3] = new Knight(figure->get_Team(), { 6, 3 });

	sf::RectangleShape exchangeMenu(sf::Vector2f{ 800, 800 });
	exchangeMenu.setFillColor(sf::Color{ 25, 25, 25, 150 });


	Window.draw(exchangeMenu);

	for (auto& figure : m_exchangableFigures)
	{
		figure->set_scale(2);
		Window.draw(*figure);
	}

	Window.display();

	while (clicked == nullptr)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(Window);


		while (Window.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed) {
				Window.close();
				break;
			}
			else if (Event.type == sf::Event::MouseButtonPressed)
				clicked = m_exchangableFigures[mousePos.x / int(SCREEN_WIDTH / 4)];
		}

	}

	clicked->set_scale(1);
	//Zapis stanu gry sprzed ruchu -> do cofania ruchu
	setArenaBackup(arena);

	//Wyczyszczenie starej pozycji przesuniêtej figury
	arena[figure->get_Pos().X][figure->get_Pos().Y] = nullptr;

	//Ustawienie nowej pozycji figury przez wymian¹
	figure->set_Pos({ move.X, move.Y });

	//Wprowadzenie wybranej figury na now¹ pozycjê wskazan¹ ruchem 
	arena[move.X][move.Y] = clicked;

	//Wprowadzenie pozycji do wybranej figury
	clicked->set_Pos({ move.X, move.Y });

	//Sygnalizacja ¿e ruch zosta³ zakoñczony
	figure->isMoving = false;

	//Ruch zosta³ wykonany
	figure->MoveIsDone = true;
}


void GameEngine::UndoMove(Figure* clicked)
{
	setArena(arenaBackup);
	clicked->set_Pos(clicked->get_oldPos());
	clicked->set_firstMove(clicked->get_firstMoveCopy());
	clicked->MoveIsDone = false;
	SwitchTurn();
	allPossibleMoves();
}

void GameEngine::RenderAll(Figure* clicked, sf::Vector2i mousePos)
{
	Window.clear();
	Window.draw(board);

	if (clicked != nullptr && clicked->isMoving)
	{
		clicked->set_SpritePos({ mousePos.x - SCREEN_WIDTH / 16 , mousePos.y - SCREEN_HEIGHT / 16 });
		RenderPossibleMoves(Window, clicked);
	}
	else if (clicked != nullptr && clicked->MoveIsDone)
	{
		RenderLastMove(Window, clicked);
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (arena[i][j] != nullptr)
			{
				if (arena[i][j]->get_Type() == Figure::Piece_Type::KING)
				{
					RednerCheckAlert(Window, reinterpret_cast <King*> (arena[i][j]));
				}
				Window.draw(*arena[i][j]);
			}
		}
	}
	Window.display();
}

void GameEngine::RenderPossibleMoves(sf::RenderTarget& target, Figure* figure)
{
	for (auto PossibleMove : figure->get_PossibleMoves())
	{
		sf::RectangleShape rectangle(sf::Vector2f{ 100, 100 });
		rectangle.setFillColor(sf::Color{ 0, 150, 255, 100 });
		rectangle.setPosition(PossibleMove.X * 100, PossibleMove.Y * 100);
		target.draw(rectangle);
	}
}

void GameEngine::RednerCheckAlert(sf::RenderTarget& target, King* king)
{
	if (king->get_check())
	{
		sf::RectangleShape rectangle(sf::Vector2f{ 100, 100 });
		rectangle.setFillColor(sf::Color{ 255, 0, 0, 100 });
		rectangle.setPosition(king->get_Pos().X * 100, king->get_Pos().Y * 100);
		target.draw(rectangle);
	}

}

void GameEngine::RenderLastMove(sf::RenderTarget& target, Figure* Figure)
{
	sf::RectangleShape rectangle1(sf::Vector2f{ 100, 100 });
	sf::RectangleShape rectangle2(sf::Vector2f{ 100, 100 });
	rectangle1.setFillColor(sf::Color{ 0, 200, 0, 70 });
	rectangle2.setFillColor(sf::Color{ 0, 200, 0, 70 });
	rectangle1.setPosition(Figure->get_oldPos().X * 100, Figure->get_oldPos().Y * 100);
	rectangle2.setPosition(Figure->get_Pos().X * 100, Figure->get_Pos().Y * 100);
	target.draw(rectangle1);
	target.draw(rectangle2);
}
void GameEngine::SwitchTurn()
{
	if (m_turn == Figure::Team::WHITE)
		m_turn = Figure::Team::BLACK;

	else
		m_turn = Figure::Team::WHITE;
}

void GameEngine::setArenaBackup(Figure* arena[8][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			arenaBackup[i][j] = arena[i][j];
		}

	}
}

void GameEngine::setArena(Figure* arenaBackup[8][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			arena[i][j] = arenaBackup[i][j];
		}

	}
}


void GameEngine::allPossibleMoves()
{

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (arena[i][j] != nullptr)
			{
				arena[i][j]->clearPossibleMoves();
				arena[i][j]->calculatePossibleMoves(arena, true);
			}
		}
	}
}

void GameEngine::ResultScreen(std::string result)
{
	sf::RectangleShape exchangeMenu(sf::Vector2f{ 800, 800 });
	exchangeMenu.setFillColor(sf::Color{ 25, 25, 25, 150 });

	sf::Text Result;
	sf::Font font;

	font.loadFromFile("font/PlayfairDisplay-Bold.ttf");
	Result.setFont(font);
	Result.setFillColor(sf::Color::White);
	Result.setString(result);
	Result.setCharacterSize(70);
	Result.setPosition(190, 350);

	Window.draw(exchangeMenu);
	Window.draw(Result);
	Window.display();

	while (Event.key.code != sf::Keyboard::Escape)
	{
		while (Window.pollEvent(Event))
		{
			if (Event.key.code == sf::Keyboard::Escape)
				break;
		}
	}
}

void GameEngine::CheckGameState()
{

	Figure::Team teamToCheck{};

	bool noMovesLeft = true;

	//Który król ma byæ sprawdzany po wykonanym ruchu zale¿y od tury
	if (m_turn == Figure::Team::WHITE)
		teamToCheck = Figure::Team::BLACK;
	else
		teamToCheck = Figure::Team::WHITE;

	//Jeœli którakolwiek z figur badanego zespo³u ma ruch do wykonania, 
	//noMovesLeft = false -> gra wci¹¿ trwa 
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (arena[i][j] != nullptr)
			{
				if (arena[i][j]->get_Team() == teamToCheck)
				{
					if (arena[i][j]->get_PossibleMoves().size() > 0)
					{
						noMovesLeft = false;
						break;
					}
				}
			}
		}
	}

	//Wyznaczenie wyniku/stanu gry
	//
	//Sprawdzenie zzy badanej dru¿ynie zosta³y jakieœ ruchy do wykonania
	//Jeœli noMovesLeft = False to dru¿yna ma ruchy, jeœli True, to w zale¿noœci od wartoœci szacha
	//jest remis albo przegrana badanego zespo³u
	if (noMovesLeft && getKing(teamToCheck)->get_check())
	{
		if (teamToCheck == Figure::Team::WHITE)
		{
			ResultScreen("BLACK WON");
		}
		else
		{
			ResultScreen("WHITE WON");
		}
	}
	//Jeœli brak mo¿liwych ruchów a król nie jest szachowany -> Pat/Remis
	else if (noMovesLeft && !getKing(teamToCheck)->get_check())
	{
		ResultScreen("DRAW");
	}

}

King* GameEngine::getKing(Figure::Team team)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (arena[i][j] != nullptr && arena[i][j]->get_Type() == Figure::Piece_Type::KING)
			{
				if (arena[i][j]->get_Team() == team)
					return reinterpret_cast <King*> (arena[i][j]);
			}
		}
	}
}



//Konstruktor inicjuj¹cy wszystkie figury i umieszczaj¹ct je na plaszny
//
GameEngine::GameEngine() : m_turn(Figure::Team::WHITE)
{

	//Za³adowanie textury planszy
	board.SetTexture("images/Board_800x800.jpg");

	//Inicializacja oraz umiejscowienie ka¿dej figury na odpowiadaj¹cym jej miejscu startowym
	//Pozycja 0.0 znajduje siê w lewym górnym rogu okna

	for (int i = 0; i < 8; i++)
	{
		arena[i][1] = new Pawn(Figure::Team::BLACK, { i,1 });
		arena[i][6] = new Pawn(Figure::Team::WHITE, { i,6 });
	}

	arena[1][7] = new Knight(Figure::Team::WHITE, { 1,7 });
	arena[6][7] = new Knight(Figure::Team::WHITE, { 6,7 });
	arena[1][0] = new Knight(Figure::Team::BLACK, { 1,0 });
	arena[6][0] = new Knight(Figure::Team::BLACK, { 6,0 });

	arena[2][0] = new Bishop(Figure::Team::BLACK, { 2,0 });
	arena[5][0] = new Bishop(Figure::Team::BLACK, { 5,0 });
	arena[2][7] = new Bishop(Figure::Team::WHITE, { 2,7 });
	arena[5][7] = new Bishop(Figure::Team::WHITE, { 5,7 });

	arena[0][0] = new Rook(Figure::Team::BLACK, { 0,0 });
	arena[7][0] = new Rook(Figure::Team::BLACK, { 7,0 });
	arena[0][7] = new Rook(Figure::Team::WHITE, { 0,7 });
	arena[7][7] = new Rook(Figure::Team::WHITE, { 7,7 });

	arena[3][7] = new Queen(Figure::Team::WHITE, { 3,7 });
	arena[3][0] = new Queen(Figure::Team::BLACK, { 3,0 });

	arena[4][7] = new King(Figure::Team::WHITE, { 4,7 });
	arena[4][0] = new King(Figure::Team::BLACK, { 4,0 });

	//Wype³nienie reszty planszy pustymi wskaŸnikami 
	for (int i = 0; i < 8; i++)
	{
		for (int j = 2; j < 6; j++)
		{
			arena[i][j] = nullptr;
		}
	}


	//Inicializacja kopii areny pustymi wskaŸnikami 
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			arenaBackup[i][j] = nullptr;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		m_exchangableFigures[i] = nullptr;
	}
}

GameEngine::~GameEngine()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			delete arena[i][j];
		}
	}
}