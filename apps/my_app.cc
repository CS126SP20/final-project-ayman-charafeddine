// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>


namespace myapp {

using cinder::app::KeyEvent;
using cinder::loadImage;

MyApp::MyApp() { }

void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  card_texture_ = cinder::gl::Texture::create(loadImage("../assets/cards/back-red-75-1.png"));
}

void MyApp::update() { }

void MyApp::draw() {
  //const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};

}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
