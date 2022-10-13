#pragma once
#include "ofMain.h"

enum particleMode{
	PARTICLE_MODE_ATTRACT = 0,
	PARTICLE_MODE_REPEL,
	PARTICLE_MODE_NEAREST_POINTS,
	PARTICLE_MODE_NOISE
};

class Particle{

	public:
		Particle();
		
		void setMode(particleMode newMode);	
		void setColor(bool newColor, int newNumber);			
		void setVelocityChange(string newVelMode, int n);	
		void changeVelocity(string velMode, int n);
		void setNewSize();											
		void setAttractPoints( vector <glm::vec3> * attract );
		void attractToPoint(int, int);
		void repelFromPoint(int, int);
		void reset();
		void update();
		void draw();		
		
		glm::vec3 pos;
		glm::vec3 vel;
		glm::vec3 frc;
		glm::vec3 backup;
		
		float drag; 
		float uniqueVal;
		float scale;
		float newScale = 0;	
		bool color;
		int number;
		int n;
		string velMode;
		particleMode mode;
		
		vector <glm::vec3> * attractPoints; 
};
