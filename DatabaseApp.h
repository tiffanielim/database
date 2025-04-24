//
// Created by Tiffanie Lim on 12/9/24.
//

#ifndef DATABASE_DATABASEAPP_H
#define DATABASE_DATABASEAPP_H
#include <SFML/Graphics.hpp>
#include "Database.h"
#include "TextInput.h"
#include "Spreadsheet.h"
#include "CS3A_Tetris/TetrisApp.h"

class DatabaseApp {
private:
    sf::RenderWindow window;
    Database db;
    TextInput queryBox;
    Spreadsheet* currentSheet = nullptr;
    std::string currentTable;

    void handleEvent(const sf::Event& event);
    void processQuery(const std::string& query);

public:
    DatabaseApp();
    void run();
};


#endif //DATABASE_DATABASEAPP_H
