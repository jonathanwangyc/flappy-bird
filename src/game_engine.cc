#include "game_engine.h"

namespace flappybird {

GameEngine::GameEngine(int window_size_x, int window_size_y) :
    kWindowSizeX(window_size_x), kWindowSizeY(window_size_y),
    bird_(Bird(kWindowSizeX, kWindowSizeY)) {
  game_status_ = 0;
  frame_count_ = 0;
  highest_score_ = {0, 0, 0, 0};
  score_ = 0;

  this->SetGameModeNormal();
}

GameEngine::GameEngine(int window_size_x, int window_size_y, bool is_test) :
    kWindowSizeX(window_size_x), kWindowSizeY(window_size_y), bird_(Bird(kWindowSizeX, kWindowSizeY, true)) {
  game_status_ = 0;
  frame_count_ = 0;
  highest_score_ = {0, 0, 0, 0};
  score_ = 0;

  obstacle_frequency_ = 180;
  game_mode_ = 2;
}

void GameEngine::Display() const {
  DisplayObjects();
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

void GameEngine::DisplayObjects() const {
  for (Obstacle obstacle : obstacles_) {
    obstacle.Draw();
  }
  bird_.Draw();
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
  ci::gl::drawStringCentered("Press 1, 2, 3 to change difficulty",
                             glm::vec2(kWindowSizeX / 2, 0.30 * kWindowSizeY), ci::Color("white"),
                             ci::Font("Georgia", 16));
  switch(game_mode_) {
    case 1:
      ci::gl::drawString("Mode: EASY", glm::vec2(0.05 * kWindowSizeX, 0.05 * kWindowSizeY), ci::Color("white"),
                         ci::Font("Georgia", 20));
      break;
    case 2:
      ci::gl::drawString("Mode: NORMAL", glm::vec2(0.05 * kWindowSizeX, 0.05 * kWindowSizeY), ci::Color("white"),
                         ci::Font("Georgia", 20));
      break;
    case 3:
      ci::gl::drawString("Mode: HARD", glm::vec2(0.05 * kWindowSizeX, 0.05 * kWindowSizeY), ci::Color("white"),
                         ci::Font("Georgia", 20));
      break;
  }
}

void GameEngine::DisplayEndingScreen() const {
  ci::gl::drawSolidRoundedRect(ci::Rectf(glm::vec2(kWindowSizeX / 2 - 125, 0.15 * kWindowSizeY),
                                         glm::vec2(kWindowSizeX / 2 + 125, 0.42 * kWindowSizeY)), 15);
  ci::gl::drawStringCentered("Score: " + std::to_string(score_),
                             glm::vec2(kWindowSizeX / 2, 0.18 * kWindowSizeY), ci::Color("black"),
                             ci::Font("Arial Black", 32));
  ci::gl::drawStringCentered("Best: " + std::to_string(highest_score_[game_mode_]),
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
    if (score_ > highest_score_[game_mode_]) {
      highest_score_[game_mode_] = score_;
    }
  } else {
    for (Obstacle& obstacle : obstacles_) {
      obstacle.AdvanceOneFrame();
    }
    UpdateScore();

    if (IsOutOfBound(obstacles_[0])) {
      obstacles_.erase(obstacles_.begin());
    }
    if (frame_count_ == obstacle_frequency_) {
      frame_count_ %= obstacle_frequency_;
      obstacles_.push_back(Obstacle(kWindowSizeX, kWindowSizeY, game_mode_));
    }

  }
}

int GameEngine::GetScore() const {
  return score_;
}

int GameEngine::GetGameStatus() const {
  return game_status_;
}

void GameEngine::SetGameStatus(int status) {
  game_status_ = status;
}

int GameEngine::GetGameMode() const {
  return game_mode_;
}

void GameEngine::SetGameModeEasy() {
  obstacle_frequency_ = 200;
  game_mode_ = 1;
  obstacles_.clear();
  obstacles_.push_back(Obstacle(kWindowSizeX, kWindowSizeY, game_mode_));
}

void GameEngine::SetGameModeNormal() {
  obstacle_frequency_ = 180;
  game_mode_ = 2;
  obstacles_.clear();
  obstacles_.push_back(Obstacle(kWindowSizeX, kWindowSizeY, game_mode_));
}

void GameEngine::SetGameModeHard() {
  obstacle_frequency_ = 160;
  game_mode_ = 3;
  obstacles_.clear();
  obstacles_.push_back(Obstacle(kWindowSizeX, kWindowSizeY, game_mode_));
}

void GameEngine::StartGame() {
  this->SetGameStatus(1);
  bird_.ResetPosition();
  bird_.Fly();
}

void GameEngine::ResetGame() {
  this->SetGameStatus(0);
  obstacles_.clear();
  frame_count_ = 0;
  score_ = 0;
  bird_.SetGravityMultiplier(1.0);
}

void GameEngine::ExecuteBirdAction() {
  bird_.Fly();
  bird_.SetGravityMultiplier(1.0);
}

bool GameEngine::IsOutOfBound(Obstacle obstacle) {
  return obstacle.GetObstacleXPosition() < 0;
}

void GameEngine::UpdateScore() {
  for (Obstacle& obstacle : obstacles_) {
    if (!obstacle.HasPassed() && obstacle.GetObstacleXPosition() <= bird_.GetBirdXPosition()) {
      score_++;
      obstacle.UpdateHasPassed();
    }
  }
}

Bird GameEngine::GetBird() const {
  return bird_;
}

std::vector<Obstacle> GameEngine::GetObstacles() const {
  return obstacles_;
}

void GameEngine::SetObstacles(std::vector<Obstacle> obstacles) {
  obstacles_ = obstacles;
}

std::vector<int> GameEngine::GetHighestScore() const {
  return highest_score_;
}

}  // namespace flappybird
