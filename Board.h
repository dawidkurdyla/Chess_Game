/*-------------------------------------------------------------------------------------------
		Ten plik jest cz�ci� projektu z przedmiotu J�zyki programowania obiektowego
-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------
		Plik zawiera deklaracj� obiektu board, s�u��cej do wy�wietlenia grafiki planszy gry
-------------------------------------------------------------------------------------------*/
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


class Board : public sf::Drawable
{
public:

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

	void SetTexture(std::string filepath);

protected:
	sf::Texture m_texture;
	sf::Sprite m_board;

};

