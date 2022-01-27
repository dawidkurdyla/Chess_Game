#include "Board.h"

void Board::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->m_board);
}

void Board::SetTexture(std::string filepath)
{
	m_texture.loadFromFile(filepath);
	m_board.setTexture(m_texture);
}