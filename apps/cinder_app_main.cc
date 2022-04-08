#include "flappybird_simulation_app.h"

using flappybird::FlappyBirdApp;

void prepareSettings(FlappyBirdApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(FlappyBirdApp, ci::app::RendererGl, prepareSettings);
