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
		void pauseParticle(bool pause2);
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
		bool color;
		int number;
		bool pause;
		particleMode mode;
		
		vector <glm::vec3> * attractPoints; 
};
