#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  game_state = "start";
  score = 0;

  player_image.load("images/player.png");

  player_1.setup(&player_image);

  enemy_bullet_image.load("images/enemy_bullet.png");
  player_bullet_image.load("images/player_bullet.png");
}

//--------------------------------------------------------------
void ofApp::update() {
  if (game_state == "start") {
  } else if (game_state == "game") {
    player_1.update();
    update_bullets();
  } else if (game_state == "end") {
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  if (game_state == "start") {
  } else if (game_state == "game") {
    ofBackground(0, 0, 0);
    player_1.draw();
    for (int i = 0; i < bullets.size(); i++) {
      bullets[i].draw();
    }
  } else if (game_state == "end") {
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (game_state == "game") {
    if (key == OF_KEY_LEFT) {
      player_1.is_left_pressed = true;
    }

    if (key == OF_KEY_RIGHT) {
      player_1.is_right_pressed = true;
    }

    if (key == OF_KEY_UP) {
      player_1.is_up_pressed = true;
    }

    if (key == OF_KEY_DOWN) {
      player_1.is_down_pressed = true;
    }
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
  if (game_state == "start") {
    game_state = "game";
  } else if (game_state == "game") {
    if (key == OF_KEY_LEFT) {
      player_1.is_left_pressed = false;
    }

    if (key == OF_KEY_RIGHT) {
      player_1.is_right_pressed = false;
    }

    if (key == OF_KEY_UP) {
      player_1.is_up_pressed = false;
    }

    if (key == OF_KEY_DOWN) {
      player_1.is_down_pressed = false;
    }

    if (key == ' ') {
      Bullet b;
      b.setup(true, player_1.pos, player_1.speed, &player_bullet_image);
      bullets.push_back(b);
    }
  }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}

void ofApp::update_bullets() {
  for (int i = 0; i < bullets.size(); i++) {
    bullets[i].update();
    if (bullets[i].pos.y - bullets[i].width / 2 < 0 ||
        bullets[i].pos.y + bullets[i].width / 2 > ofGetHeight()) {
      bullets.erase(bullets.begin() + i);
    }
  }
  // we'll call a collision check function here shortly
}