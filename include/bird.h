#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "obstacle.h"

namespace flappybird {

class Bird {
public:
  Bird(int window_size_x, int window_size_y);
  void Draw() const;
  void AdvanceOneFrame();
  void Fly();

  bool HasFall() const;
  bool HasCollide(std::vector<Obstacle> obstacles) const;

  void ResetPosition();
  double GetBirdXPosition();

  void SetGravityMultiplier(double multiplier);

  const int kWindowSizeX;
  const int kWindowSizeY;

  const double kBirdWidth = 51.1;
  const double kBirdHeight = 36.1;

  const double kGravity = 2.65;
  const double kJumpSpace = 95;

private:
  ci::gl::Texture2dRef flappy_bird_;

  ci::vec2 bird_top_left_;
  ci::vec2 bird_bottom_right;

  double gravity_multiplier_ = 1.0;
};

}  // namespace flappybird
