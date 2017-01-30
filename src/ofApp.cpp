/*References for:
	OSC Messages = https://github.com/lian/ofx-dev/blob/master/addons/ofxOsc/examples/oscReceiveExample/src/testApp.cpp

*/
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(40);
	ofBackground(0);

	for (int i = 0; i < currentTweetNum; i++) {
		
	}

	srand((unsigned int)time((time_t *)NULL));

	// 0 output channels,
	// 2 input channels
	// 44100 samples per second
	// BUFFER_SIZE samples per buffer
	// 4 num buffers (latency)

	left = new float[BUFFER_SIZE];
	right = new float[BUFFER_SIZE];

	for (int i = 0; i < NUM_WINDOWS; i++)
	{
		for (int j = 0; j < BUFFER_SIZE / 2; j++)
		{
			freq[i][j] = 0;
		}
	}

	ofSoundStreamSetup(0, 2, this, 44100, BUFFER_SIZE, 4);

	shader.load("vertShader.vert", "fragShader.frag");

	cout << " listening for osc on port:" << PORT << "\n";
	oscRetreive.setup(PORT);



}

//--------------------------------------------------------------
void ofApp::update(){

	angle += speed;
	easing(ease);
	//shaderVis();

	sumOutput = 0;

	for (int i = 0; i < BUFFER_SIZE - 1; i++) {
		outputValue = inputSignal;
		sumOutput += outputValue * outputValue;
	}

	rms = sqrt(sumOutput);

	avgRms *= smoothness;
	avgRms += ((1 - smoothness) * rms) / 4; //We minus smoothness from 1 as we always want a value under 1;

	// check for waiting messages

	while (oscRetreive.hasWaitingMessages())
	{
		// get the next message
		ofxOscMessage m;
		oscRetreive.getNextMessage(&m);

		if (m.getAddress() == "/tweetStreamCol")
		{
			tweetCol = m.getArgAsString(0);
			cout << "Tweet Color: " << tweetCol << endl;
		}

		if (m.getAddress() == "/tweetStreamNum")
		{
			currentTweetNum = m.getArgAsInt(0);

			coords.push_back(ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2));
			pos.push_back(ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2));
			target.push_back(ofVec2f(ofGetWidth() / 2, ofGetHeight()) / 2);
			
			cout << "Tweet Count: "<< currentTweetNum << endl;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	shader.begin();

	for (int i = 0; i < currentTweetNum; i++) {
		runCoords(i, coordNum);
		target[i] = coords[i];
		shader.setUniform2f("vecPos" + to_string(i), pos[i]);
		shader.setUniform2f("windowSize", ofGetWidth(), ofGetHeight());
		ofDrawCircle(pos[i].x, pos[i].y, 2 + avgRms, 2 +avgRms);
	}

	shader.end();

}

void ofApp::runCoords(int i, int coordNum) {
	switch (coordNum) {
	case 0: coords[i] = ofVec2f(
		ofGetWidth() / 2 + (scalar * cos(ofDegToRad(angle * (i + 10)))),
		ofGetHeight() / 2 + (scalar * sin(ofDegToRad(angle)) * cos(ofDegToRad(angle * (i + 10)
		)))
	);
		break;
	case 1: coords[i] = ofVec2f(
		ofGetWidth() / 2 + (scalar * cos(ofDegToRad(angle * (i + 10)) + cos(ofDegToRad(angle * (i + 10))))),
		ofGetHeight() / 2 + (scalar * sin(ofDegToRad(angle * (i + 10))) * cos(ofDegToRad(angle)))
	);
		break;
	case 2: coords[i] = ofVec2f(
		ofGetWidth() / 2 + (scalar * cos(ofDegToRad(angle * (i + 10)))),
		ofGetHeight() / 2 + (scalar * sin(ofDegToRad(angle * (i + 10))))
	);
		break;
	case 3: coords[i] = ofVec2f(
		ofGetWidth() / 2 + (scalar * cos(ofDegToRad(angle * i ) + cos(ofDegToRad(angle * (i + 10))))),
		ofGetHeight() / 2 + (scalar * sin(ofDegToRad(angle * (i + 10))) * cos(ofDegToRad(angle + (i*i) / 10
		)))
	);
		break;
	default:
		coords[i] = ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);
		break;
	}

}

void ofApp::easing(float easing) {
	for (int i = 0; i < currentTweetNum; i++) {
		float dx = target[i].x - pos[i].x;
		pos[i].x += dx * easing * (i + 10);
		float dy = target[i].y - pos[i].y;
		pos[i].y += dy * easing * (i + 10);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case '1':
		coordNum = 0;
		break;
	case '2':
		coordNum = 1;
		break;
	case '3':
		coordNum = 2;
		break;
	case '4':
		coordNum = 3;
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//Reference: https://forum.openframeworks.cc/t/audio-input-fft-example/186 example code found in one of the last posts by 'grimus'

void ofApp::audioReceived(float * input, int bufferSize, int nChannels) {
	// samples are "interleaved"
	for (int i = 0; i < bufferSize; i++) {
		left[i] = input[i * 2];
		//right[i] = input[i * 2 + 1];
		inputSignal = left[i] * 10;
	}
	bufferCounter++;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
