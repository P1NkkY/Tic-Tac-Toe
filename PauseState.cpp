#include "PauseState.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "consts.h"
#include <iostream>

PauseState::PauseState(GameDataRef data) : _data(data) {}

void PauseState::Init() {
    _data.get()->assets.LoadTexture("Pause Background",
                                    PAUSE_BACKGROUND_FILEPATH);
    _data.get()->assets.LoadTexture("Resume Button", RESUME_BUTTON);

    _data.get()->assets.LoadTexture("Home Button", HOME_BUTTON);
    _background.setTexture(_data.get()->assets.GetTexture("Pause Background"));
    _resumeButton.setTexture(_data.get()->assets.GetTexture("Resume Button"));
    _homeButton.setTexture(_data.get()->assets.GetTexture("Home Button"));

    _resumeButton.setPosition(_data.get()->window.getSize().x / 2 -
                                  _resumeButton.getLocalBounds().width / 2,
                              _data.get()->window.getSize().y / 3 -
                                  _resumeButton.getLocalBounds().height / 2);
    _homeButton.setPosition(_data.get()->window.getSize().x / 2 -
                                _homeButton.getLocalBounds().width / 2,
                            _data.get()->window.getSize().y / 3 * 2 -
                                _homeButton.getLocalBounds().height / 2);
}

void PauseState::HandleInput() {
    sf::Event event;

    while (_data.get()->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            _data.get()->window.close();
        }

        if (_data.get()->input.IsSpriteClicked(_resumeButton, sf::Mouse::Left,
                                               _data.get()->window)) {
            _data.get()->machine.RemoveState();
        }

        if (_data.get()->input.IsSpriteClicked(_homeButton, sf::Mouse::Left,
                                               _data.get()->window)) {
            _data.get()->machine.RemoveState();
            _data.get()->machine.AddState(StateRef(new MainMenuState(_data)),
                                          true);
        }
    }
}

void PauseState::Update(float dt) {}

void PauseState::Draw(float dt) {
    _data.get()->window.clear();

    _data.get()->window.draw(_background);
    _data.get()->window.draw(_resumeButton);
    _data.get()->window.draw(_homeButton);

    _data.get()->window.display();
}