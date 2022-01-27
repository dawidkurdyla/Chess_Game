/*-------------------------------------------------------------------------------------------
		Ten plik jest czêœci¹ projektu z przedmiotu Jêzyki programowania obiektowego
-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------
		Plik zawiera deklaracjê obiektu board, s³u¿¹cej do wyœwietlenia grafiki planszy gry
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

