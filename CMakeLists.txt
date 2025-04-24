cmake_minimum_required(VERSION 3.26)
project(Database)

set(CMAKE_CXX_STANDARD 17)

add_executable(Database main.cpp
        Spreadsheet.h
        Spreadsheet.cpp
        Font.h
        Font.cpp
        Cell.h
        Cell.cpp
        Header.h
        Header.cpp
        Row.cpp
        QueryParser.h
        QueryParser.cpp
        QueryParser.cpp
        StateMachine.h
        StateMachine.cpp
        Table.h
        Table.cpp
        Database.h
        Database.cpp
        TextInput.h
        TextInput.cpp
        Backspace.h
        Backspace.cpp
        Cursor.h
        Cursor.cpp
        CS3A_Tetris/Block.cpp
        CS3A_Tetris/Block.h
        CS3A_Tetris/Field.cpp
        CS3A_Tetris/Field.h
        CS3A_Tetris/Game.cpp
        CS3A_Tetris/Game.h
        CS3A_Tetris/Settings.h
        CS3A_Tetris/SplashScreen.cpp
        CS3A_Tetris/SplashScreen.h
        CS3A_Tetris/TetrisApp.cpp
        CS3A_Tetris/TetrisApp.h
        DatabaseApp.h
        DatabaseApp.cpp
)

target_link_libraries(Database sfml-graphics sfml-audio)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)