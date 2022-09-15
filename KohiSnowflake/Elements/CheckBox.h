#pragma once
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <vector>

#include "../Config.h"

class CheckBox {
public:
    CheckBox(const int16_t& x, const int16_t& y, const uint16_t& width, const uint16_t& height, const uint32_t& selectedColor = SELECTED_COLOR);

    void setLabel(const std::string& label, const sf::Font& font);

    void click(const bool& callCallbacks = true);

    void addCallback(void (*callback)(const bool&));

    void clearCallbacks();

    void callCallbacks();

    void eventProcessing(const sf::Event& event, const sf::Vector2i& mousePos);

    void draw(sf::RenderWindow& window);

private:
    int16_t x, y;
    uint16_t width, height;
    uint32_t selectedColor;
    std::string mouseButton = "none";

    bool selected = false;
    sf::RectangleShape border;
    sf::Text text;

    std::vector<void (*)(const bool&)> callbacks = {};
};