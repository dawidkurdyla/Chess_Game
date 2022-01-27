/*-------------------------------------------------------------------------------------------
		Ten plik jest cz�ci� projektu z przedmiotu J�zyki programowania obiektowego
-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------
		Plik zawiera p�tl� g��wn� programu, obs�uguj�c� wszystkie funkcje
-------------------------------------------------------------------------------------------*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Main_Loop.h"
#include "Figure.h"
#include "GameEngine.h"
#include "Menu.h"
#include <fstream>


void Chess::Main_Loop()
{
	//Obiekt przechowuj�cy koordynaty obliczone z wsp�rz�dnych myszki
	Figure::Position mouseCord;

	//Obiekt typu figura s�u��cy do przechowawania wska�nika na aktualnie wci�ni�t� figure
	Figure* clicked = nullptr;

	//Obiekt menu g��wnego gry
	Menu menu("Play", "Exit");

	while (menu.window.isOpen())
	{
		while (menu.window.pollEvent(menu.event))
		{

			if (menu.event.type == sf::Event::Closed)
			{
				menu.window.close();
				break;
			}
			else if (menu.event.type == sf::Event::KeyReleased)
			{
				//Je�li strza�ka w g�r�
				if (menu.event.key.code == sf::Keyboard::Up)
				{
					menu.MoveUp();
					break;
				}
				//Je�li strza�ka w d�
				else if (menu.event.key.code == sf::Keyboard::Down)
				{
					menu.MoveDown();
					break;
				}
				//Je�li enter
				if (menu.event.key.code == sf::Keyboard::Return)
				{
					if (menu.get_selected() == int(Menu::Button::Exit))
					{
						menu.window.close();
						break;
					}

					if (menu.get_selected() == int(Menu::Button::Play))
					{
						GameEngine Engine;

						Engine.allPossibleMoves();

						while (Engine.Window.isOpen())
						{
							//Pobranie pozycji kursora na ekranie
							sf::Vector2i mousePos = sf::Mouse::getPosition(Engine.Window);

							while (Engine.Window.pollEvent(Engine.Event))
							{
								//Przeliczenie pozycji kursora na wsp�rz�dne w macierzy figur
								//Zaokr�glaj�c w d� (konwersja na int) uzyskujemy odpowiednie wsp�rz�dne
								mouseCord.X = mousePos.x / int(Engine.SCREEN_WIDTH / 8);
								mouseCord.Y = mousePos.y / int(Engine.SCREEN_HEIGHT / 8);

								//Zamykanie okna przyciskiem "X"
								if (Engine.Event.type == sf::Event::Closed)
								{
									Engine.Window.close();
									break;
								}
								//Cofni�cie ostatniego wykonanego ruchu
								else if (clicked != nullptr && Engine.Event.type == sf::Event::KeyPressed)
								{
									if (Engine.Event.key.code == sf::Keyboard::BackSpace)
									{
										Engine.UndoMove(clicked);
									}
								}

								/*Escape
								else if (Engine.Event.key.code == sf::Keyboard::Escape)
								{
									Engine.Window.close();
								}*/

								//Wybranie figury do ruchu				
								else if (Engine.Event.type == sf::Event::MouseButtonPressed)
								{
									if (Engine.Event.key.code == sf::Mouse::Left)
									{
										//Sprawdzenie czy na klikni�tym polu znajduje si� figura
										//oraz czy nacisni�ta figura zgadza si� z aktualn� tur� gry
										if (Engine.arena[mouseCord.X][mouseCord.Y] != nullptr
											&& (Engine.arena[mouseCord.X][mouseCord.Y]->get_Team() == Engine.getTurn()))
										{
											clicked = Engine.arena[mouseCord.X][mouseCord.Y];
											clicked->set_oldPos(clicked->get_Pos());
											clicked->isMoving = true;
											clicked->MoveIsDone = false;
										}

									}
								}
								//Wykonanie ruchu wybran� figur�
								else if (Engine.Event.type == sf::Event::MouseButtonReleased)
								{
									if (Engine.Event.key.code == sf::Mouse::Left)
									{
										if (clicked != nullptr && clicked->isMoving)
										{
											//Sprawdzenie czy wybrany ruch jest dopuszczalny dla danej figury
											if (clicked->moveIsPossible({ mouseCord.X, mouseCord.Y }))
											{
												Engine.Move(clicked, clicked->get_currentMove(), Engine.arena);
												Engine.allPossibleMoves();
												Engine.CheckGameState();
												Engine.SwitchTurn();
											}
											//Je�li ruch jest niemo�liwy do wykonania figura wraca na swoj� poprzedni� pozycj�
											else
												Engine.Move(clicked, { clicked->get_oldPos().X,clicked->get_oldPos().Y, Figure::Move_Type::NONE }, Engine.arena);
										}
									}
								}

							}

							//Renderowanie planszy, figur, mo�liwych ruch�w, wykonanego ruchu itd
							//
							Engine.RenderAll(clicked, mousePos);
						}

					}

				}
			}
		}
		menu.window.clear();
		menu.window.draw(menu);
		menu.window.display();

	}
}