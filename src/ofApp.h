#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define PORT 12345
#define BUFFER_SIZE 256
#define NUM_WINDOWS 80


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void easing(float easing);
		void runCoords(int i, int coordNum);
		void audioReceived(float * input, int bufferSize, int nChannels);
		float distVal(int pixY, int pixX);

		int pixCount, moveNum;
		int coordNum = 0;
		int maxDist = 3;
		int scalar = 220;

		float angle;
		float ease = 0.004;
		float speed = 0.03;

		//Audio Variables
		float inputSignal = 0;
		float smoothedValue, deltaValue;
		float outputValue;

		float sumOutput, rms, avgRms, smoothness = 0.7;

		vector <ofVec2f> pos, target, coords;

		bool resetOn;
		ofShader shader;
		ofxOscReceiver oscRetreive;
		int currentTweetNum;
		string tweetCol;

	private:
		float * left;
		float * right;
		int 	bufferCounter;

		float magnitude[BUFFER_SIZE];
		float phase[BUFFER_SIZE];
		float power[BUFFER_SIZE];

		float freq[NUM_WINDOWS][BUFFER_SIZE / 2];
		float freq_phase[NUM_WINDOWS][BUFFER_SIZE / 2];
		
};