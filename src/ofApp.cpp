#include "ofApp.h"

//--------------------------------------------------------------   // Push test
void ofApp::setup(){
	ofSetVerticalSync(true);
	
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
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));

	for(unsigned int i = 0; i < p.size(); i++){
		if(particleRectBorder.inside(p[i].pos.x, p[i].pos.y)){					// This magnifies the particles inside the rectangle
			p[i].setNewSize();
			p[i].draw();
		}
		else{p[i].draw();}
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

			// Rectangle Draw
			// --------------------------------------------------------------------------------------

	ofNoFill();
	ofSetColor(255);
	ofDrawRectangle(rect);		
	ofFill();

			// -----------------------------------------------------------------------------------------


	ofSetColor(230);	
	ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode. \nt to change color (red, green, blue). \ns to pause particles. \nd to increase the particle's speed, a to decrease it.", 10, 20);
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
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
		if (number > 3) //countwr to determine color
			number = 1; 
		}
	if((key == 's')||(key == 'S'))
	{
		if (pause == true){pause = false;} //Used to check if particles are paused or are moving 
		else{pause = true;}		
	}

	if((key == 'd')||(key == 'D'))   //Indicates that we want to increase the speed 
	{velocityMode = "doubled";n=d;d+=1;a=1;}	

	if((key == 'a')||(key == 'A'))   //Indicates that we want to decrease the speed 
	{velocityMode = "halved";n=a;a+=1;d=1;}


	if( key == ' ' ){
		resetParticles();
	}
    //Added values are reset
	if ((key == '1')||(key == '2')||(key == '3')||(key == '4')||( key == ' ' )){
		velocityMode= "None";
		d= 1;
		a = 1;			
		colorChange = false;
		number = 0;
		pause = false;
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
	if (button == 0){							// This sets the properties for the rectangle: rect
		rect.x = rectStartPoint.x;
		rect.y = rectStartPoint.y;
		rect.width = x - rectStartPoint.x;		// This sets the width of the rectangle based on the coordinates of mouse when dragged
		rect.height = y - rectStartPoint.y;		// This sets the height of the rectangle based on the coordinates of mouse when dragged


		rectBorder1.x = rect.getBottomLeft().x + 5;
		rectBorder1.y = rect.getBottomLeft().y - 5;
		rectBorder2.x = rect.getTopRight().x - 5;
		rectBorder2.y = rect.getTopRight().y + 5;
		particleRectBorder.set(rectBorder1, rectBorder2);		// This creates a second rectangle that will resize the scale of particles when they leave the main rectangle
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (button == 0){					// This sets the coordinates for the starting point of the rectangle
		rectStartPoint.x = x;
		rectStartPoint.y = y;
	}

	if (button == 2){					// This erases the rectangle if the coordinates of the rick click is inside the rectangle
		if (rect.inside(x,y)){
			rect.set(0, 0, 0, 0);
		}
	}
	
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
