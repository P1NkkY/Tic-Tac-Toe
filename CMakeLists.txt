cmake_minimum_required(VERSION 3.28)
project(TicTacToe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

# Add your executable
add_executable(${PROJECT_NAME} 
    State.h
    StateMachine.h
    AssetManager.h
    InputManager.h
    Game.h
    consts.h
    SplashState.h

    StateMachine.cpp
    AssetManager.cpp
    InputManager.cpp
    Game.cpp
    SplashState.cpp
    main.cpp
)

# Link SFML libraries to your executable
target_link_libraries(${PROJECT_NAME}
PUBLIC
    sfml-window
    sfml-graphics
)