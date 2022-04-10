#include "flappybird_simulation_app.h"

using cinder::vec2;

namespace flappybird {

FlappyBirdApp::FlappyBirdApp() : kFlappyBird(ci::gl::Texture2d::create(loadImage(loadAsset("flappy_bird.png")))),
                                 game_engine_(GameEngine(kWindowSizeX, kWindowSizeY)) {
  ci::app::setWindowSize(kWindowSizeX, kWindowSizeY);
  background = ci::gl::Texture2d::create(loadImage(loadAsset("background.png")));

}

void FlappyBirdApp::draw() {
  ci::gl::clear();
  ci::gl::draw(background, ci::Rectf(vec2(0, 0), vec2(kWindowSizeX,kWindowSizeY)));

  game_engine_.Display();
}

void FlappyBirdApp::update() {
  if (game_engine_.GetGameStatus() == 1) {
    game_engine_.AdvanceOneFrame();
  }
}

void FlappyBirdApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_SPACE:
      if (game_engine_.GetGameStatus() == 0) {
        game_engine_.StartGame();
      } else if (game_engine_.GetGameStatus() == 1) {
        game_engine_.MakeBirdFly();
        game_engine_.ResetGravityMultiplier();
      }
      break;
    case ci::app::KeyEvent::KEY_RETURN:
      if (game_engine_.GetGameStatus() == 2) {
        game_engine_.ResetGame();
      }
      break;
    case ci::app::KeyEvent::KEY_1:
      if (game_engine_.GetGameStatus() == 0) {
        game_engine_.SetGameModeEasy();
      }
      break;
    case ci::app::KeyEvent::KEY_2:
      if (game_engine_.GetGameStatus() == 0) {
        game_engine_.SetGameModeNormal();
      }
      break;
    case ci::app::KeyEvent::KEY_3:
      if (game_engine_.GetGameStatus() == 0) {
        game_engine_.SetGameModeHard();
      }
      break;
  }
}

}  // namespace flappybird

