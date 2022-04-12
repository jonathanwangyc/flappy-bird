#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "game_engine.h"

namespace flappybird {

class FlappyBirdApp : public ci::app::App {
public:
  /**
   * Constructor that sets up the window size for the pop-up window and initializes game_engine_.
   */
  FlappyBirdApp();

  /**
   * Draw all objects onto the pop-up window.
   */
  void draw() override;

  /**
   * Updates obstacles' positions after one unit of time.
   */
  void update() override;

  /**
   * Triggers different events based on different key pressed.
   * @param event contains information about the key event
   */
  void keyDown(ci::app::KeyEvent event) override;

  const int kWindowSizeX = 1250; /// The pop-up window width
  const int kWindowSizeY = 725; /// The pop-up window height

private:
  GameEngine game_engine_;
  ci::gl::Texture2dRef background;
};

}  // namespace flappybird
