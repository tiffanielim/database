//
// Created by Tiffanie Lim on 11/26/24.
//

#ifndef CS8_DATABASE_CELL_H
#define CS8_DATABASE_CELL_H
#include <SFML/Graphics.hpp>
#include "Font.h"

class Cell {
private:
    sf::Text _text;
    sf::RectangleShape _cell;
    Font fontManager;
    std::string _value;
    void centerText();

public:
    Cell();
    void setText(const std::string &text);
    std::string getText() const;
    std::string getValue() const;
    void setValue(const std::string &value);
    void setPosition(float x, float y);
    void setSize(float width, float height);
    void draw(sf::RenderTarget &target) const;
    void setOutlineColor(const sf::Color& color);
    void setOutlineThickness(float thickness);
    void setFillColor(const sf::Color &color);
    sf::FloatRect getGlobalBounds() const;
};

#endif //CS8_DATABASE_CELL_H
