#include "bird.h"

using cinder::vec2;

namespace flappybird {

Bird::Bird() {
  flappy_bird_ = ci::gl::Texture2d::create(loadImage(ci::app::loadAsset("flappy_bird.png")));
}

void Bird::Draw() const {
  ci::gl::draw(flappy_bird_, ci::Rectf(vec2(700, 200), vec2(950,380)));
}

}  // namespace flappybird

