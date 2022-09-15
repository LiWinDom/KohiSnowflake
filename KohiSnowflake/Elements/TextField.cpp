#include "TextField.h"

TextField::TextField(const int16_t& x, const int16_t& y, const uint16_t& width, const uint16_t& height, const sf::Font& font) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    this->border.setFillColor(sf::Color(BACKGROUND_COLOR));
    this->border.setOutlineColor(sf::Color(INACTIVE_COLOR));
    this->border.setOutlineThickness(BORDER_SIZE);
    this->border.setSize(sf::Vector2f(this->width - 2 * BORDER_SIZE, this->height - 2 * BORDER_SIZE));
    this->border.setPosition(this->x + BORDER_SIZE, this->y + BORDER_SIZE);

    this->textText.setCharacterSize(TEXT_SIZE);
    this->textText.setOrigin(0, TEXT_SIZE / 1.5);
    this->textText.setPosition(this->x + PADDING_SIZE, this->y + this->height / 2);
    this->textText.setFillColor(sf::Color(HOVER_COLOR));
    this->textText.setFont(font);

    return;
}

std::string TextField::getText() {
    return this->text;
}

void TextField::active() {
    this->selected = true;
    this->border.setOutlineColor(sf::Color(SELECTED_COLOR));
    this->textText.setFillColor(sf::Color(SELECTED_COLOR));

    return;
}

void TextField::deactive() {
    this->selected = false;
    this->textText.setFillColor(sf::Color(HOVER_COLOR));
    this->border.setOutlineColor(sf::Color(INACTIVE_COLOR));

    return;
}

void TextField::addChangeCallback(void (*callback)(const std::string& text)) {
    this->changeCallbacks.push_back(callback);
    return;
}

void TextField::clearChangeCallbacks() {
    this->changeCallbacks = {};
    return;
}

void TextField::callChangeCallbacks() {
    for (uint8_t i = 0; i < this->changeCallbacks.size(); ++i) {
        this->changeCallbacks[i](this->text);
    }
    return;
}

void TextField::addEnterCallback(void (*callback)(const std::string& text)) {
    this->enterCallbacks.push_back(callback);
    return;
}

void TextField::clearEnterCallbacks() {
    this->enterCallbacks = {};
    return;
}

void TextField::callEnterCallbacks() {
    for (uint8_t i = 0; i < this->enterCallbacks.size(); ++i) {
        this->enterCallbacks[i](this->text);
    }
    return;
}

void TextField::clearCallbacks() {
    this->clearChangeCallbacks();
    this->clearEnterCallbacks();
    return;
}

void TextField::eventProcessing(const sf::Event& event, const sf::Vector2i& mousePos) {
    // Hover change
    if (!this->selected) {
        if (mousePos.x >= this->x && mousePos.x <= this->x + this->width &&
            mousePos.y >= this->y && mousePos.y <= this->y + this->height) {
            this->border.setOutlineColor(sf::Color(HOVER_COLOR));
        }
        else {
            this->border.setOutlineColor(sf::Color(INACTIVE_COLOR));
        }

    }

    // Click
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->mouseButton == "none") {
        if (mousePos.x >= this->x && mousePos.x <= this->x + this->width &&
            mousePos.y >= this->y && mousePos.y <= this->y + this->height) {
            this->mouseButton = "left";
        }
        else {
            this->mouseButton = "missed";
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->mouseButton == "none") {
        this->mouseButton = "right";
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        if (mousePos.x >= this->x && mousePos.x <= this->x + this->width &&
            mousePos.y >= this->y && mousePos.y <= this->y + this->height) {
            if (this->mouseButton == "left") {
                this->active();
            }
        }
        else {
            this->deactive();
        }
        this->mouseButton = "none";
    }

    // Keyboard event
    if (this->selected) {
        if (event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                this->callEnterCallbacks();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                if (text.size() > 0) {
                    this->text.pop_back();
                    this->textText.setString(this->text);
                    this->callChangeCallbacks();
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
                if (text.size() > 0) {
                    this->text = "";
                    this->textText.setString(this->text);
                    this->callChangeCallbacks();
                }
            }
        }
        else if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                this->text += event.text.unicode;
                this->textText.setString(this->text);
                this->callChangeCallbacks();
            }
        }
    }
    return;
}

void TextField::draw(sf::RenderWindow& window) {
    window.draw(border);
    window.draw(textText);

    return;
}