//
// Created by Tiffanie Lim on 11/5/24.
//

#include "TextInput.h"

TextInput::TextInput(float width, float height, float x, float y)
        : box(sf::Vector2f(width, height)), maxLength(100), isActive(false),
          cursor(text.getCharacterSize())
{
    text.setFont(Font::getFont("futura"));
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x + 5.f, y + 5.f);

    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(2.f);
    box.setPosition(x, y);

}

void TextInput::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::TextEntered)
    {
        if (isActive)
            processInput(event.text.unicode);
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (box.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
            isActive = true;
        else
            isActive = false;
    }
    if (event.type == sf::Event::KeyPressed)
    {
        if ((event.key.control || event.key.system) && event.key.code == sf::Keyboard::Z)
            undo();
    }
}

void TextInput::update(sf::Time deltaTime)
{
    cursor.update(deltaTime);
}

void TextInput::render(sf::RenderWindow& window)
{
    window.draw(box);
    window.draw(text);
    if (isActive)
    {
        cursor.render(window);
    }
}

void TextInput::processInput(sf::Uint32 unicode)
{
    if (unicode == '\b')
        deleteCharacter();
    else if (unicode < 128 && content.length() < maxLength)
    {
        backspace.saveState(content);
        content.insert(content.begin() + cursor.getPosition(), static_cast<char>(unicode));
        text.setString(content);
        cursor.moveRight();
        cursor.updatePosition(text);
    }
}

void TextInput::deleteCharacter()
{
    unsigned int cursorPos = cursor.getPosition();
    if (!content.empty() && cursorPos > 0)
    {
        backspace.saveState(content);
        content.erase(cursorPos - 1, 1);
        cursor.moveLeft();
        text.setString(content);
        cursor.updatePosition(text);
    }
}

void TextInput::undo()
{
    std::string previousState = backspace.undo();
    if (!previousState.empty())
    {
        content = previousState;
        text.setString(content);
        cursor.setPosition(content.size());
        cursor.updatePosition(text);
    }
}

std::string TextInput::getText() const
{
    return content;
}

void TextInput::clear()
{
    content.clear();
    text.setString("");
    cursor.setPosition(0);
    cursor.updatePosition(text);
}

sf::FloatRect TextInput::getBounds() const
{
    return box.getGlobalBounds();
}