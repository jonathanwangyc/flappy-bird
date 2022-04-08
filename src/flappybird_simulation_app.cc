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

//  ci::gl::Texture2dRef images = ci::gl::Texture2d::create(loadImage(loadAsset("obstacle_bottom_pipe.png")));
//  ci::gl::Texture2dRef lid = ci::gl::Texture2d::create(ci::loadImage(loadAsset("obstacle_bottom_lid.png")));
//
//  ci::Rectf limit1 = ci::Rectf(vec2(100, 200), vec2(220,360));
//  ci::Rectf lid1 = ci::Rectf(vec2(80, 150), vec2(240,200));
//  ci::Rectf limit2 = ci::Rectf(vec2(300, 200), vec2(420,480));
//  ci::Rectf lid2 = ci::Rectf(vec2(280, 150), vec2(440,200));
//  ci::Rectf limit3 = ci::Rectf(vec2(500, 200), vec2(620,600));
//  ci::Rectf lid3 = ci::Rectf(vec2(480, 150), vec2(640,200));
//
//  ci::gl::draw(images, limit1);
//  ci::gl::draw(lid, lid1);
//  ci::gl::draw(images, limit2);
//  ci::gl::draw(lid, lid2);
//  ci::gl::draw(images, limit3);
//  ci::gl::draw(lid, lid3);

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
      } else if (game_engine_.GetGameStatus() == 1) {
        // flappy bird goes jummppppppp
        game_engine_.MakeBirdFly();
      }
      break;
    case ci::app::KeyEvent::KEY_RETURN:
      if (game_engine_.GetGameStatus() == 2) {
        // go to starting screen
        game_engine_.SetGameStatus(0);
      }
      break;
  }
}

}  // namespace flappybird

