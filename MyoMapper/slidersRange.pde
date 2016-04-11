Range rYaw;
Range rPitch;
Range rRoll;
Range avgEMG;

int sYawX, sPitchX, sRollX, sEmgX;
int sYawXsize, sPitchXsize, sRollXsize, sEmgXsize;
int sYawY, sPitchY, sRollY, sEmgY;
int sYawYsize, sPitchYsize, sRollYsize, sEmgYsize;

int rYawX, rPitchX, rRollX, rEmgX;
int rYawXsize, rPitchXsize, rRollXsize, rEmgXsize;
int rYawY, rPitchY, rRollY, rEmgY;
int rYawYsize, rPitchYsize, rRollYsize, rEmgYsize;

void rescale() {
  
  rYawXsize = rPitchXsize = rRollXsize = rEmgXsize = sYawXsize = sPitchXsize = sRollXsize = sEmgXsize = int(width*0.3); // X size sliders
  rYawYsize = rPitchYsize = rRollYsize = rEmgYsize = sYawYsize = sPitchYsize = sRollYsize = sEmgYsize = int(height*0.04);  // Y Size
  sYawX = sPitchX = sRollX = sEmgX = rYawX = rPitchX = rRollX = rEmgX = tglYawX; // x margins
  
  sYawY = tglemgY;
  sPitchY = sYawY+(sYawYsize*3);
  sRollY = sYawY+(sYawYsize*6);
  sEmgY = sYawY+(sYawYsize*9);
  
  rYawY = sYawY+sYawYsize;
  rPitchY = sPitchY+rYawYsize;
  rRollY = sRollY+rYawYsize;
  rEmgY = sEmgY+rEmgYsize;

  rYaw = cp5.addRange("Range Yaw")
    .setBroadcast(false) 
    .setPosition(rYawX, rYawY)
    .setSize(rYawXsize, rYawYsize)
    .setHandleSize(20)
    .setRange(-2,2)
    .setRangeValues(0,2)
    .setBroadcast(true)
    .setColorForeground(color(255,40))
    .setColorBackground(color(255,40)) 
    .setHighValue(1)
    .setLowValue(0)
    ;
 
  rPitch = cp5.addRange("Range Pitch")
    .setBroadcast(false) 
    .setPosition(rPitchX, rPitchY)
    .setSize(rPitchXsize,rPitchYsize)
    .setHandleSize(20)
    .setRange(-2,2)
    .setRangeValues(0,2)
    .setBroadcast(true)
    .setColorForeground(color(255,40))
    .setColorBackground(color(255,40))  
    .setHighValue(1)
    .setLowValue(0)
    ;
             
  rRoll = cp5.addRange("Range Roll")
    .setBroadcast(false) 
    .setPosition(rRollX, rRollY)
    .setSize(rRollXsize,rRollYsize)
    .setHandleSize(20)
    .setRange(-2,2)
    .setRangeValues(-2,2)
    .setBroadcast(true)
    .setColorForeground(color(255,40))
    .setColorBackground(color(255,40))  
    .setHighValue(1)
    .setLowValue(0)
    ; 
    
  avgEMG = cp5.addRange("Range MAV")
    .setBroadcast(false) 
    .setPosition(rEmgX, rEmgY)
    .setSize(rEmgXsize, rEmgYsize)
    .setHandleSize(20)
    .setRange(0,4)
    .setRangeValues(0,2)
    .setBroadcast(true)
    .setColorForeground(color(255,40))
    .setColorBackground(color(255,40))  
    .setHighValue(1)
    .setLowValue(0)
    ;  
    
  noStroke();  
}