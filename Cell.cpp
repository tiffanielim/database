//
// Created by Tiffanie Lim on 11/26/24.
//

#include "Cell.h"

Cell::Cell()
{
//    _cell.setFillColor(sf::Color(255, 209, 223));
    _cell.setFillColor(sf::Color(255, 255, 194));
    _cell.setOutlineColor(sf::Color::Black);
    _cell.setOutlineThickness(1);

    _text.setFillColor(sf::Color::Black);
    _text.setCharacterSize(15);
    sf::Font &font = fontManager.getFont("futura");
    _text.setFont(font);
}

void Cell::centerText()
{
    sf::FloatRect bounds = _text.getLocalBounds();
    _text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    _text.setPosition(
            _cell.getPosition().x + _cell.getSize().x / 2.0f,
            _cell.getPosition().y + _cell.getSize().y / 2.0f
    );
}

void Cell::setText(const std::string &text)
{
    _text.setString(text);
    centerText();
}

std::string Cell::getText() const
{
    return _text.getString();
}

void Cell::setPosition(float x, float y)
{
    _cell.setPosition(x, y);
    _text.setPosition(x + _cell.getSize().x / 2, y + _cell.getSize().y / 2);
}

void Cell::setSize(float width, float height)
{
    _cell.setSize({width, height});
}

void Cell::draw(sf::RenderTarget &target) const
{
    target.draw(_cell);
    target.draw(_text);
}

std::string Cell::getValue() const
{
    return _value;
}

void Cell::setValue(const std::string &value)
{
    _value = value;
    setText(value);
}

void Cell::setOutlineColor(const sf::Color& color)
{
    _cell.setOutlineColor(color);
}

void Cell::setOutlineThickness(float thickness)
{
    _cell.setOutlineThickness(thickness);
}

void Cell::setFillColor(const sf::Color &color) {
    _cell.setFillColor(color);
}

sf::FloatRect Cell::getGlobalBounds() const
{
    return _cell.getGlobalBounds();
}