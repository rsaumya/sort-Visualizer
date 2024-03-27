#include<iostream>
#include "Menu.h"

Menu::Menu(float width, float height)
{
	if (!m_font.loadFromFile("Fonts/arial.ttf"))
	{
		std::cout << "unable to load m_menu file\n";
		exit(EXIT_FAILURE);
	}

	//ESC: back to main menu
	info.setFont(m_font);
	info.setFillColor(sf::Color(248, 240, 227, 204));
	info.setString("ESC: Back to main menu");
	info.setCharacterSize(20);
	info.setPosition(sf::Vector2f(0, height -10- info.getCharacterSize()));

	//Bubble Sort
	m_menu[0].setFont(m_font);
	m_menu[0].setFillColor(sf::Color::Red);
	m_menu[0].setString("Bubble Sort");
	m_textBounds = m_menu[0].getLocalBounds();
	m_menu[0].setOrigin(m_textBounds.width/2.0f,m_textBounds.height/2.0f);
	m_menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS+1) * 1));

	//Insertion Sort
	m_menu[1].setFont(m_font);
	m_menu[1].setFillColor(sf::Color::White);
	m_menu[1].setString("Insertion Sort");
	m_textBounds = m_menu[1].getLocalBounds();
	m_menu[1].setOrigin(m_textBounds.width / 2.0f, m_textBounds.height / 2.0f);
	m_menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS+1) * 2));

	//Selection Sort
	m_menu[2].setFont(m_font);
	m_menu[2].setFillColor(sf::Color::White);
	m_menu[2].setString("Selection Sort");
	m_textBounds = m_menu[2].getLocalBounds();
	m_menu[2].setOrigin(m_textBounds.width / 2.0f, m_textBounds.height / 2.0f);
	m_menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS+1) * 3));

	//Quick Sort
	m_menu[3].setFont(m_font);
	m_menu[3].setFillColor(sf::Color::White);
	m_menu[3].setString("Quick Sort");
	m_textBounds = m_menu[3].getLocalBounds();
	m_menu[3].setOrigin(m_textBounds.width / 2.0f, m_textBounds.height / 2.0f);
	m_menu[3].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 4));

	//Merge Sort
	m_menu[4].setFont(m_font);
	m_menu[4].setFillColor(sf::Color::White);
	m_menu[4].setString("Merge Sort");
	m_textBounds = m_menu[4].getLocalBounds();
	m_menu[4].setOrigin(m_textBounds.width / 2.0f, m_textBounds.height / 2.0f);
	m_menu[4].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 5));

	//

	//Exit
	m_menu[5].setFont(m_font);
	m_menu[5].setFillColor(sf::Color::White);
	m_menu[5].setString("Exit");
	m_textBounds = m_menu[5].getLocalBounds();
	m_menu[5].setOrigin(m_textBounds.width / 2.0f, m_textBounds.height / 2.0f);
	m_menu[5].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 6));
}

Menu::~Menu()
{

}

void Menu::draw(sf::RenderWindow& window)
{
	window.draw(info);

	for (int i = 0; i < MAX_ITEMS; i++)
	{
		window.draw(m_menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		m_menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		m_menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex +1  < MAX_ITEMS)
	{
		m_menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		m_menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}