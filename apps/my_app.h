// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>

namespace myapp {

enum class PlayerPosition {
  top,
  right,
  bottom,
  left
};

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
 private:
  void DrawDealing();
  cinder::gl::TextureRef card_texture_;
  bool gl_is_rotated_;
  float card_pos_change_;
  size_t cards_dealt_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
