#include "bird.h"

using cinder::vec2;

namespace flappybird {

Bird::Bird(int window_size_x, int window_size_y) : kWindowSizeX(window_size_x), kWindowSizeY(window_size_y) {
  flappy_bird_ = ci::gl::Texture2d::create(loadImage(ci::app::loadAsset("flappy_bird.png"))); // load the bird image
  gravity_multiplier_ = 1.0;
  bird_top_left_ = vec2(kWindowSizeX/2 - kBirdWidth/2, kWindowSizeY/2 - kBirdHeight/2); // initializes the bird's position
  bird_bottom_right_ = vec2(kWindowSizeX/2 + kBirdWidth/2, kWindowSizeY/2 + kBirdHeight/2);
}

Bird::Bird(int window_size_x, int window_size_y, bool is_test) : kWindowSizeX(window_size_x), kWindowSizeY(window_size_y) {
  gravity_multiplier_ = 1.0;
  bird_top_left_ = vec2(kWindowSizeX/2 - kBirdWidth/2, kWindowSizeY/2 - kBirdHeight/2);
  bird_bottom_right_ = vec2(kWindowSizeX/2 + kBirdWidth/2, kWindowSizeY/2 + kBirdHeight/2);
}

void Bird::Draw() const {
  ci::gl::draw(flappy_bird_, ci::Rectf(bird_top_left_, bird_bottom_right_)); // draw the bird
}

void Bird::AdvanceOneFrame() {
  gravity_multiplier_ += 0.03;
  bird_top_left_ += vec2(0, gravity_multiplier_ * kGravity); // moves the bird's position downward by a value
  bird_bottom_right_ += vec2(0, gravity_multiplier_ * kGravity);
}

void Bird::Fly() {
  bird_top_left_ -= vec2(0, kJumpSpace); // moves the bird's position upward by kJumpSpace
  bird_bottom_right_ -= vec2(0, kJumpSpace);
}

bool Bird::HasFall() const {
  return bird_bottom_right_.y >= kWindowSizeY; // checks if the bird's position exceeds the window screen
}

bool Bird::HasCollide(std::vector<Obstacle> obstacles) const {
  ci::Rectf bird_hit_box = ci::Rectf(bird_top_left_, bird_bottom_right_);
  for (Obstacle& obstacle : obstacles) {
    // checks if the bird's hit box has intersected (collide) with the bit boxes of obstacles
    if (bird_hit_box.intersects(obstacle.GetTopObstacleHitBox()) ||
        bird_hit_box.intersects(obstacle.GetBottomObstacleHitBox())) {
      return true;
    }
  }
  return false;
}

void Bird::ResetPosition() {
  bird_top_left_ = vec2(kWindowSizeX/2 - kBirdWidth/2, kWindowSizeY/2 - kBirdHeight/2);
  bird_bottom_right_ = vec2(kWindowSizeX/2 + kBirdWidth/2, kWindowSizeY/2 + kBirdHeight/2);
}

double Bird::GetBirdXPosition() const {
  return bird_top_left_.x;
}

void Bird::SetGravityMultiplier(double multiplier) {
  gravity_multiplier_ = multiplier;
}

double Bird::GetGravityMultiplier() const {
  return gravity_multiplier_;
}

ci::vec2 Bird::GetBirdTopLeft() const {
  return bird_top_left_;
}

ci::vec2 Bird::GetBirdBottomRight() const {
  return bird_bottom_right_;
}

}  // namespace flappybird
