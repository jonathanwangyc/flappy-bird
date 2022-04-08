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
        // start the game
        game_engine_.SetGameStatus(1);
        game_engine_.ResetBirdPosition();
      } else if (game_engine_.GetGameStatus() == 1) {
        // flappy bird goes jummppppppp
        game_engine_.MakeBirdFly();
      }
      break;
    case ci::app::KeyEvent::KEY_RETURN:
      if (game_engine_.GetGameStatus() == 2) {
        // go to starting screen
        game_engine_.SetGameStatus(0);
        std::cout << "Game status 1" << std::endl;
        game_engine_.ClearObstacle();
        game_engine_.ResetScore();
      }
      break;
  }
}

}  // namespace flappybird

