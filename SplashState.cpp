#include "SplashState.h"

#include "consts.h"

#include <iostream>
#include <sstream>

SplashState::SplashState(GameDataRef data) : m_data(data) {}

void SplashState::Init() {
    m_data->assets.LoadTexture("Splash State Background",
                               SPLASH_SCENE_BACKGROUND_FILEPATH);
    m_background.setTexture(
        m_data->assets.GetTexture("Splash State Background"));
}

void SplashState::HandleInput() {
    sf::Event event;

    while (m_data->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            m_data->window.close();
        }
    }
}

void SplashState::Update(float dt) {
    if (m_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOT_TIME) {
        // Switch to the Main Menu
    }
}

void SplashState::Draw(float dt) {
    m_data->window.clear(sf::Color::Red);
    m_data->window.draw(m_background);
    m_data->window.display();
}