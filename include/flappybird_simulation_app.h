#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "game_engine.h"

using cinder::vec2;

namespace flappybird {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class FlappybirdApp : public ci::app::App {
public:
  /**
   * Constructor that sets up the window size for the pop-up window and initializes container_.
   */
  FlappybirdApp();

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

  const int kWindowSizeX = 1250; /// The pop-up window width
  const int kWindowSizeY = 775; /// The pop-up window height
  const vec2 kContainerTopLeft = vec2(100, 50); /// the top left coordinate of the container
  const vec2 kContainerBottomRight = vec2(700, 400); /// the bottom right coordinate of the container

private:
  // GasContainer container_; /// A class that stores the particles.
};

}  // namespace flappybird
