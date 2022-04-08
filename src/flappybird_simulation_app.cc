#include "flappybird_simulation_app.h"

namespace flappybird {

FlappybirdApp::FlappybirdApp() {
  ci::app::setWindowSize(kWindowSizeX, kWindowSizeY);
}

void FlappybirdApp::draw() {
  ci::Color background_color("white");
  ci::gl::clear(background_color);

//  ci::Url kBirdImagePath = ci::Url("https://www.pngkey.com/maxpic/u2t4u2e6i1w7w7e6/");
//  ci::gl::Texture2dRef image = ci::gl::Texture2d::create(loadImage(loadUrl(kBirdImagePath)));
  ci::gl::Texture2dRef images = ci::gl::Texture2d::create(ci::loadImage(loadAsset("obstacle_bottom_body.png")));
  ci::gl::Texture2dRef lid = ci::gl::Texture2d::create(ci::loadImage(loadAsset("obstacle_bottom_lid.png")));
//  auto img = ci::loadImage( loadAsset("../../../../../../assets/obstacle.png") );
//  auto mTex = ci::gl::Texture2d::create( img );
//
  ci::Rectf limit1 = ci::Rectf(vec2(100, 200), vec2(220,360));
  ci::Rectf lid1 = ci::Rectf(vec2(80, 150), vec2(240,200));
  ci::Rectf limit2 = ci::Rectf(vec2(300, 200), vec2(420,480));
  ci::Rectf lid2 = ci::Rectf(vec2(280, 150), vec2(440,200));
  ci::Rectf limit3 = ci::Rectf(vec2(500, 200), vec2(620,600));
  ci::Rectf lid3 = ci::Rectf(vec2(480, 150), vec2(640,200));

  ci::gl::draw(images, limit1);
  ci::gl::draw(lid, lid1);
  ci::gl::draw(images, limit2);
  ci::gl::draw(lid, lid2);
  ci::gl::draw(images, limit3);
  ci::gl::draw(lid, lid3);
  // container_.Display();
}

void FlappybirdApp::update() {
  // container_.AdvanceOneFrame();
}

void FlappybirdApp::keyDown(ci::app::KeyEvent event) {

}

}  // namespace flappybird

