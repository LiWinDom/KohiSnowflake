#include "KohiSnowflake.h"

KohiSnowflake::KohiSnowflake(const int16_t& x, const int16_t& y, const uint16_t& width, const uint16_t& height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    this->lines = sf::VertexArray(sf::LineStrip, 0);
    this->recalc(0);

    return;
}

void KohiSnowflake::recalc(const uint16_t& steps) {
    uint32_t size = 3 * std::pow(4, steps);

    const double length = std::min(this->height, this->width) / 1.5;
    sf::Vector2f coord((this->width - length) / 2, (this->height - 2 * length * std::sqrt(3) / 3) / 2 + length * std::sqrt(3) / 6);
    this->lines.resize(size + 1);
    uint32_t counter = 0;
    this->lines[counter].position = coord;
    this->lines[counter].color = sf::Color::Black;

    this->create(0, steps, coord, 0, counter);
    this->create(0, steps, coord, -2 * PI / 3, counter);
    this->create(0, steps, coord, 2 * PI / 3, counter);
    return;
}

void KohiSnowflake::draw(sf::RenderWindow& window) {
    window.draw(this->lines);
    return;
}

void KohiSnowflake::create(const uint8_t& curStep, const uint8_t& needSteps, sf::Vector2f coord, const double& rotation, uint32_t& insert) {
    if (curStep == needSteps) {
        sf::Vector2f newPoint = this->getSecondPoint(this->lines[insert].position, sf::Vector2f(std::min(this->height, this->width) / 1.5 / std::pow(3, needSteps), rotation));
        this->lines[insert + 1].color = this->lines[insert].color;
        this->lines[++insert].position = newPoint;
        return;
    }
    this->create(curStep + 1, needSteps, coord, rotation, insert);
    this->create(curStep + 1, needSteps, coord, rotation + PI / 3, insert);
    this->create(curStep + 1, needSteps, coord, rotation - PI / 3, insert);
    this->create(curStep + 1, needSteps, coord, rotation, insert);

    return;
}

sf::Vector2f KohiSnowflake::getSecondPoint(sf::Vector2f first, sf::Vector2f movement) {
    return sf::Vector2f(first.x + movement.x * std::cos(movement.y), first.y - movement.x * std::sin(movement.y));
}
