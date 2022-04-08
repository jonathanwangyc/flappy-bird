#include "obstacle.h"

#include <random>

using cinder::vec2;

namespace flappybird {

Obstacle::Obstacle(int window_size_x, int window_size_y) : kWindowSizeX(window_size_x), kWindowSizeY(window_size_y) {
  obstacle_top_lid_ = ci::gl::Texture2d::create(loadImage(ci::app::loadAsset("obstacle_top_lid.png")));
  obstacle_top_pipe_ = ci::gl::Texture2d::create(loadImage(ci::app::loadAsset("obstacle_top_pipe.png")));
  obstacle_bottom_lid_ = ci::gl::Texture2d::create(loadImage(ci::app::loadAsset("obstacle_bottom_lid.png")));
  obstacle_bottom_pipe_ = ci::gl::Texture2d::create(loadImage(ci::app::loadAsset("obstacle_bottom_pipe.png")));

  InitializeObstaclePosition();
}

void Obstacle::Draw() const {
  ci::gl::draw(obstacle_top_lid_, ci::Rectf(top_lid_top_left_, top_lid_bottom_right));
  ci::gl::draw(obstacle_top_pipe_, ci::Rectf(top_pipe_top_left_, top_pipe_bottom_right));

  ci::gl::draw(obstacle_bottom_lid_, ci::Rectf(bottom_lid_top_left_, bottom_lid_bottom_right));
  ci::gl::draw(obstacle_bottom_pipe_, ci::Rectf(bottom_pipe_top_left_, bottom_pipe_bottom_right));
//  std::cout << "Attempt to draw!" << std::endl;
//  std::cout << top_lid_top_left_ << top_lid_bottom_right << std::endl;
//  std::cout << top_pipe_top_left_ << top_pipe_bottom_right << std::endl;
//  std::cout << bottom_lid_top_left_ << bottom_lid_bottom_right << std::endl;
//  std::cout << bottom_pipe_top_left_ << bottom_pipe_bottom_right << std::endl;

}

void Obstacle::AdvanceOneFrame() {
  top_lid_top_left_-= vec2(moving_speed_, 0);
  top_lid_bottom_right-= vec2(moving_speed_, 0);

  top_pipe_top_left_-= vec2(moving_speed_, 0);
  top_pipe_bottom_right-= vec2(moving_speed_, 0);

  bottom_lid_top_left_-= vec2(moving_speed_, 0);
  bottom_lid_bottom_right-= vec2(moving_speed_, 0);

  bottom_pipe_top_left_-= vec2(moving_speed_, 0);
  bottom_pipe_bottom_right-= vec2(moving_speed_, 0);
}

// code below is derived from:
// https://www.delftstack.com/howto/cpp/how-to-generate-random-doubles-cpp/
double Obstacle::GenerateRandomDouble(const double& min, const double& max) {
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distribution(min, max);
  return distribution(eng);
}

void Obstacle::InitializeObstaclePosition() {
  double deviation = GenerateRandomDouble(2 * lid_dimension_.y, kWindowSizeY - 3 * lid_dimension_.y);

  top_lid_top_left_ = vec2(kWindowSizeX, deviation - lid_dimension_.y);
  top_lid_bottom_right = top_lid_top_left_ + lid_dimension_;

  top_pipe_top_left_ = vec2(kWindowSizeX + (lid_dimension_.x - pipe_width_) / 2, 0);
  top_pipe_bottom_right = vec2(kWindowSizeX + pipe_width_ + (lid_dimension_.x - pipe_width_) / 2, deviation - lid_dimension_.y);

  bottom_lid_top_left_ = vec2(kWindowSizeX, deviation + gap_width_);
  bottom_lid_bottom_right = bottom_lid_top_left_ + lid_dimension_;

  bottom_pipe_top_left_ = top_pipe_top_left_ + vec2(0, deviation + gap_width_ + lid_dimension_.y);
  bottom_pipe_bottom_right = vec2(kWindowSizeX + pipe_width_  + (lid_dimension_.x - pipe_width_) / 2, kWindowSizeY);
}

double Obstacle::GetObstacleXPosition() {
  return top_lid_bottom_right.x;
}

}  // namespace flappybird
