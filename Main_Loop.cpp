/*-------------------------------------------------------------------------------------------
		Ten plik jest czêœci¹ projektu z przedmiotu Jêzyki programowania obiektowego
-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------
		Plik zawiera pêtlê g³ówn¹ programu, obs³uguj¹c¹ wszystkie funkcje
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
	//Obiekt przechowuj¹cy koordynaty obliczone z wspó³rzêdnych myszki
	Figure::Position mouseCord;

	//Obiekt typu figura s³u¿¹cy do przechowawania wskaŸnika na aktualnie wciœniêt¹ figure
	Figure* clicked = nullptr;

	//Obiekt menu g³ównego gry
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
				//Jeœli strza³ka w górê
				if (menu.event.key.code == sf::Keyboard::Up)
				{
					menu.MoveUp();
					break;
				}
				//Jeœli strza³ka w dó³
				else if (menu.event.key.code == sf::Keyboard::Down)
				{
					menu.MoveDown();
					break;
				}
				//Jeœli enter
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
								//Przeliczenie pozycji kursora na wspó³rzêdne w macierzy figur
								//Zaokr¹glaj¹c w dó³ (konwersja na int) uzyskujemy odpowiednie wspó³rzêdne
								mouseCord.X = mousePos.x / int(Engine.SCREEN_WIDTH / 8);
								mouseCord.Y = mousePos.y / int(Engine.SCREEN_HEIGHT / 8);

								//Zamykanie okna przyciskiem "X"
								if (Engine.Event.type == sf::Event::Closed)
								{
									Engine.Window.close();
									break;
								}
								//Cofniêcie ostatniego wykonanego ruchu
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
										//Sprawdzenie czy na klikniêtym polu znajduje siê figura
										//oraz czy nacisniêta figura zgadza siê z aktualn¹ tur¹ gry
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
								//Wykonanie ruchu wybran¹ figur¹
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
											//Jeœli ruch jest niemo¿liwy do wykonania figura wraca na swoj¹ poprzedni¹ pozycjê
											else
												Engine.Move(clicked, { clicked->get_oldPos().X,clicked->get_oldPos().Y, Figure::Move_Type::NONE }, Engine.arena);
										}
									}
								}

							}

							//Renderowanie planszy, figur, mo¿liwych ruchów, wykonanego ruchu itd
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