#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "obstacle.h"

namespace flappybird {

/*
 * A class that stores the bird object and handles the position, drawing of it.
 */
class Bird {
public:
  /**
   * Constructor that initializes the position of the bird.
   * @param window_size_x the pop-up window width
   * @param window_size_y the pop-up window height
   */
  Bird(int window_size_x, int window_size_y);

  /**
   * Constructor for the purpose of testing.
   */
  Bird(int window_size_x, int window_size_y, bool is_test);

  /**
   * Draw the bird object onto the pop-up window.
   */
  void Draw() const;

  /**
   * Updates the bird's position after one unit of time due to gravity.
   */
  void AdvanceOneFrame();

  /**
   * Updates the bird's position after space bar was pressed.
   */
  void Fly();

  /**
   * Checks if the bird's position is still valid in the window.
   * @return true if bird's position is touching the bottom of screen
   */
  bool HasFall() const;

  /**
   * Checks if the bird has collided with any obstacles.
   * @return true if there's any collision.
   */
  bool HasCollide(std::vector<Obstacle> obstacles) const;

  /**
   * Resets the bird's position to default.
   */
  void ResetPosition();

  /**
   * Gets the x-axis coordinate of the bird.
   */
  double GetBirdXPosition() const;

  /**
   * Sets the value of gravity_multiplier_.
   * @param multiplier the desired value
   */
  void SetGravityMultiplier(double multiplier);

  /**
   * Getter for gravity_multiplier_ for the purpose of testing.
   */
  double GetGravityMultiplier() const;

  /**
   * Getter for bird_top_left_ for the purpose of testing.
   */
  ci::vec2 GetBirdTopLeft() const;

  /**
   * Getter for bird_bottom_right for the purpose of tesiting.
   */
  ci::vec2 GetBirdBottomRight() const;

  const int kWindowSizeX; /// the pop-up window width
  const int kWindowSizeY; /// the pop-up window height
  const double kBirdWidth = 51.1; /// the width of the bird
  const double kBirdHeight = 36.1; /// the height of the bird
  const double kGravity = 2.65; /// a gravity constant
  const double kJumpSpace = 95; /// a constant determines the scale of the jump

private:
  ci::gl::Texture2dRef flappy_bird_; /// the image of the bird
  ci::vec2 bird_top_left_; /// the position of the bird
  ci::vec2 bird_bottom_right_; /// the position of the bird
  double gravity_multiplier_ = 1.0; /// a value mimicking the behavior of gravity
};

}  // namespace flappybird
