#include "InputManager.h"

bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button,
                                   sf::RenderWindow &window) {
    if (sf::Mouse::isButtonPressed(button)) {
        sf::IntRect tempRect(object.getPosition().x, object.getPosition().y,
                             object.getGlobalBounds().width,
                             object.getGlobalBounds().height);
        if (tempRect.contains(sf::Mouse::getPosition(window))) {
            return true;
        }
    }

    return false;
}

sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow &window) {
    return sf::Mouse::getPosition(window);
}
