#pragma once

#include<SFML/Graphics.hpp>

#define MAX_ITEMS 6

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex =0;
	sf::Font m_font;
	sf::Text m_menu[MAX_ITEMS];
	sf::Text info;
	sf::FloatRect m_textBounds;
};

