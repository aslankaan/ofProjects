#include "Player.h"

void Player::setup(ofImage* _img) {
  img = _img;
  pos = ofPoint(ofGetWidth() / 2, ofGetHeight() - 50);
  img->resize(100, 75);
  width = img->getWidth();
  height = img->getHeight();
  speed = 5;
  lives = 5;
}
void Player::update() {
  if(is_right_pressed){
    pos.x += speed;
    if(pos.x > ofGetWidth()){
      pos.x = 0;
    }
  }
  if(is_left_pressed){
    pos.x -= speed;
    if(pos.x < 0){
      pos.x = ofGetWidth();
    }
  }
}
void Player::draw() {
  
  img->draw(pos.x - width / 2, pos.y - width / 2);
}

void Player::shoot() {}

void Player::calculate_movement() {}

bool Player::check_can_shoot() {}