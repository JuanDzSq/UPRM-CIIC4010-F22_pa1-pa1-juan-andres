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
		int number = 0;
		bool pause = false;
		string velocityMode = "None";
		int n;
		int d=1;
		int a=1;

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
