#pragma once

#include "bird.h"
#include "obstacle.h"

namespace flappybird {

class GameEngine {
public:
  GameEngine(int window_size_x, int window_size_y);
  void Display() const;
  void AdvanceOneFrame();

  int GetGameStatus();
  void SetGameStatus(int status);
  void MakeBirdFly();

  const int kWindowSizeX;
  const int kWindowSizeY;
private:
  int game_status_;
  const int kObstacleFrequency = 200;
  int frame_count_;
  Bird bird_;
  std::vector<Obstacle> obstacles_;

  bool HasCollide();
  bool IsOutOfBound(Obstacle obstacle);
};

}  // namespace flappybird