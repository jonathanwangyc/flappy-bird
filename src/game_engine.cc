#include "game_engine.h"

namespace flappybird {

GameEngine::GameEngine() {
  game_status_ = 0;
  bird = Bird();
  obstacles.push(Obstacle());
}

void GameEngine::Display() const {
  bird.Draw();

  std::queue<Obstacle> obstacles_copy = obstacles;
  while (!obstacles_copy.empty())
  {
    obstacles_copy.front().Draw();
    obstacles_copy.pop();
  }
}

void GameEngine::AdvanceOneFrame() {

}

int GameEngine::GetGameStatus() {
  return game_status_;
}

}  // namespace flappybird

