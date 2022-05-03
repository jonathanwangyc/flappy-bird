#include "flappybird_simulation_app.h"

using cinder::vec2;

namespace flappybird {

FlappyBirdApp::FlappyBirdApp() : game_engine_(GameEngine(kWindowSizeX, kWindowSizeY)) {
  ci::app::setWindowSize(kWindowSizeX, kWindowSizeY);
  background = ci::gl::Texture2d::create(loadImage(loadAsset("background.png"))); // load the background image
}

void FlappyBirdApp::draw() {
  ci::gl::clear();
  ci::gl::draw(background, ci::Rectf(vec2(0, 0), vec2(kWindowSizeX,kWindowSizeY))); // draw the background image

  game_engine_.Display();
}

void FlappyBirdApp::update() {
  if (game_engine_.GetGameStatus() == 1) {
    game_engine_.AdvanceOneFrame(); // only advance one frame if the game status is 1 (running)
  }
}

void FlappyBirdApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_SPACE:
      // game status = 0 (starting screen): call StartGame()
      // game status = 1 (running): call ExecuteBirdAction()
      if (game_engine_.GetGameStatus() == 0) {
        game_engine_.StartGame();
      } else if (game_engine_.GetGameStatus() == 1) {
        game_engine_.ExecuteBirdAction();
      }
      break;
    case ci::app::KeyEvent::KEY_RETURN:
      // game status = 2 (ending screen): call ResetGame()
      if (game_engine_.GetGameStatus() == 2) {
        game_engine_.ResetGame();
      }
      break;
    case ci::app::KeyEvent::KEY_1:
      // game status = 0 (starting screen): call SetGameModeEasy()
      if (game_engine_.GetGameStatus() == 0) {
        game_engine_.SetGameModeEasy();
      }
      break;
    case ci::app::KeyEvent::KEY_2:
      // game status = 0 (starting screen): call SetGameModeNormal()
      if (game_engine_.GetGameStatus() == 0) {
        game_engine_.SetGameModeNormal();
      }
      break;
    case ci::app::KeyEvent::KEY_3:
      // game status = 0 (starting screen): call SetGameModeHard()
      if (game_engine_.GetGameStatus() == 0) {
        game_engine_.SetGameModeHard();
      }
      break;
  }
}

}  // namespace flappybird
