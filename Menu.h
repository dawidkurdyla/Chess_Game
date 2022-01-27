/*-------------------------------------------------------------------------------------------
		Ten plik jest cz�ci� projektu z przedmiotu J�zyki programowania obiektowego
-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------
		Plik zawiera deklaracj� klasy Manu:
		Klasa s�u�y do wy�wietlenia oraz obs�ugi menu w programie
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

	//Obs�uga wydarze� na tym oknie 
	sf::Event event;

	//Okno g��wnego manu
	sf::RenderWindow window{ sf::VideoMode(SCREEN_HEIGHT, SCREEN_WIDTH), "Main Menu", sf::Style::Default };

	Menu(std::string first, std::string seckond);

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

	//Przemieszczanie si� po opcjach menu w g�r�
	void MoveUp();

	//Przemieszczanie si� po opcjach menu w d�
	void MoveDown();

	//Wyb�r danej opcji
	int get_selected() const { return m_selected; }

	//Ustawienie tekstury
	void set_texture(std::string filepath);



private:

	//Numer symbolizuj�cy wybran� opcj� z menu
	int m_selected;

	//Czcionka 
	sf::Font font;

	//Tablca tekstu do wy�wietlenia w menu
	sf::Text MenuOptions[Max_main_menu];

	//Obiekt zawieraj�cy tekstur� danej figury
	sf::Texture m_texture;

	//Obiekt rysowalny danej figury
	sf::Sprite m_background;



};

