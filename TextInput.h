//
// Created by Tiffanie Lim on 11/5/24.
//

#ifndef AUTOCORRECT_TEXTINPUT_H
#define AUTOCORRECT_TEXTINPUT_H
#include <SFML/Graphics.hpp>
#include "Font.h"
#include "Cursor.h"
#include "Backspace.h"
#include <string>
#include <vector>

class TextInput {
private:
    sf::RectangleShape box;
    sf::Text text;
    sf::Font font;
    std::string content;
    bool isActive;
    unsigned int maxLength;
    Cursor cursor;
    Backspace backspace;

    void processInput(sf::Uint32 unicode);
    void deleteCharacter();
    void undo();
public:
    TextInput(float width, float height, float x, float y);

    void handleEvent(const sf::Event& event);
    void update(sf::Time deltaTime);
    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
    std::string getText() const;
    void clear();
};

#endif //AUTOCORRECT_TEXTINPUT_H
