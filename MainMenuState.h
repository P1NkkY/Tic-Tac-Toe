#pragma once

#include "Game.h"
#include "State.h"
#include <SFML/Graphics.hpp>

class MainMenuState : public State {
  public:
    MainMenuState(GameDataRef data);

    void Init();

    void HandleInput();

    void Update(float dt);

    void Draw(float dt);

  private:
    GameDataRef _data;
    sf::Sprite _background;
    sf::Sprite _playButton;
    sf::Sprite _playButtonOuter;
    sf::Sprite _title;
};