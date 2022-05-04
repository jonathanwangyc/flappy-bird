#include <catch2/catch.hpp>

#include "game_engine.h"

using flappybird::Bird;
using flappybird::Obstacle;
using flappybird::GameEngine;
using cinder::vec2;

const int kWindowSizeX = 500; /// the pop-up window width
const int kWindowSizeY = 500; /// the pop-up window height

const double kBirdWidth = 51.1;
const double kBirdHeight = 36.1;

TEST_CASE("Constructor") {
  GameEngine gameEngine = GameEngine(kWindowSizeX, kWindowSizeY, true);

  // check if the variables are set up correctly and/or reset back to 0
  REQUIRE(gameEngine.GetGameStatus() == 0);
  REQUIRE(gameEngine.GetScore() == 0);
  REQUIRE(gameEngine.GetHighestScore() == std::vector<int>{0, 0, 0, 0});
  REQUIRE(gameEngine.GetGameMode() == 2);
}

TEST_CASE("StartGame() test") {
  GameEngine gameEngine = GameEngine(kWindowSizeX, kWindowSizeY, true);
  gameEngine.StartGame();
  Bird bird = gameEngine.GetBird();

  // check if the gameEngine correctly initialize a bird object
  REQUIRE(gameEngine.GetGameStatus() == 1);
  REQUIRE(bird.GetBirdTopLeft() == vec2(kWindowSizeX/2 - kBirdWidth/2, kWindowSizeY/2 - kBirdHeight/2) - vec2(0, bird.kJumpSpace));
  REQUIRE(bird.GetBirdBottomRight() == vec2(kWindowSizeX/2 + kBirdWidth/2, kWindowSizeY/2 + kBirdHeight/2) - vec2(0, bird.kJumpSpace));
}

TEST_CASE("ResetGame() test") {
  GameEngine gameEngine = GameEngine(kWindowSizeX, kWindowSizeY, true);
  gameEngine.ResetGame();

  // check if the variables are reset to 0 after reset function wsa called
  REQUIRE(gameEngine.GetGameStatus() == 0);
  REQUIRE(gameEngine.GetObstacles().size() == 0);
  REQUIRE(gameEngine.GetScore() == 0);
  REQUIRE(gameEngine.GetHighestScore() == std::vector<int>{0, 0, 0, 0});
}

TEST_CASE("UpdateScore() test") {
  GameEngine gameEngine = GameEngine(kWindowSizeX, kWindowSizeY, true);

  SECTION("Has passed") {
    // initialize a test obstacle located on the left of the bird (passed)
    Obstacle obstacle = Obstacle(kWindowSizeX, kWindowSizeY, 1, vec2(0, 0), vec2(10, 10));
    gameEngine.SetObstacles(std::vector<Obstacle>{obstacle});
    gameEngine.UpdateScore();

    // check if the function updates the score
    REQUIRE(gameEngine.GetScore() == 1);
  }
  SECTION("Hasn't passed") {
    // initialize a test obstacle located on the right of the bird (hasn't passed)
    Obstacle obstacle = Obstacle(kWindowSizeX, kWindowSizeY, 1, vec2(300, 0), vec2(400, 10));
    gameEngine.SetObstacles(std::vector<Obstacle>{obstacle});
    gameEngine.UpdateScore();

    // check if the function maintain the same score
    REQUIRE(gameEngine.GetScore() == 0);
  }
}
