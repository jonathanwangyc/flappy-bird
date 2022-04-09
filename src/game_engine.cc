#include "game_engine.h"

namespace flappybird {

GameEngine::GameEngine(int window_size_x, int window_size_y) :
    kWindowSizeX(window_size_x), kWindowSizeY(window_size_y),
    bird_(Bird(kWindowSizeX, kWindowSizeY)) {
  game_status_ = 0;
  frame_count_ = 0;
  highest_score_ = 0;
  score_ = 0;

  obstacles_.push_back(Obstacle(kWindowSizeX, kWindowSizeY));
}

void GameEngine::Display() const {
  for (Obstacle obstacle : obstacles_) {
    obstacle.Draw();
  }
  bird_.Draw();
  // TODO: improve bird falling mechanics. (potentially falling animation), different game mode

  switch (game_status_) {
    case 0:
      DisplayScore();
      DisplayStartingScreen();
      break;
    case 1:
      DisplayScore();
      break;
    case 2:
      DisplayEndingScreen();
      break;
  }
}

void GameEngine::DisplayScore() const {
  ci::gl::drawStringCentered(std::to_string(score_),
                             glm::vec2(kWindowSizeX / 2, 0.12 * kWindowSizeY), ci::Color("white"),
                             ci::Font("Arial Black", 60));
}

void GameEngine::DisplayStartingScreen() const {
  ci::gl::drawStringCentered("Press \"Space\" to start...",
                             glm::vec2(kWindowSizeX / 2, 0.25 * kWindowSizeY), ci::Color("white"),
                             ci::Font("Georgia", 32));
}

void GameEngine::DisplayEndingScreen() const {
  ci::gl::drawSolidRoundedRect(ci::Rectf(glm::vec2(kWindowSizeX / 2 - 125, 0.15 * kWindowSizeY),
                                         glm::vec2(kWindowSizeX / 2 + 125, 0.42 * kWindowSizeY)), 15);
  ci::gl::drawStringCentered("Score: " + std::to_string(score_),
                             glm::vec2(kWindowSizeX / 2, 0.18 * kWindowSizeY), ci::Color("black"),
                             ci::Font("Arial Black", 32));
  ci::gl::drawStringCentered("Best: " + std::to_string(highest_score_),
                             glm::vec2(kWindowSizeX / 2, 0.24 * kWindowSizeY), ci::Color("black"),
                             ci::Font("Arial Black", 32));
  ci::gl::drawStringCentered("Press \"Return\"",
                             glm::vec2(kWindowSizeX / 2, 0.32 * kWindowSizeY), ci::Color("black"),
                             ci::Font("Georgia", 28));
  ci::gl::drawStringCentered("to try again...",
                             glm::vec2(kWindowSizeX / 2, 0.37 * kWindowSizeY), ci::Color("black"),
                             ci::Font("Georgia", 28));
}

void GameEngine::AdvanceOneFrame() {
  frame_count_++;

  bird_.AdvanceOneFrame();

  if (bird_.HasFall() || bird_.HasCollide(obstacles_)) {
    this->SetGameStatus(2);
    if (score_ > highest_score_) {
      highest_score_ = score_;
    }
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

void GameEngine::ResetGravityMultiplier() {
  bird_.SetGravityMultiplier(1.0);
}

}  // namespace flappybird

