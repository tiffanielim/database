//
// Created by Tiffanie Lim on 11/4/24.
//

#ifndef AUTOCORRECT_CURSOR_H
#define AUTOCORRECT_CURSOR_H
#include <SFML/Graphics.hpp>

class Cursor {
private:
    sf::RectangleShape cursor;
    sf::Time blinkTime;
    bool visible;
    unsigned int position;

public:
    Cursor(unsigned int size);

    void update(sf::Time deltaTime);
    void render(sf::RenderWindow& window);
    void updatePosition(const sf::Text& text);
    unsigned int getPosition() const;
    void moveLeft();
    void moveRight();
    void setPosition(unsigned int pos);
};

#endif //AUTOCORRECT_CURSOR_H
