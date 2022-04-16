#include <catch2/catch.hpp>

#include "game_engine.h"

using flappybird::Bird;
using flappybird::Obstacle;
using cinder::vec2;

const int kWindowSizeX = 500; /// the pop-up window width
const int kWindowSizeY = 500; /// the pop-up window height

const double kBirdWidth = 51.1;
const double kBirdHeight = 36.1;

TEST_CASE("Constructor test") {
  Bird bird = Bird(kWindowSizeX, kWindowSizeY, true);

  REQUIRE(bird.GetGravityMultiplier() == Approx(1.0));
  REQUIRE(bird.GetBirdTopLeft() == vec2(kWindowSizeX/2 - kBirdWidth/2, kWindowSizeY/2 - kBirdHeight/2));
  REQUIRE(bird.GetBirdBottomRight() == vec2(kWindowSizeX/2 + kBirdWidth/2, kWindowSizeY/2 + kBirdHeight/2));
}

TEST_CASE("Bird AdvanceOneFrame() test") {
  Bird bird = Bird(kWindowSizeX, kWindowSizeY, true);
  bird.AdvanceOneFrame();
  vec2 one_frame = vec2(0, bird.GetGravityMultiplier() * bird.kGravity);

  REQUIRE(bird.GetGravityMultiplier() == Approx(1.03));
  REQUIRE(bird.GetBirdTopLeft() == vec2(kWindowSizeX/2 - kBirdWidth/2, kWindowSizeY/2 - kBirdHeight/2) + one_frame);
  REQUIRE(bird.GetBirdBottomRight() == vec2(kWindowSizeX/2 + kBirdWidth/2, kWindowSizeY/2 + kBirdHeight/2) + one_frame);
}

TEST_CASE("Fly() test") {
  Bird bird = Bird(kWindowSizeX, kWindowSizeY, true);
  bird.Fly();

  REQUIRE(bird.GetGravityMultiplier() == Approx(1.0));
  REQUIRE(bird.GetBirdTopLeft() == vec2(kWindowSizeX/2 - kBirdWidth/2, kWindowSizeY/2 - kBirdHeight/2) - vec2(0, bird.kJumpSpace));
  REQUIRE(bird.GetBirdBottomRight() == vec2(kWindowSizeX/2 + kBirdWidth/2, kWindowSizeY/2 + kBirdHeight/2) - vec2(0, bird.kJumpSpace));
}

TEST_CASE("HasCollide() test") {
  Bird bird = Bird(kWindowSizeX, kWindowSizeY, true);

  SECTION("Will collide") {
    Obstacle obstacle = Obstacle(kWindowSizeX, kWindowSizeY, 2, vec2(0, 0), vec2(500, 250));
    std::vector<Obstacle> obstacles = {obstacle};

    REQUIRE(bird.HasCollide(obstacles) == true);
  }
  SECTION("Won't collide") {
    Obstacle obstacle = Obstacle(kWindowSizeX, kWindowSizeY, 2, vec2(0, 0), vec2(10, 10));
    std::vector<Obstacle> obstacles = {obstacle};

    REQUIRE(bird.HasCollide(obstacles) == false);
  }
}

TEST_CASE("ResetPosition() test") {
  Bird bird = Bird(kWindowSizeX, kWindowSizeY, true);
  bird.AdvanceOneFrame();
  bird.ResetPosition();

  REQUIRE(bird.GetBirdTopLeft() == vec2(kWindowSizeX/2 - kBirdWidth/2, kWindowSizeY/2 - kBirdHeight/2));
  REQUIRE(bird.GetBirdBottomRight() == vec2(kWindowSizeX/2 + kBirdWidth/2, kWindowSizeY/2 + kBirdHeight/2));
}