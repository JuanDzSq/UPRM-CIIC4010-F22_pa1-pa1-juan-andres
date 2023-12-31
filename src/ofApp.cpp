#include "ofApp.h"
#include<iostream>
#include <cstdlib>

using namespace std;


//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	pause = false;
	recording = false;
	replaying = false;
	velocityMode = "None";
	int num = 1500;
	p.assign(num, Particle());
	currentMode = PARTICLE_MODE_ATTRACT;

	currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse"; 

	resetParticles();
}

//--------------------------------------------------------------
void ofApp::resetParticles(){

	//these are the attraction points used in the fourth demo 
	attractPoints.clear();
	for(int i = 0; i < 4; i++){
		attractPoints.push_back( glm::vec3( ofMap(i, 0, 4, 100, ofGetWidth()-100) , ofRandom(100, ofGetHeight()-100) , 0) );
	}
	
	attractPointsWithMovement = attractPoints;
	
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);		
		p[i].setAttractPoints(&attractPointsWithMovement);;
		p[i].reset();
	}	
}

//--------------------------------------------------------------
void ofApp::update(){
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);
		p[i].setColor(colorChange, number);//sets parameters to change the colors
		p[i].setVelocityChange(velocityMode,n); //sets parameters to change the velocity
		if(!pause){p[i].update();} //Triggers particle pause
		
	}
	
	//lets add a bit of movement to the attract points
	for(unsigned int i = 0; i < attractPointsWithMovement.size(); i++){
		attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
		attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
	}	

	counter += 1;

	if(counter % 250 == 0 && replaying == true) {
		replayLock = false;									// The lock gets released so that the replay can make the keyPress
		keyPressed(giveInput(keys));
		replayLock = true;									// This will make it so that the program does not listen to any keys pressed during a replay

		if(newinput.size() == 0){
			replaying = false;
			replayLock = false;
		}

	}
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));

	for(unsigned int i = 0; i < p.size(); i++){
		p[i].draw();
	}
	
	ofSetColor(190);
	if( currentMode == PARTICLE_MODE_NEAREST_POINTS ){
		for(unsigned int i = 0; i < attractPoints.size(); i++){
			ofNoFill();
			ofDrawCircle(attractPointsWithMovement[i], 10);
			ofFill();
			ofDrawCircle(attractPointsWithMovement[i], 4);
		}
	}

	ofSetColor(230);	
	ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode. \nt to change color (red, green, blue). \ns to pause particles. \nd to increase the particle's speed, a to decrease it.", 10, 20);
	
	if(recording){
		ofDrawBitmapString("RECORDING",(ofGetWidth()-80),20);	
		ofSetColor(255,0,0);
		ofDrawCircle((ofGetWidth()-90),16, 5);	
		}
	
	else if(replaying){
		ofDrawBitmapString("REPLAYING",(ofGetWidth()-80),20);	
		ofSetColor(255,0,0);
		ofDrawCircle((ofGetWidth()-90),16, 5);
	}
}

//--------------------------------------------------------------
int ofApp::giveInput(vector <int> input){
	if(newinput.size() == 0){			// The input vector will not copy to newinput vector unless the replay finished or a Cancel is called
		newinput = input;
	}
	int in = newinput[0];
	newinput.erase(newinput.begin());	
	return in;
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	// Recording feature Definition ------------------------------------------------------------------------------------------------------------

  	if(((key == 'p')||(key == 'P')) && recording == false && replaying == false && keys.size() != 0){					// This will go when the program is not recording and is not replaying
		counter = 1;
		replaying = true;
		replayLock = true;																								// This will make it so that the program does not listen to any keys pressed during a replay
	}
	else if(((key == 'c')||(key == 'C')) && recording == false && replaying == true){				// This will go when the program is not recording but it is replaying
		replaying = false;
		replayLock = false;
		newinput.clear();
	}
	else if (replayLock != true){																	// This will go when the program is not replaying
		if((key == 'r')||(key == 'R')){
			if(recording==true){
				recording = false;
			}
			else{
				keys.clear();					// Clears previous recording
				newinput.clear();
				recording = true;				// Starts recording
			}							
		}
		if((recording) && (key != 'r') && (key != 'R') && (key != 'p') && (key != 'P') && (key != 'c') && (key != 'C')){	// This records the keys pressed that are not 'r', 'p', and 'c' when program is recording
			keys.push_back(key);
			}
		
	//------------------------------------------------------------------------------------------------------------------------------------------
		
		if( key == '1'){
			currentMode = PARTICLE_MODE_ATTRACT;
			currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse"; 
					
		}
		if( key == '2'){
			currentMode = PARTICLE_MODE_REPEL;
			currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse"; 
						
		}
		if( key == '3'){
			currentMode = PARTICLE_MODE_NEAREST_POINTS;
			currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS:"; 
								
		}
		if( key == '4'){
			currentMode = PARTICLE_MODE_NOISE;
			currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation"; 						
			resetParticles();
		}	
		if ((key == 't')||(key == 'T')){
			colorChange = true;
			number+=1;
			if (number > 3) 								//countwr to determine color
				number = 1; 
			}
		if((key == 's')||(key == 'S')){
			if (pause){pause = false;} 						//Used to check if particles are paused or are moving 
			else{pause = true;}		
		}
		if((key == 'd')||(key == 'D')){  					//Indicates that we want to increase the speed 
			velocityMode = "doubled";
			n=d;
			d+=1;
			a=1;
		}	
		if((key == 'a')||(key == 'A')){   					//Indicates that we want to decrease the speed 
			velocityMode = "halved";
			n=a;
			a+=1;
			d=1;
		}
		if ((key == '1')||(key == '2')||(key == '3')||(key == '4')||( key == ' ' )){
			velocityMode= "None";
			d= 1;
			a = 1;			
			colorChange = false;
			number = 0;
			pause = false;
		}
		if( key == ' ' ){
			resetParticles();
		}
		//Added values are reset
	}
}



//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
