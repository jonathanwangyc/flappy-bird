#pragma once

#include "bird.h"
#include "obstacle.h"

namespace flappybird {

class GameEngine {
public:
  GameEngine(int window_size_x, int window_size_y);
  void Display() const;
  void DisplayObjects() const;
  void DisplayScore() const;
  void DisplayStartingScreen() const;
  void DisplayEndingScreen() const;
  void AdvanceOneFrame();

  int GetScore();
  int GetGameStatus();
  void SetGameStatus(int status);
  int GetGameMode();

  void SetGameModeEasy();
  void SetGameModeNormal();
  void SetGameModeHard();
  void StartGame();
  void ResetGame();

  void ExecuteBirdAction();

  const int kWindowSizeX;
  const int kWindowSizeY;

private:
  int game_status_;
  int game_mode_;
  int obstacle_frequency_;
  int frame_count_;
  Bird bird_;
  std::vector<Obstacle> obstacles_;

  std::vector<int> highest_score_;
  int score_;

  bool IsOutOfBound(Obstacle obstacle);
  void UpdateScore();
};

}  // namespace flappybird