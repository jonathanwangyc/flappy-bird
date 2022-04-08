#pragma once

#include <queue>
#include "bird.h"
#include "obstacle.h"

namespace flappybird {

class GameEngine {
public:
  GameEngine();
  void Display() const;
  void AdvanceOneFrame();

  int GetGameStatus();
private:
  int game_status_;
  Bird bird;
  std::queue<Obstacle> obstacles;
};

}  // namespace flappybird