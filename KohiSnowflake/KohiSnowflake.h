#pragma once
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Config.h"

class KohiSnowflake
{
public:
	KohiSnowflake(const int16_t& x, const int16_t& y, const uint16_t& width, const uint16_t& height);

    void recalc(const uint16_t& steps);

    void draw(sf::RenderWindow& window);

private:
    void create(const uint8_t& curStep, const uint8_t& needSteps, sf::Vector2f coord, const double& rotation, uint32_t& insert);

    sf::Vector2f getSecondPoint(sf::Vector2f first, sf::Vector2f movement);

    int16_t x, y;
    uint16_t width, height;

    sf::VertexArray lines;
};

