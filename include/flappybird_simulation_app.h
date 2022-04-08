#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "game_engine.h"

namespace flappybird {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class FlappyBirdApp : public ci::app::App {
public:
  /**
   * Constructor that sets up the window size for the pop-up window and initializes container_.
   */
  FlappyBirdApp();

  /**
   * Draw the particles onto the pop-up window.
   */
  void draw() override;

  /**
   * Updates particles' position/velocity after one unit of time.
   */
  void update() override;

  /**
   * Speeds up/down particle velocity based on different key events.
   * @param event contains information about the key event
   */
  void keyDown(ci::app::KeyEvent event) override;

  const int kWindowSizeX = 1550; /// The pop-up window width
  const int kWindowSizeY = 925; /// The pop-up window height

  ci::gl::Texture2dRef background;
  const ci::gl::Texture2dRef kFlappyBird;

private:
  GameEngine game_engine_;
  // container_; /// A class that stores the particles.
};

}  // namespace flappybird
