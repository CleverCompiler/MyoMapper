import controlP5.*;
ControlP5 cp5;


int windowX, windowY = 0;
void setup() {
  
  frameRate(24);
  
  cp5 = new ControlP5(this);
  
  size(int(displayWidth*0.8), int(displayHeight*0.9)); //window size
  
  myoSetup(); 
  setUpMIDI();
  toggles();
  bangs();
  oscSetup(); 
  rescale();
  setupSliders(); 
} 

void draw() {
  background(0);
  
  if(poseOnOff)sendPose();
  if(orientOnOff)sendOrientation();
  if(accOnOff)sendAcceleration();
  if(gyroOnOff)sendGyro();
  if(mavOnOff)MAV();
  emgSend();
  updateSliders();
  labels();
  if(waveformOnOff){
    labelsAnalysis();
    analysis();
  }
}
