#pragma once

#include "Game.h"
#include "State.h"
#include <SFML/Graphics.hpp>

class SplashState : public State {
  public:
    SplashState(GameDataRef data);

    void Init();

    void HandleInput();

    void Update(float dt);

    void Draw(float dt);

  private:
    GameDataRef m_data;
    sf::Clock m_clock;
    sf::Sprite m_background;
};