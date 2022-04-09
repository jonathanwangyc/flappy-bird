#pragma once

#include "bird.h"
#include "obstacle.h"

namespace flappybird {

class GameEngine {
public:
  GameEngine(int window_size_x, int window_size_y);
  void Display() const;
  void DisplayScore() const;
  void DisplayStartingScreen() const;
  void DisplayEndingScreen() const;
  void AdvanceOneFrame();

  int GetScore();
  int GetGameStatus();
  void SetGameStatus(int status);

  void MakeBirdFly();
  void ClearObstacle();
  void ResetScore();
  void ResetBirdPosition();
  void ResetGravityMultiplier();

  const int kWindowSizeX;
  const int kWindowSizeY;

private:
  int game_status_;
  const int kObstacleFrequency = 180;
  int frame_count_;
  Bird bird_;
  std::vector<Obstacle> obstacles_;

  int highest_score_;
  int score_;

  bool IsOutOfBound(Obstacle obstacle);
  void UpdateScore();
};

}  // namespace flappybird