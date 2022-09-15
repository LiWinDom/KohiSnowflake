#pragma once
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <vector>

#include "../Config.h"

class Slider {
public:
    Slider(const int16_t& x, const int16_t& y, const uint16_t& width, const uint16_t& height, const int16_t& min, const int16_t& max);

    void setLabel(const std::string& label, const sf::Font& font);

    void setValue(const int16_t& value);

    void addCallback(void (*callback)(const int16_t&));

    void clearCallbacks();

    void callCallbacks();

    void eventProcessing(const sf::Event& event, const sf::Vector2i& mousePos);

    void draw(sf::RenderWindow& window);

private:
    void updateDotPosition();

    int16_t x, y;
    uint16_t width, height;
    int16_t min, max;
    std::string mouseButton = "none";

    int16_t value = 0;
    sf::RectangleShape slider;
    sf::CircleShape dot;
    sf::Text text;

    std::vector<void (*)(const int16_t&)> callbacks = {};
};