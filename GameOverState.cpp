#include "GameOverState.h"
#include "MainMenuState.h"
#include "consts.h"
#include <iostream>
#include <sstream>

#include "GameState.h"

GameOverState::GameOverState(GameDataRef data) : _data(data) {}

void GameOverState::Init() {
    _data.get()->assets.LoadTexture("Retry Button", RETRY_BUTTON);
    _data.get()->assets.LoadTexture("Home Button", HOME_BUTTON);

    _retryButton.setTexture(_data.get()->assets.GetTexture("Retry Button"));
    _homeButton.setTexture(_data.get()->assets.GetTexture("Home Button"));

    _retryButton.setPosition(_data.get()->window.getSize().x / 2 -
                                 _retryButton.getLocalBounds().width / 2,
                             _data.get()->window.getSize().y / 3 -
                                 _retryButton.getLocalBounds().height / 2);
    _homeButton.setPosition(_data.get()->window.getSize().x / 2 -
                                _homeButton.getLocalBounds().width / 2,
                            _data.get()->window.getSize().y / 3 * 2 -
                                _homeButton.getLocalBounds().height / 2);
}

void GameOverState::HandleInput() {
    sf::Event event;

    while (_data.get()->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            _data.get()->window.close();
        }

        if (_data.get()->input.IsSpriteClicked(_retryButton, sf::Mouse::Left,
                                               _data.get()->window)) {
            _data.get()->machine.AddState(StateRef(new GameState(_data)), true);
        }

        if (_data.get()->input.IsSpriteClicked(_homeButton, sf::Mouse::Left,
                                               _data.get()->window)) {
            _data.get()->machine.AddState(StateRef(new MainMenuState(_data)),
                                          true);
        }
    }
}

void GameOverState::Update(float dt) {}

void GameOverState::Draw(float dt) {
    _data.get()->window.clear(sf::Color::Red);

    _data.get()->window.draw(_retryButton);
    _data.get()->window.draw(_homeButton);

    _data.get()->window.display();
}