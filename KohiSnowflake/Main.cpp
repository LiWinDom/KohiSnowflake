#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <Windows.h>

#include "Config.h"
#include "Containers.h"
#include "Elements/Everything.h"

sf::Font font;
bool inFocus = true;

void onStart(sf::RenderWindow& window) {
    font.loadFromFile("resourses/Consolas.ttf");
    //sf::Image icon;
    //icon.loadFromFile("resourses/icon.png");
    //window.setIcon(52, 52, icon.getPixelsPtr());
    window.setVerticalSyncEnabled(true);
    window.setActive(true);
    return;
}

void display(sf::RenderWindow& window) {
    window.clear(sf::Color(BACKGROUND_COLOR));
    window.display();
    return;
}

void eventProcessing(sf::RenderWindow& window) {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();

        if (event.type == sf::Event::LostFocus) {
            inFocus = false;
        }
        else if (event.type == sf::Event::GainedFocus) {
            inFocus = true;
        }
        if (!inFocus) continue;

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    }
    return;
}

int main() {
#if !DEBUG
    ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif // !DEBUG

    try {
        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Kohi snowflake [0.1]", sf::Style::Close);
        onStart(window);

        while (window.isOpen()) {
            eventProcessing(window);
            display(window);
        }
    }
    catch (...) {
        ShowWindow(GetConsoleWindow(), SW_SHOW);
        std::cout << "Something went wrong. We are sorry about that";
    }
    return 0;
}