// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>

#include "CinderImGui.h"




namespace myapp {

using cinder::app::KeyEvent;
using cinder::loadImage;
using cinder::Color;

MyApp::MyApp() {
  card_texture_ = cinder::gl::Texture::create(loadImage("/home/ayman/Cinder/my-projects/final-project-ayman-charafeddine/assets/cards/back-red-75-1.png"));
}

void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  ImGui::initialize();
}

void MyApp::update() {
  if (card_pos_change_ < 250.0f) {
    card_pos_change_ += 10.0f;
  } else {
    card_pos_change_ = 0;
    cards_dealt_++;
  }
}

void MyApp::draw() {
  cinder::gl::clear(Color(0.04f, 0.42f, 0));
  ImGui::Text("Hello, world!");
  DrawDealing();
}

void MyApp::keyDown(KeyEvent event) { }

void MyApp::DrawDealing() {
  cinder::gl::draw(card_texture_, getWindowCenter());

  cinder::gl::pushModelView();
  if (cards_dealt_ >= 0 && cards_dealt_ < 13) {
    cinder::gl::translate((getWindowCenter().x - card_pos_change_), getWindowCenter().y);
  } else if (cards_dealt_ >= 13 && cards_dealt_ < 26) {
    cinder::gl::translate((getWindowCenter().x), getWindowCenter().y - card_pos_change_);
  } else if (cards_dealt_ >= 26 && cards_dealt_ < 39) {
    cinder::gl::translate((getWindowCenter().x + card_pos_change_), getWindowCenter().y);
  } else if (cards_dealt_ >= 39 && cards_dealt_ < 52) {
    cinder::gl::translate((getWindowCenter().x), getWindowCenter().y  + card_pos_change_);
  }
  cinder::gl::rotate(float(getElapsedSeconds() * 8.0));
  cinder::gl::translate(-37.5f, -53.5f);
  cinder::gl::draw(card_texture_);
  cinder::gl::popModelView();
}

}  // namespace myapp
