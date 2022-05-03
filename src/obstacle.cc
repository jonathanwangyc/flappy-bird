#include "obstacle.h"

#include <random>

using cinder::vec2;

namespace flappybird {

Obstacle::Obstacle(int window_size_x, int window_size_y, int game_mode) :
    kWindowSizeX(window_size_x), kWindowSizeY(window_size_y) {
  // load in the image of different components of the obstacle
  obstacle_top_lid_ = ci::gl::Texture2d::create(loadImage(ci::app::loadAsset("obstacle_top_lid.png")));
  obstacle_top_pipe_ = ci::gl::Texture2d::create(loadImage(ci::app::loadAsset("obstacle_top_pipe.png")));
  obstacle_bottom_lid_ = ci::gl::Texture2d::create(loadImage(ci::app::loadAsset("obstacle_bottom_lid.png")));
  obstacle_bottom_pipe_ = ci::gl::Texture2d::create(loadImage(ci::app::loadAsset("obstacle_bottom_pipe.png")));

  game_mode_ = game_mode;
  has_passed_ = false;
  InitializeGameMode();
  InitializeObstaclePosition();
}

Obstacle::Obstacle(int window_size_x, int window_size_y, int game_mode, ci::vec2 obstacle_top_left,
                   ci::vec2 obstacle_bottom_right) : kWindowSizeX(window_size_x), kWindowSizeY(window_size_y) {
  top_lid_top_left_ = obstacle_top_left;
  top_lid_bottom_right_ = obstacle_bottom_right;
  game_mode_ = game_mode;
  has_passed_ = false;
  InitializeGameMode();
}

void Obstacle::Draw() const {
  // draw all the different components of the obstacle
  ci::gl::draw(obstacle_top_lid_, ci::Rectf(top_lid_top_left_, top_lid_bottom_right_));
  ci::gl::draw(obstacle_top_pipe_, ci::Rectf(top_pipe_top_left_, top_pipe_bottom_right_));
  ci::gl::draw(obstacle_bottom_lid_, ci::Rectf(bottom_lid_top_left_, bottom_lid_bottom_right_));
  ci::gl::draw(obstacle_bottom_pipe_, ci::Rectf(bottom_pipe_top_left_, bottom_pipe_bottom_right_));
}

void Obstacle::AdvanceOneFrame() {
  top_lid_top_left_ -= vec2(moving_speed_, 0); // moves the obstacle's position (for all components) after one frame
  top_lid_bottom_right_ -= vec2(moving_speed_, 0);

  top_pipe_top_left_ -= vec2(moving_speed_, 0);
  top_pipe_bottom_right_ -= vec2(moving_speed_, 0);

  bottom_lid_top_left_ -= vec2(moving_speed_, 0);
  bottom_lid_bottom_right_ -= vec2(moving_speed_, 0);

  bottom_pipe_top_left_ -= vec2(moving_speed_, 0);
  bottom_pipe_bottom_right_ -= vec2(moving_speed_, 0);
}

void Obstacle::InitializeGameMode() {
  // game mode 1 (easy): slower speed, wider gap
  // game mode 2 (normal): normal speed, gap
  // game mode 3 (hard): faster speed, smaller gap
  switch (game_mode_) {
    case 1:
      moving_speed_ = 2.0;
      gap_width_ = 216 / 1.0;
      break;
    case 2:
      moving_speed_ = 2.5;
      gap_width_ = 216 / 1.2;
      break;
    case 3:
      moving_speed_ = 3.0;
      gap_width_ = 216 / 1.4;
      break;
  }
}

// code below is derived from:
// https://www.delftstack.com/howto/cpp/how-to-generate-random-doubles-cpp/
double Obstacle::GenerateRandomDouble(const double& min, const double& max) {
  std::random_device rd; // random seed
  std::default_random_engine eng(rd()); // initialize a random number generator engine
  std::uniform_real_distribution<double> distribution(min, max);
  return distribution(eng);
}

void Obstacle::InitializeObstaclePosition() {
  // limit the possible starting y-axis coordinate for the gap, and generates a random value from that constraint
  // ex. if deviation is 150, the top obstacle ranges from (0, 150), the bottom ranges from (150 + gap width, kWindowSizeY)
  double deviation = GenerateRandomDouble(2 * lid_dimension_.y, kWindowSizeY - 3 * lid_dimension_.y);

  // initialize the position of all components of obstacle using window size, pipe width, lid dimension, and deviation
  top_lid_top_left_ = vec2(kWindowSizeX, deviation - lid_dimension_.y);
  top_lid_bottom_right_ = top_lid_top_left_ + lid_dimension_;

  top_pipe_top_left_ = vec2(kWindowSizeX + (lid_dimension_.x - pipe_width_) / 2, 0);
  top_pipe_bottom_right_ = vec2(kWindowSizeX + pipe_width_ + (lid_dimension_.x - pipe_width_) / 2, deviation - lid_dimension_.y);

  bottom_lid_top_left_ = vec2(kWindowSizeX, deviation + gap_width_);
  bottom_lid_bottom_right_ = bottom_lid_top_left_ + lid_dimension_;

  bottom_pipe_top_left_ = top_pipe_top_left_ + vec2(0, deviation + gap_width_ + lid_dimension_.y);
  bottom_pipe_bottom_right_ = vec2(kWindowSizeX + pipe_width_  + (lid_dimension_.x - pipe_width_) / 2, kWindowSizeY);
}

double Obstacle::GetObstacleXPosition() const {
  return top_lid_bottom_right_.x;
}

ci::Rectf Obstacle::GetTopObstacleHitBox() const {
  return ci::Rectf(vec2(top_lid_top_left_.x, 0), top_lid_bottom_right_);
}

ci::Rectf Obstacle::GetBottomObstacleHitBox() const {
  return ci::Rectf(bottom_lid_top_left_, vec2(bottom_lid_bottom_right_.x, kWindowSizeY));;
}

bool Obstacle::HasPassed() const {
  return has_passed_;
}

void Obstacle::UpdateHasPassed() {
  has_passed_ = !has_passed_;
}

int Obstacle::GetGameMode() const {
  return game_mode_;
}

double Obstacle::GetMovingSpeed() const {
  return moving_speed_;
}

double Obstacle::GetGapWidth() const {
  return gap_width_;
}

ci::vec2 Obstacle::GetObstacleTopLeft() const {
  return top_lid_top_left_;
}

ci::vec2 Obstacle::GetObstacleBottomRight() const {
  return top_lid_bottom_right_;
}

}  // namespace flappybird
