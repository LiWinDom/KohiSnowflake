#include "Slider.h"

Slider::Slider(const int16_t& x, const int16_t& y, const uint16_t& width, const uint16_t& height, const int16_t& min, const int16_t& max) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->min = min;
    this->max = max;

    this->slider.setFillColor(sf::Color(INACTIVE_COLOR));
    this->slider.setSize(sf::Vector2f(this->width, this->height / 2));
    this->slider.setPosition(this->x, this->y + this->height / 4);

    this->dot.setFillColor(sf::Color(HOVER_COLOR));
    this->dot.setRadius(this->height);
    this->updateDotPosition();

    this->text.setCharacterSize(TEXT_SIZE);
    this->text.setPosition(this->x + this->width / 2, this->y + this->height / 2);
    this->text.setFillColor(sf::Color(BACKGROUND_COLOR));

    return;
}

void Slider::setLabel(const std::string& label, const sf::Font& font) {
    this->text.setFont(font);
    this->text.setString(label);
    sf::FloatRect bounds = this->text.getLocalBounds();
    this->text.setOrigin(bounds.width / 2.0, TEXT_SIZE / 1.5);

    return;
}

void Slider::setValue(const int16_t& value) {
    this->value = value;
    if (this->selected) {
        this->border.setFillColor(sf::Color(this->selectedColor));
        this->text.setFillColor(sf::Color(BACKGROUND_COLOR));
    }
    else {
        this->border.setFillColor(sf::Color(BACKGROUND_COLOR));
        this->text.setFillColor(sf::Color(this->selectedColor));
    }
    return;
}

void Slider::addCallback(void (*callback)(const int16_t&)) {
    this->callbacks.push_back(callback);
    return;
}

void Slider::clearCallbacks() {
    this->callbacks = {};
    return;
}

void Slider::callCallbacks() {
    for (uint8_t i = 0; i < callbacks.size(); ++i) {
        callbacks[i](this->value);
    }
    return;
}

void Slider::eventProcessing(const sf::Event& event, const sf::Vector2i& mousePos) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseButton == "none") {
        if (mousePos.x >= this->x && mousePos.x <= this->x + this->width &&
            mousePos.y >= this->y && mousePos.y <= this->y + this->height) {
            mouseButton = "left";
        }
        else {
            mouseButton = "missed";
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && mouseButton == "none") {
        mouseButton = "right";
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        if (mouseButton == "left") {
            if (mousePos.x >= this->x && mousePos.x <= this->x + this->width &&
                mousePos.y >= this->y && mousePos.y <= this->y + this->height) {
                this->click();
            }
        }
        mouseButton = "none";
    }
    return;
}

void Slider::draw(sf::RenderWindow& window) {
    window.draw(slider);
    window.draw(dot);
    window.draw(text);

    return;
}

void Slider::updateDotPosition() {
    this->dot.setPosition(, this->y);
    return;
}