#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace flappybird {

/*
 * A class that stores an obstacle object and handles the initialization, position, and drawing of it.
 */
class Obstacle {
public:
  /**
   * Constructor that initializes the position of the obstacle.
   * @param window_size_x the pop-up window width
   * @param window_size_y the pop-up window height
   * @param game_mode the current game mode (easy, normal, hard)
   */
  Obstacle(int window_size_x, int window_size_y, int game_mode);

  /**
   * Constructor for the purpose of testing.
   */
  Obstacle(int window_size_x, int window_size_y, int game_mode, ci::vec2 obstacle_top_left, ci::vec2 obstacle_bottom_left);

  /**
   * Draw the obstacle object onto the pop-up window.
   */
  void Draw() const;

  /**
   * Updates the obstacle's position after one unit of time.
   */
  void AdvanceOneFrame();

  /**
   * Generates a random double given minimum and maximum value.
   * @param min minimum value
   * @param max maximum value
   * @return a random value between the constraints
   */
  double GenerateRandomDouble(const double& min, const double& max);

  /**
   * Gets the x-axis coordinate of the obstacle.
   */
  double GetObstacleXPosition() const;

  /**
   * Gets the hit box of the top part of the obstacle.
   */
  ci::Rectf GetTopObstacleHitBox() const;

  /**
   * Gets the hit box of the bottom part of the obstacle.
   */
  ci::Rectf GetBottomObstacleHitBox() const;

  /**
   * Checks if the obstacle has passed the bird object.
   * @return true if it does
   */
  bool HasPassed() const;

  /**
   * Negates the boolean value of has_passed_.
   */
  void UpdateHasPassed();

  /**
   * Getter for game_mode_ for the purpose of testing.
   */
  int GetGameMode() const;

  /**
   * Getter for moving_speed_ for the purpose of testing.
   */
  double GetMovingSpeed() const;

  /**
   * Getter for gap_width_ for the purpose of testing.
   */
  double GetGapWidth() const;

  /**
   * Getter for top_lid_top_left_ for the purpose of testing.
   */
  ci::vec2 GetObstacleTopLeft() const;

  /**
   * Getter for top_lid_bottom_right for the purpose of testing.
   */
  ci::vec2 GetObstacleBottomRight() const;

private:
  int kWindowSizeX; /// the pop-up window width
  int kWindowSizeY; /// the pop-up window height
  int game_mode_; /// current game mode
  bool has_passed_; /// indicate if the obstacle has passed the bird
  double moving_speed_; /// the moving speed of the obstacle
  double pipe_width_ = double(244) / 3; /// the width of the pipe obstacle
  double gap_width_; /// the gap between top and bottom obstacle
  ci::vec2 lid_dimension_ = ci::vec2(244 / 2, 113 / 2); /// the width and height of the lid obstacle

  ci::gl::Texture2dRef obstacle_top_lid_; /// the image of top lid obstacle
  ci::gl::Texture2dRef obstacle_top_pipe_; /// the image of top pipe obstacle
  ci::gl::Texture2dRef obstacle_bottom_lid_; /// the image of bottom lid obstacle
  ci::gl::Texture2dRef obstacle_bottom_pipe_; /// the image of bottom pipe obstacle

  ci::vec2 top_lid_top_left_; /// the position of top lid obstacle
  ci::vec2 top_lid_bottom_right_; /// the position of top lid obstacle
  ci::vec2 top_pipe_top_left_; /// the position of top pipe obstacle
  ci::vec2 top_pipe_bottom_right_; /// the position of top pipe obstacle
  ci::vec2 bottom_lid_top_left_; /// the position of bottom lid obstacle
  ci::vec2 bottom_lid_bottom_right_; /// the position of bottom lid obstacle
  ci::vec2 bottom_pipe_top_left_; /// the position of bottom pipe obstacle
  ci::vec2 bottom_pipe_bottom_right_; /// the position of bottom pipe obstacle

  /**
   * Initializes moving_speed_, gap_width_ based on different game mode.
   */
  void InitializeGameMode();

  /**
   * Randomly initializes the position of the different components of the obstacle.
   */
  void InitializeObstaclePosition();
};

}  // namespace flappybird
