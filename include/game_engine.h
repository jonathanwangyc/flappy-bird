#pragma once

#include "bird.h"
#include "obstacle.h"

namespace flappybird {

class GameEngine {
public:
  GameEngine(int window_size_x, int window_size_y);
  GameEngine(int window_size_x, int window_size_y, bool is_test);
  void Display() const;
  void DisplayObjects() const;
  void DisplayScore() const;
  void DisplayStartingScreen() const;
  void DisplayEndingScreen() const;
  void AdvanceOneFrame();

  int GetScore() const;
  int GetGameStatus() const;
  void SetGameStatus(int status);
  int GetGameMode() const;

  void SetGameModeEasy();
  void SetGameModeNormal();
  void SetGameModeHard();
  void StartGame();
  void ResetGame();

  void ExecuteBirdAction();
  void UpdateScore();

  Bird GetBird() const;
  std::vector<Obstacle> GetObstacles() const;
  void SetObstacles(std::vector<Obstacle> obstacles);
  std::vector<int> GetHighestScore() const;

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
};

}  // namespace flappybird