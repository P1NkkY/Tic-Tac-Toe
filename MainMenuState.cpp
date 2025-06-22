#include "MainMenuState.h"
#include "consts.h"
#include <iostream>
#include <sstream>

#include "GameState.h"

MainMenuState::MainMenuState(GameDataRef data) : _data(data) {}

void MainMenuState::Init() {
    _data.get()->assets.LoadTexture("Background",
                                    MAIN_MENU_BACKGROUND_FILEPATH);
    _data.get()->assets.LoadTexture("Play Button", MAIN_MENU_PLAY_BUTTON);
    _data.get()->assets.LoadTexture("Play Button Outer",
                                    MAIN_MENU_PLAY_BUTTON_OUTER);
    _data.get()->assets.LoadTexture("Game Title", MAIN_METU_TITLE_PATH);

    _background.setTexture(_data.get()->assets.GetTexture("Background"));
    _playButton.setTexture(_data.get()->assets.GetTexture("Play Button"));
    _playButtonOuter.setTexture(
        _data.get()->assets.GetTexture("Play Button Outer"));
    _title.setTexture(_data.get()->assets.GetTexture("Game Title"));

    _playButton.setPosition(
        (SCREEN_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2),
        (SCREEN_HEIGHT / 2) - (_playButton.getGlobalBounds().height / 2));
    _playButtonOuter.setPosition(
        (SCREEN_WIDTH / 2) - (_playButtonOuter.getGlobalBounds().width / 2),
        (SCREEN_HEIGHT / 2) - (_playButtonOuter.getGlobalBounds().height / 2));
    _title.setPosition((SCREEN_WIDTH / 2) -
                           (_title.getGlobalBounds().width / 2),
                       _title.getGlobalBounds().height * 0.1);
}

void MainMenuState::HandleInput() {
    sf::Event event;

    while (_data.get()->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            _data.get()->window.close();
        }

        if (_data.get()->input.IsSpriteClicked(_playButton, sf::Mouse::Left,
                                               _data.get()->window)) {
            _data.get()->machine.AddState(StateRef(new GameState(_data)), true);
        }
    }
}

void MainMenuState::Update(float dt) {}

void MainMenuState::Draw(float dt) {
    _data.get()->window.clear();

    _data.get()->window.draw(_background);
    _data.get()->window.draw(_playButton);
    _data.get()->window.draw(_playButtonOuter);
    _data.get()->window.draw(_title);

    _data.get()->window.display();
}