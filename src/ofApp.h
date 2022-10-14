#pragma once

#include "ofMain.h"
#include "Particle.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void resetParticles();
		void keyPressed  (int key);
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
		
		particleMode currentMode;
		string currentModeStr; 
		bool colorChange;
		int colorCounter= 0;
		bool pause;
		
		
		bool recording;
		bool replaying;
		bool replayLock = false;
		string rcrd;
		vector <int> keys;
		vector <int> newinput;
		int giveInput(vector <int> input);
		int counter = 1;

		string velocityMode;
		int n;
		int doubled=1;
		int halved=1;

		// Rectangle feature properties declartation -------------
		ofRectangle rect;
		ofRectangle particleRectBorder;
		glm::vec3 rectBorder1;
		glm::vec3 rectBorder2;
		glm::vec3 rectStartPoint;
		// -------------------------------------------------------

		vector <Particle> p;
		vector <glm::vec3> attractPoints;
		vector <glm::vec3> attractPointsWithMovement;
		
};