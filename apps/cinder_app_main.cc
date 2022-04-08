#include "flappybird_simulation_app.h"

using flappybird::FlappybirdApp;

void prepareSettings(FlappybirdApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(FlappybirdApp, ci::app::RendererGl, prepareSettings);
