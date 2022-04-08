#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace flappybird {

class Obstacle {
public:
  Obstacle(int window_size_x, int window_size_y);
  void Draw() const;
  void AdvanceOneFrame();

  double GetObstacleXPosition();

private:
  int kWindowSizeX;
  int kWindowSizeY;

  double moving_speed_ = 2.5;

  cinder::vec2 lid_dimension_ = cinder::vec2(244 / 2, 113 / 2);
  double pipe_width_ = double(244) / 3;
  double gap_width_ = 216 / 1.2;

  ci::gl::Texture2dRef obstacle_top_lid_;
  ci::gl::Texture2dRef obstacle_top_pipe_;
  ci::gl::Texture2dRef obstacle_bottom_lid_;
  ci::gl::Texture2dRef obstacle_bottom_pipe_;

  cinder::vec2 top_lid_top_left_;
  cinder::vec2 top_lid_bottom_right;

  cinder::vec2 top_pipe_top_left_;
  cinder::vec2 top_pipe_bottom_right;

  cinder::vec2 bottom_lid_top_left_;
  cinder::vec2 bottom_lid_bottom_right;

  cinder::vec2 bottom_pipe_top_left_;
  cinder::vec2 bottom_pipe_bottom_right;

  double GenerateRandomDouble(const double& min, const double& max);
  void InitializeObstaclePosition();
};

}  // namespace flappybird
