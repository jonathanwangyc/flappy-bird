#include <catch2/catch.hpp>

#include "game_engine.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using flappybird::Bird;

//TEST_CASE("Test") {
//  Bird bird(1250, 725);
//  REQUIRE(bird.GetBirdXPosition() == Approx(599.45));
//}

//TEST_CASE("Test") {
//  flappybird::Obstacle obstacle(1250, 725, 1);
//  REQUIRE(obstacle.GetObstacleXPosition() == Approx(599.45));
//}

TEST_CASE("Test image") {
  auto flappy_bird_ = loadImage(ci::app::loadAsset("flappy_bird.png"));
  flappy_bird_->getRowBytes();
  auto image = ci::gl::Texture2d::create(flappy_bird_);
}

