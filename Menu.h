/*-------------------------------------------------------------------------------------------
		Ten plik jest czêœci¹ projektu z przedmiotu Jêzyki programowania obiektowego
-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------
		Plik zawiera deklaracjê klasy Manu:
		Klasa s³u¿y do wyœwietlenia oraz obs³ugi menu w programie
-------------------------------------------------------------------------------------------*/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define Max_main_menu 2
class Menu : public sf::Drawable
{
public:

	//Rozmiary ekranu
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 800;

	enum class Button { Play = 0, Exit, Continue, ExitToMenu };

	//Obs³uga wydarzeñ na tym oknie 
	sf::Event event;

	//Okno g³ównego manu
	sf::RenderWindow window{ sf::VideoMode(SCREEN_HEIGHT, SCREEN_WIDTH), "Main Menu", sf::Style::Default };

	Menu(std::string first, std::string seckond);

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

	//Przemieszczanie siê po opcjach menu w górê
	void MoveUp();

	//Przemieszczanie siê po opcjach menu w dó³
	void MoveDown();

	//Wybór danej opcji
	int get_selected() const { return m_selected; }

	//Ustawienie tekstury
	void set_texture(std::string filepath);



private:

	//Numer symbolizuj¹cy wybran¹ opcjê z menu
	int m_selected;

	//Czcionka 
	sf::Font font;

	//Tablca tekstu do wyœwietlenia w menu
	sf::Text MenuOptions[Max_main_menu];

	//Obiekt zawieraj¹cy teksturê danej figury
	sf::Texture m_texture;

	//Obiekt rysowalny danej figury
	sf::Sprite m_background;



};

