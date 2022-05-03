#include <catch2/catch.hpp>

#include "game_engine.h"

using flappybird::Obstacle;
using cinder::vec2;

const int kWindowSizeX = 500; /// the pop-up window width
const int kWindowSizeY = 500; /// the pop-up window height

TEST_CASE("Constructor/InitializeGameMode() test") {
  SECTION("Game mode 1") {
    Obstacle obstacle = Obstacle(kWindowSizeX, kWindowSizeY, 1, vec2(0, 0), vec2(10, 10));

    REQUIRE(obstacle.GetGameMode() == 1);
    REQUIRE(obstacle.HasPassed() == false);
    REQUIRE(obstacle.GetMovingSpeed() == Approx(2.0));
    REQUIRE(obstacle.GetGapWidth() == Approx(216 / 1.0));
  }
  SECTION("Game mode 2") {
    Obstacle obstacle = Obstacle(kWindowSizeX, kWindowSizeY, 2, vec2(0, 0), vec2(10, 10));

    REQUIRE(obstacle.GetGameMode() == 2);
    REQUIRE(obstacle.HasPassed() == false);
    REQUIRE(obstacle.GetMovingSpeed() == Approx(2.5));
    REQUIRE(obstacle.GetGapWidth() == Approx(216 / 1.2));
  }
}

TEST_CASE("Obstacle AdvanceOneFrame() test") {
  Obstacle obstacle = Obstacle(kWindowSizeX, kWindowSizeY, 2, vec2(50, 50), vec2(100, 100));
  obstacle.AdvanceOneFrame();
  vec2 one_frame = vec2(obstacle.GetMovingSpeed(), 0);

  REQUIRE(obstacle.GetObstacleTopLeft() == vec2(50, 50) - one_frame);
  REQUIRE(obstacle.GetObstacleBottomRight() == vec2(100, 100) - one_frame);
}

TEST_CASE("GenerateRandomDouble() test") {
  Obstacle obstacle = Obstacle(kWindowSizeX, kWindowSizeY, 2, vec2(0, 0), vec2(10, 10));

  SECTION("Positive range") {
    double random_double = obstacle.GenerateRandomDouble(0.25, 0.75);
    REQUIRE((random_double >= 0.25 && random_double <= 0.75) == true);
  }
  SECTION("Negative range") {
    double random_double = obstacle.GenerateRandomDouble(-0.25, -0.75);
    REQUIRE((random_double <= -0.25 && random_double >= -0.75) == true);
  }
  SECTION("One possible value") {
    double random_double = obstacle.GenerateRandomDouble(1, 1);
    REQUIRE(random_double == 1);
  }
}