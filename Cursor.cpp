//
// Created by Tiffanie Lim on 11/4/24.
//

#include "Cursor.h"

Cursor::Cursor(unsigned int size)
        : cursor(sf::Vector2f(2.f, static_cast<float>(size))), blinkTime(sf::Time::Zero), visible(true), position(0)
{
    cursor.setFillColor(sf::Color::Black);
}

void Cursor::update(sf::Time deltaTime)
{
    blinkTime += deltaTime;
    if (blinkTime >= sf::seconds(0.5f))
    {
        visible = !visible;
        blinkTime = sf::Time::Zero;
    }
}

void Cursor::render(sf::RenderWindow& window)
{
    if (visible)
        window.draw(cursor);
}

void Cursor::updatePosition(const sf::Text& text)
{
    sf::Vector2f position = text.findCharacterPos(this->position);
    cursor.setPosition(position.x + 2, position.y);
}

unsigned int Cursor::getPosition() const
{
    return position;
}

void Cursor::moveLeft()
{
    if (position > 0)
        position--;
}

void Cursor::moveRight()
{
    position++;
}

void Cursor::setPosition(unsigned int pos)
{
    position = pos;
}

