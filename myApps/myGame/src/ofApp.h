#pragma once

#include "Bullet.h"
#include "Enemy.h"
#include "LevelController.h"
#include "Life.h"
#include "Player.h"
#include "ofMain.h"

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);
  void update_bullets();

  string game_state;
  int score;
  Player player_1;
  vector<Bullet> bullets;

  ofImage player_image;
  ofImage enemy_bullet_image;
  ofImage player_bullet_image;

};
