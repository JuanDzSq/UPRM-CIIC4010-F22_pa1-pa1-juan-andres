#pragma once

#include "ofMain.h"
#include "Particle.h"
#include <vector>
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void resetParticles();
		void replayMode(vector <int>storedKeys);
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
		int number = 0;
		bool pause;
		bool recording;
		bool replaying;
		string rcrd;
		string velocityMode;
		int n;
		int d=1;
		int a=1;
		int count;

		vector <Particle> p;
		vector <glm::vec3> attractPoints;
		vector <glm::vec3> attractPointsWithMovement;
		vector <int>keys;

		
};


