#pragma once

#include "AssetManager.h"
#include "InputManager.h"
#include "StateMachine.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

struct GameData {
    StateMachine machine;
    sf::RenderWindow window;
    AssetManager assets;
    InputManager input;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game {
  private:
  public:
    Game(int width, int height, std::string title);
    ~Game() {}

  private:
    const float dt = 1.0f / 60.0f;
    sf::Clock m_clock;
    GameDataRef m_data = std::make_shared<GameData>();

    void Run();
};
