#pragma once

#include "bird.h"
#include "obstacle.h"

namespace flappybird {

class GameEngine {
public:
  /**
   * Constructor that initializes all the variables and Bird instance.
   * @param window_size_x the pop-up window width
   * @param window_size_y the pop-up window height
   */
  GameEngine(int window_size_x, int window_size_y);

  /**
   * Constructor for the purpose of testing.
   */
  GameEngine(int window_size_x, int window_size_y, bool is_test);

  /**
   * Draws all the objects onto the pop-up window.
   */
  void Display() const;

  /**
   * Updates the position of Bird, Obstacles, checks for end game condition, and updates the current score.
   */
  void AdvanceOneFrame();

  /**
   * Getter for score_.
   */
  int GetScore() const;

  /**
   * Getter for game_status_.
   */
  int GetGameStatus() const;

  /**
   * Setter for game_status_.
   */
  void SetGameStatus(int status);

  /**
   * Getter for game_mode_.
   */
  int GetGameMode() const;

  /**
   * Adjusts the variables for easy game mode.
   */
  void SetGameModeEasy();

  /**
   * Adjusts the variables for normal game mode.
   */
  void SetGameModeNormal();

  /**
   * Adjusts the variables for hard game mode.
   */
  void SetGameModeHard();

  /**
   * Updates the game status and resets the position of the bird.
   */
  void StartGame();

  /**
   * Resets the variables to the initial values.
   */
  void ResetGame();

  /**
   * Executes the corresponding game logics after space bar was pressed.
   */
  void ExecuteBirdAction();

  /**
   * Loops through the obstacles to update current score.
   */
  void UpdateScore();

  /**
   * Getter for bird_ for the purpose of testing.
   */
  Bird GetBird() const;

  /**
   * Getter for obstacles_ for the purpose of testing.
   */
  std::vector<Obstacle> GetObstacles() const;

  /**
   * Setter for obstacles_ for the purpose of testing.
   */
  void SetObstacles(std::vector<Obstacle> obstacles);

  /**
   * Getter for highest_score_ for the purpose of testing.
   */
  std::vector<int> GetHighestScore() const;

  const int kWindowSizeX; /// the pop-up window width
  const int kWindowSizeY; /// the pop-up window height

private:
  int game_status_; /// current game status (0 starting, 1 running, 2 ending)
  int game_mode_; /// current game mode (1 easy, 2 normal, 3 hard)
  int obstacle_frequency_; /// the frequency of the obstacle
  int frame_count_; /// frame count since the initialization of previous obstacle
  Bird bird_; /// a instance of Bird class
  std::vector<Obstacle> obstacles_; /// all the current instance of Obstacle class
  std::vector<int> highest_score_; /// highest scores for different game modes
  int score_; /// score for current game

  /**
   * Displays the Bird and Obstacles objects onto the window.
   */
  void DisplayObjects() const;

  /**
   * Displays the current score onto the window.
   */
  void DisplayScore() const;

  /**
   * Displays the instructions and current game mode onto the window.
   */
  void DisplayStartingScreen() const;

  /**
   * Displays the score and best score onto the window.
   */
  void DisplayEndingScreen() const;

  /**
   * Checks if the input obstacle's position is to the left of the window.
   * @param obstacle an instance of Obstacle class
   * @return true if the obstacle is out of the screen
   */
  bool IsOutOfBound(Obstacle obstacle);
};

}  // namespace flappybird
