volatile long encodercounter=0;
long pt=0;
float ep=0;
float ei=0;
float previousOutput=0;


void setup () 
{
  
Serial.begin (9600); 

pinMode( 3 , INPUT); 
pinMode( 2 , INPUT); 
pinMode( 6 ,OUTPUT); 
pinMode( 5 ,OUTPUT);

attachInterrupt(digitalPinToInterrupt(3), updateEncoder,CHANGE);
 
} 
void loop()
{  
  int target =1000;
  float kp=2.0;
  float ki=0.1;
  float kd=0.01;
  float alpha= 0.9;
  float output=PID(target ,kp ,ki,kd);
  float smoothedOutput=output;
  if (previousOutput!=0){
    float smoothedOutput=smoothing(previousOutput,output,alpha);}
   previousOutput=output; 
  float speed=fabs(smoothedOutput);
  if(speed>255) speed=255;
  int direction=1;
  if(smoothedOutput<0) direction=0;
  digitalWrite( 5 , direction);
  analogWrite ( 6 , speed);
}
    
    void updateEncoder()
{
  if (digitalRead(3)>digitalRead(2))
  encodercounter++;
   else encodercounter--;
}
float PID(int target ,float kp ,float ki,float kd){
   int ct=millis();
  float dt= ((float)ct-pt)/1000;
  int e=encodercounter-target;
  
  ei += e*dt;
  float ed=(e-ep)/dt;
  
  float u=(e*kp)+(ki*ei)+(kd*ed);
  pt=ct;
  ep=e;}
float smoothing(float po ,float o, float alpha){
  return alpha*po +(1-alpha)*o;}