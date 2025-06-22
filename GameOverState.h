#pragma once

#include "Game.h"
#include "State.h"
#include <SFML/Graphics.hpp>

class GameOverState : public State {
  public:
    GameOverState(GameDataRef data);

    void Init();

    void HandleInput();

    void Update(float dt);

    void Draw(float dt);

  private:
    GameDataRef _data;
    sf::Sprite _retryButton;
    sf::Sprite _homeButton;
};