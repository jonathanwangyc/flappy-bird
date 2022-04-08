#include "bird.h"

using cinder::vec2;

namespace flappybird {

Bird::Bird(int window_size_x, int window_size_y) : kWindowSizeX(window_size_x), kWindowSizeY(window_size_y) {
  flappy_bird_ = ci::gl::Texture2d::create(loadImage(ci::app::loadAsset("flappy_bird.png")));

  bird_top_left_ = vec2(kWindowSizeX/2 - kBirdWidth/2, kWindowSizeY/2 - kBirdHeight/2);
  bird_bottom_right = vec2(kWindowSizeX/2 + kBirdWidth/2, kWindowSizeY/2 + kBirdHeight/2);
}

void Bird::Draw() const {
  ci::gl::draw(flappy_bird_, ci::Rectf(bird_top_left_, bird_bottom_right));
}

void Bird::AdvanceOneFrame() {
  bird_top_left_ += vec2(0, kGravity);
  bird_bottom_right += vec2(0, kGravity);
}

void Bird::Fly() {
  bird_top_left_ -= vec2(0, kJumpSpace);
  bird_bottom_right -= vec2(0, kJumpSpace);
}

}  // namespace flappybird

