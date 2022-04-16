#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace flappybird {

class Obstacle {
public:
  Obstacle(int window_size_x, int window_size_y, int game_mode);
  Obstacle(int window_size_x, int window_size_y, int game_mode, ci::vec2 obstacle_top_left, ci::vec2 obstacle_bottom_left);
  void Draw() const;
  void AdvanceOneFrame();

  double GenerateRandomDouble(const double& min, const double& max);

  double GetObstacleXPosition() const;
  ci::Rectf GetTopObstacleHitBox() const;
  ci::Rectf GetBottomObstacleHitBox() const;

  bool HasPassed() const;
  void UpdateHasPassed();

  int GetGameMode() const;
  double GetMovingSpeed() const;
  double GetGapWidth() const;

  ci::vec2 GetObstacleTopLeft() const;
  ci::vec2 GetObstacleBottomRight() const;

private:
  int kWindowSizeX;
  int kWindowSizeY;

  int game_mode_;
  bool has_passed;
  double moving_speed_;

  ci::vec2 lid_dimension_ = ci::vec2(244 / 2, 113 / 2);
  double pipe_width_ = double(244) / 3;
  double gap_width_;

  ci::gl::Texture2dRef obstacle_top_lid_;
  ci::gl::Texture2dRef obstacle_top_pipe_;
  ci::gl::Texture2dRef obstacle_bottom_lid_;
  ci::gl::Texture2dRef obstacle_bottom_pipe_;

  ci::vec2 top_lid_top_left_;
  ci::vec2 top_lid_bottom_right;

  ci::vec2 top_pipe_top_left_;
  ci::vec2 top_pipe_bottom_right;

  ci::vec2 bottom_lid_top_left_;
  ci::vec2 bottom_lid_bottom_right;

  ci::vec2 bottom_pipe_top_left_;
  ci::vec2 bottom_pipe_bottom_right;

  void InitializeGameMode();
  void InitializeObstaclePosition();
};

}  // namespace flappybird
