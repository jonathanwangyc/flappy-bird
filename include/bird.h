#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace flappybird {

class Bird {
public:
  Bird();
  void Draw() const;

private:
  ci::gl::Texture2dRef flappy_bird_;
};

}  // namespace flappybird
