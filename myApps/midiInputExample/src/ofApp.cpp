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
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetVerticalSync(true);
  ofBackground(255, 255, 255);
  ofSetLogLevel(OF_LOG_VERBOSE);

  phase = 0;
  updateWaveform(32);
  ofSoundStreamSetup(1, 0);  // mono output

  // print input ports to console
  midiIn.listInPorts();

  // open port by number (you may need to change this)
  // midiIn.openPort(1);
  midiIn.openPort("Launchpad S");  // by name
  // midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port

  // don't ignore sysex, timing, & active sense messages,
  // these are ignored by default
  midiIn.ignoreTypes(false, false, false);

  // add ofApp as a listener
  midiIn.addListener(this);

  // print received messages to the console
  midiIn.setVerbose(true);
}

//--------------------------------------------------------------
void ofApp::update() {
  ofScopedLock waveformLock(waveformMutex);
  updateWaveform(ofMap(ofGetMouseX(), 0, ofGetWidth(), 3, 64, true));
  frequency = ofMap(ofGetMouseY(), 0, ofGetHeight(), 60, 700, true);
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(ofColor::black);
    ofSetLineWidth(5);
    ofSetColor(ofColor::lightGreen);
    outLine.draw();
    ofSetColor(ofColor::cyan);
    waveLine.draw();
}

//--------------------------------------------------------------
void ofApp::exit() {
  // clean up
  midiIn.closePort();
  midiIn.removeListener(this);
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage &msg) {
  // add the latest message to the message queue
  midiMessages.push_back(msg);

  if (msg.pitch == 0) {
    if (msg.velocity > 0) {
      ofLog(OF_LOG_WARNING, "0 Pressed");
    } else {
      ofLog(OF_LOG_WARNING, "0 Released");
    }
  }

  // remove any old messages if we have too many
  while (midiMessages.size() > maxMessages) {
    midiMessages.erase(midiMessages.begin());
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  switch (key) {
    case '?':
      midiIn.listInPorts();
      break;
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased() {}


//--------------------------------------------------------------

void ofApp::updateWaveform(int waveformResolution) {
    waveform.resize(waveformResolution);
    waveLine.clear();
    
    // "waveformStep" maps a full oscillation of sin() to the size 
    // of the waveform lookup table
    float waveformStep = (M_PI * 2.) / (float) waveform.size();
    
    for(int i = 0; i < waveform.size(); i++) {
        waveform[i] = sin(i * waveformStep);
        
        waveLine.addVertex(ofMap(i, 0, waveform.size() - 1, 0, ofGetWidth()),
                           ofMap(waveform[i], -1, 1, 0, ofGetHeight()));
    }
}

void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    ofScopedLock waveformLock(waveformMutex);
    
    float sampleRate = 44100;
    float phaseStep = frequency / sampleRate;
    
    outLine.clear();
    
    for(int i = 0; i < bufferSize * nChannels; i += nChannels) {
        phase += phaseStep;
        int waveformIndex = (int)(phase * waveform.size()) % waveform.size();
        output[i] = waveform[waveformIndex];
        
        outLine.addVertex(ofMap(i, 0, bufferSize - 1, 0, ofGetWidth()),
                          ofMap(output[i], -1, 1, 0, ofGetHeight()));
    }
}