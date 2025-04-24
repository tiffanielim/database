//
// Created by Tiffanie Lim on 11/4/24.
//

#ifndef CS8_CURSOR_FONT_H
#define CS8_CURSOR_FONT_H
//template <typename T, typename S>
//struct Pair
//{
//    T first;
//    S second
//}; this is what the map holds, objects of these pairs

#include <map>
#include <string>
#include <SFML/Graphics.hpp>

class Font {
private:
    inline static std::map<std::string, sf::Font> _fonts;
    static void loadFont(const std::string& fontName);
    static std::string getFontPath(std::string fontName);

public:
    static sf::Font& getFont(const std::string& fontName);

};

#endif //CS8_CURSOR_FONT_H