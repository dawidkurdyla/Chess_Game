/*-------------------------------------------------------------------------------------------
		Ten plik jest czêœci¹ projektu z przedmiotu Jêzyki programowania obiektowego
-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------
		Plik zawiera definicjê metod klasy Menu
-------------------------------------------------------------------------------------------*/


#include "Menu.h"

Menu::Menu(std::string first, std::string seckond)
{
	//Za³adowanie czczionki
	font.loadFromFile("font/PlayfairDisplay-Bold.ttf");
	m_texture.loadFromFile("images/ManuBackground.png");
	m_background.setTexture(m_texture);
	m_background.setPosition(0, 0);

	//Inicializacja 3 pól w danym menu
	MenuOptions[0].setFont(font);
	MenuOptions[0].setFillColor(sf::Color::White);
	MenuOptions[0].setString(first);
	MenuOptions[0].setCharacterSize(70);
	MenuOptions[0].setPosition(200, 200);

	MenuOptions[1].setFont(font);
	MenuOptions[1].setFillColor(sf::Color::White);
	MenuOptions[1].setString(seckond);
	MenuOptions[1].setCharacterSize(70);
	MenuOptions[1].setPosition(200, 400);

	m_selected = -1;
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(m_background);

	for (int i = 0; i < Max_main_menu; i++)
		target.draw(MenuOptions[i]);

}

void Menu::MoveUp()
{
	if (m_selected >= 0)
	{
		//Ustawienie bia³ego w poprzedniej pozycji
		MenuOptions[m_selected].setFillColor(sf::Color::White);

		//Zmniejszenie m_selected, poruszanie siê w górê
		m_selected--;

		//Przejœcie na dó³ jeœli dojdziemy do max u góry
		if (m_selected == -1)
		{
			m_selected = 1;
		}

		MenuOptions[m_selected].setFillColor(sf::Color::Blue);
	}
}

void Menu::MoveDown()
{
	if (m_selected + 1 <= Max_main_menu)
	{
		MenuOptions[m_selected].setFillColor(sf::Color::White);
		m_selected++;

		if (m_selected == 2)
			m_selected = 0;

		MenuOptions[m_selected].setFillColor(sf::Color::Blue);
	}
}