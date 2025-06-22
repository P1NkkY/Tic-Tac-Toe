#include "GameState.h"
#include "PauseState.h"
#include "consts.h"
#include <iostream>
#include <sstream>

#include "GameOverState.h"

GameState::GameState(GameDataRef data) : _data(data) {}

void GameState::Init() {
    gameState = STATE_PLAYING;
    turn = PLAYER_PIECE;

    _data.get()->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
    _data.get()->assets.LoadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);
    _data.get()->assets.LoadTexture("X Piece", X_PIECE_FILEPATH);
    _data.get()->assets.LoadTexture("O Piece", O_PIECE_FILEPATH);
    _data.get()->assets.LoadTexture("X Winning Piece",
                                    X_WINNING_PIECE_FILEPATH);
    _data.get()->assets.LoadTexture("O Winning Piece",
                                    O_WINNING_PIECE_FILEPATH);

    _background.setTexture(_data.get()->assets.GetTexture("Background"));
    _pauseButton.setTexture(_data.get()->assets.GetTexture("Pause Button"));
    _gridSprite.setTexture(_data.get()->assets.GetTexture("Grid Sprite"));

    _pauseButton.setPosition(_data.get()->window.getSize().x -
                                 _pauseButton.getLocalBounds().width,
                             _pauseButton.getPosition().y);
    _gridSprite.setPosition(
        SCREEN_WIDTH / 2 - _gridSprite.getGlobalBounds().width / 2,
        SCREEN_HEIGHT / 2 - _gridSprite.getGlobalBounds().height / 2);

    InitGridPieces();

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            gridArray[x][y] = EMPTY_PIECE;
        }
    }
}

void GameState::HandleInput() {
    sf::Event event;

    while (_data.get()->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            _data.get()->window.close();
        }

        if (_data.get()->input.IsSpriteClicked(_pauseButton, sf::Mouse::Left,
                                               _data.get()->window)) {
            _data.get()->machine.AddState(StateRef(new PauseState(_data)),
                                          false);
        } else if (_data.get()->input.IsSpriteClicked(
                       _gridSprite, sf::Mouse::Left, _data.get()->window)) {
            if (STATE_PLAYING == gameState) {
                CheckAndPlacePiece();
            }
        }
    }
}

void GameState::Update(float dt) {
    if (gameState == STATE_DRAW || gameState == STATE_LOOSE ||
        gameState == STATE_WON) {
        if (_clock.getElapsedTime().asMilliseconds() >
            TIME_BEFORE_SHOWING_GAVE_OVER) {
            _data.get()->machine.AddState(StateRef(new GameOverState(_data)),
                                          true);
        }
    }
}

void GameState::Draw(float dt) {
    _data.get()->window.clear();

    _data.get()->window.draw(_background);
    _data.get()->window.draw(_pauseButton);
    _data.get()->window.draw(_gridSprite);

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            _data.get()->window.draw(_gridPieces[x][y]);
        }
    }

    _data.get()->window.display();
}

void GameState::InitGridPieces() {
    sf::Vector2u tempSpriteSize =
        _data.get()->assets.GetTexture("X Piece").getSize();

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            _gridPieces[x][y].setTexture(
                _data.get()->assets.GetTexture("X Piece"));
            _gridPieces[x][y].setPosition(
                _gridSprite.getPosition().x + tempSpriteSize.x * x - 7,
                _gridSprite.getPosition().y + tempSpriteSize.y * y - 7);
            _gridPieces[x][y].setColor(sf::Color(255, 255, 255, 0));
        }
    }
}

void GameState::CheckAndPlacePiece() {
    sf::Vector2i touchPoint =
        _data.get()->input.GetMousePosition(_data.get()->window);
    sf::FloatRect gridSize = _gridSprite.getGlobalBounds();
    sf::Vector2f gapOutsideOfGrid =
        sf::Vector2f((SCREEN_WIDTH - gridSize.width) / 2,
                     (SCREEN_HEIGHT - gridSize.height) / 2);
    sf::Vector2f gridLocalTouchPos = sf::Vector2f(
        touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);
    sf::Vector2f gridSectionSize =
        sf::Vector2f(gridSize.width / 3, gridSize.height / 3);

    int column, row;
    if (gridLocalTouchPos.x < gridSectionSize.x) {
        column = 1;
    } else if (gridLocalTouchPos.x < gridSectionSize.x * 2) {
        column = 2;
    } else if (gridLocalTouchPos.x < gridSize.width * 2) {
        column = 3;
    }

    if (gridLocalTouchPos.y < gridSectionSize.y) {
        row = 1;
    } else if (gridLocalTouchPos.y < gridSectionSize.y * 2) {
        row = 2;
    } else if (gridLocalTouchPos.y < gridSize.height * 2) {
        row = 3;
    }

    if (gridArray[column - 1][row - 1] == EMPTY_PIECE) {
        gridArray[column - 1][row - 1] = turn;

        if (PLAYER_PIECE == turn) {
            _gridPieces[column - 1][row - 1].setTexture(
                _data.get()->assets.GetTexture("X Piece"));
            CheckPlayerHasWon(turn);
            turn = AI_PIECE;
        } else if (AI_PIECE == turn) {
            _gridPieces[column - 1][row - 1].setTexture(
                _data.get()->assets.GetTexture("O Piece"));
            CheckPlayerHasWon(turn);
            turn = PLAYER_PIECE;
        }

        _gridPieces[column - 1][row - 1].setColor(
            sf::Color(255, 255, 255, 255));
    }
}

void GameState::CheckPlayerHasWon(int player) {
    Check3PiecesForMatch(0, 0, 1, 0, 2, 0, player);
    Check3PiecesForMatch(0, 1, 1, 1, 2, 1, player);
    Check3PiecesForMatch(0, 2, 1, 2, 2, 2, player);
    Check3PiecesForMatch(0, 0, 0, 1, 0, 2, player);
    Check3PiecesForMatch(1, 0, 1, 1, 1, 2, player);
    Check3PiecesForMatch(2, 0, 2, 1, 2, 2, player);
    Check3PiecesForMatch(0, 0, 1, 1, 2, 2, player);
    Check3PiecesForMatch(0, 2, 1, 1, 2, 0, player);

    int emptyNum = 9;

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (EMPTY_PIECE != gridArray[x][y]) {
                emptyNum--;
            }
        }
    }

    if (emptyNum == 0 && STATE_WON != gameState && STATE_LOOSE != gameState) {
        gameState = STATE_DRAW;
    }

    if (gameState == STATE_DRAW || gameState == STATE_LOOSE ||
        gameState == STATE_WON) {
        _clock.restart();
    }

    std::cout << gameState << std::endl;
}

void GameState::Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3,
                                     int y3, int pieceToCheck) {
    if (pieceToCheck == gridArray[x1][y1] &&
        pieceToCheck == gridArray[x2][y2] &&
        pieceToCheck == gridArray[x3][y3]) {
        std::string winningPieceStr;

        if (pieceToCheck == O_PIECE) {
            winningPieceStr = "O Winning Piece";
        } else {
            winningPieceStr = "X Winning Piece";
        }
        _gridPieces[x1][y1].setTexture(
            _data.get()->assets.GetTexture(winningPieceStr));
        _gridPieces[x2][y2].setTexture(
            _data.get()->assets.GetTexture(winningPieceStr));
        _gridPieces[x3][y3].setTexture(
            _data.get()->assets.GetTexture(winningPieceStr));

        if (pieceToCheck == PLAYER_PIECE) {
            gameState = STATE_WON;
        } else {
            gameState = STATE_LOOSE;
        }
    }
}
