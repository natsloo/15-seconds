#include "Button.h"

Button::Button(sf::Vector2f& size, sf::Color fillC, sf::Vector2f& position, std::string& text, sf::Font& font) {
    buttonShape.setSize(size);
    buttonShape.setPosition(position);
    buttonShape.setFillColor(fillC);
    
    buttonText.setString(text);
    buttonText.setFont(font);
    buttonText.setCharacterSize(31);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setOutlineColor(sf::Color::Black);
    buttonText.setOutlineThickness(2);
    buttonText.setPosition(
        position.x + (size.x - buttonText.getLocalBounds().width) / 2 - 2,
        position.y + (size.y - buttonText.getLocalBounds().height) / 2 - 10
    );
}

//void Button::setFillColour(sf::Color c) {
//    buttonShape.setFillColor(c);
//}

void Button::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(this->buttonShape);
    target.draw(this->buttonText);
}

bool Button::isClicked(sf::Vector2f& mousePos) {
    if (buttonShape.getGlobalBounds().contains(mousePos)) {
        return true;
    }
    return false;
}
