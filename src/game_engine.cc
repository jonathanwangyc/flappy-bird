#include "game_engine.h"

namespace flappybird {

GameEngine::GameEngine(int window_size_x, int window_size_y) :
    kWindowSizeX(window_size_x), kWindowSizeY(window_size_y),
    bird_(Bird(kWindowSizeX, kWindowSizeY)) {
  game_status_ = 0;
  frame_count_ = 0;

  obstacles_.push_back(Obstacle(kWindowSizeX, kWindowSizeY));
}

void GameEngine::Display() const {
  bird_.Draw();

  for (Obstacle obstacle : obstacles_) {
    obstacle.Draw();
  }

}

void GameEngine::AdvanceOneFrame() {
  frame_count_++;

  bird_.AdvanceOneFrame();
//  if (HasCollide()) {
//
//  } else {
    for (Obstacle& obstacle : obstacles_) {
      obstacle.AdvanceOneFrame();
    }

    if (IsOutOfBound(obstacles_[0])) {
      // remove first obstacle

      obstacles_.erase(obstacles_.begin());
    }
    if (frame_count_ == kObstacleFrequency) {
      frame_count_%=kObstacleFrequency;
      obstacles_.push_back(Obstacle(kWindowSizeX, kWindowSizeY));
    }
//
//  }
}

int GameEngine::GetGameStatus() {
  return game_status_;
}

void GameEngine::SetGameStatus(int status) {
  game_status_ = status;
}

void GameEngine::MakeBirdFly() {
  bird_.Fly();
}

bool GameEngine::HasCollide() {
  this->SetGameStatus(0);

  return false;
}

bool GameEngine::IsOutOfBound(Obstacle obstacle) {
  return obstacle.GetObstacleXPosition() < 0;
}

}  // namespace flappybird

