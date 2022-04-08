#include "game_engine.h"

namespace flappybird {

GameEngine::GameEngine(int window_size_x, int window_size_y) :
    kWindowSizeX(window_size_x), kWindowSizeY(window_size_y),
    bird_(Bird(kWindowSizeX, kWindowSizeY)) {
  game_status_ = 0;
  frame_count_ = 0;
  score_ = 0;

  obstacles_.push_back(Obstacle(kWindowSizeX, kWindowSizeY));
}

void GameEngine::Display() const {
  for (Obstacle obstacle : obstacles_) {
    obstacle.Draw();
  }
  bird_.Draw();
  // TODO: Implement starting/ending screen

  // make sure the score only show during and after game
  ci::gl::drawStringCentered(
      "Score: " + std::to_string(score_),
      glm::vec2(kWindowSizeX / 2, 30), ci::Color("blue"), ci::Font("Arial Black", 32));
}

void GameEngine::AdvanceOneFrame() {
  frame_count_++;

  bird_.AdvanceOneFrame();

  if (bird_.HasFall() || bird_.HasCollide(obstacles_)) {
    this->SetGameStatus(2);
    std::cout << "Game Stopped!" << std::endl;
  } else {
    for (Obstacle& obstacle : obstacles_) {
      obstacle.AdvanceOneFrame();
    }
    UpdateScore();

    if (IsOutOfBound(obstacles_[0])) {
      obstacles_.erase(obstacles_.begin());
    }
    if (frame_count_ == kObstacleFrequency) {
      frame_count_ %= kObstacleFrequency;
      obstacles_.push_back(Obstacle(kWindowSizeX, kWindowSizeY));
    }

  }
}

int GameEngine::GetScore() {
  return score_;
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

bool GameEngine::IsOutOfBound(Obstacle obstacle) {
  return obstacle.GetObstacleXPosition() < 0;
}

void GameEngine::ClearObstacle() {
  obstacles_.clear();
}

void GameEngine::UpdateScore() {
  for (Obstacle& obstacle : obstacles_) {
    if (!obstacle.HasPassed() && obstacle.GetObstacleXPosition() <= bird_.GetBirdXPosition()) {
      score_++;
      obstacle.UpdateHasPassed();
    }
  }
}

void GameEngine::ResetScore() {
  score_ = 0;
}

void GameEngine::ResetBirdPosition() {
  bird_.ResetPosition();
}

}  // namespace flappybird

