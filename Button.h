#pragma once

#include <SFML/Graphics.hpp>

class Button : public sf::Drawable
{
	sf::RectangleShape buttonShape;
	sf::Text buttonText;
public:
	Button(sf::Vector2f& size, sf::Color fillC, sf::Vector2f& position, std::string& text, sf::Font& font);
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	bool isClicked(sf::Vector2f& mousePos);
	/*void setFillColour(sf::Color);
	void setSize()*/
};

