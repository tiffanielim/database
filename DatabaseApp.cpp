//
// Created by Tiffanie Lim on 12/9/24.
//

#include "DatabaseApp.h"

DatabaseApp::DatabaseApp()
        : window(sf::VideoMode(1980, 1120), "Database"), queryBox(1345, 40, 50, 50)
{
    window.setFramerateLimit(60);
}

void DatabaseApp::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::Closed)
        window.close();

    queryBox.handleEvent(event);

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Enter)
        {
            std::string query = queryBox.getText();
            processQuery(query);
            queryBox.clear();
        }
        if (event.key.code == sf::Keyboard::Slash)
        {
            try {
                TetrisApp::run();
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        }
    }
}

void DatabaseApp::processQuery(const std::string& query)
{
    try {
        db.query(query);

        if (query.find("CREATE TABLE") != std::string::npos)
        {
            size_t tableStart = query.find("TABLE") + 6;
            size_t tableEnd = query.find(' ', tableStart);
            currentTable = query.substr(tableStart, tableEnd - tableStart);

            currentSheet = &db.getSpreadsheet(currentTable);
        }
        if (query.find("SELECT") != std::string::npos)
        {
            currentSheet = &db.getSpreadsheet(currentTable);
        }
        if (query.find("DELETE") != std::string::npos)
        {
            currentSheet = nullptr;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void DatabaseApp::run()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            handleEvent(event);

        sf::Time deltaTime = clock.restart();
        queryBox.update(deltaTime);

//        window.clear(sf::Color(251, 198, 207));
        window.clear(sf::Color(255, 232, 124));

        if (currentSheet)
        {
            sf::FloatRect textBoxBounds = queryBox.getBounds();
            currentSheet->setOffset(textBoxBounds.left, textBoxBounds.top + textBoxBounds.height + 10);
            currentSheet->draw(window);
        }

        queryBox.render(window);
        window.display();
    }
}
