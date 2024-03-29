/*
 * Copyright (c) 2013 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxMidi for documentation
 *
 */
#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

class ofApp : public ofBaseApp, public ofxMidiListener {
 public:
  void setup();
  void update();
  void draw();
  void exit();

  void updateWaveform(int waveformResolution);
  void audioOut(float* output, int bufferSize, int nChannels);

  std::vector<float> waveform;  // this is the lookup table
  double phase;
  float frequency;

  ofMutex waveformMutex;
  ofPolyline waveLine;
  ofPolyline outLine;

  void keyPressed(int key);
  void keyReleased(int key);

  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased();

  void newMidiMessage(ofxMidiMessage& eventArgs);

  ofxMidiIn midiIn;
  std::vector<ofxMidiMessage> midiMessages;
  std::size_t maxMessages = 10;  //< max number of messages to keep track of
};
