




int sensorPin = A3;    // select the input pin
int sensorValue = 0;  // variable to store the value coming from the sensor
double timer=0; //variable that sets at both ends of every swing
double ttimer=0; //keeps track of time throughout wave, used as input
double swingtimer=0; //time of swing
double sliver=0; //fraction of swing, used to output to LEDs
int indexer=0; // helps calculate swingtimer
double counter=0; // assists ttimer value on swing right to left
double start=0; // assists ttimer on swing right to left
int columnvector[10]; // no need for this right now
int column=0; // used to output column of LEDs
float c; //primitive column value


int H[10][69]={
  {0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
  {0,0,1,0,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0},
  {0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0},
  {0,0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0},
  {0,0,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1,1,1,0,0,0},
  {0,0,1,0,0,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,1,1,0,0,0},
  {0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0},
  {0,0,1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0},
  {0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
  {0,0,1,0,0,0,0,1,0,0,1,1,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1},  };
   
   
void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(9600);
  for(int i = 2; i < 13; i++)  {pinMode(i, OUTPUT);}  // initialize digital pins 0-50 as an output. note: 0&1 are for serial comunication
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin); // turn the ledPin on
 

 
  if (sensorValue>460&&sensorValue<480) { // angular velocity is 0, ends of swingwave
    timer=millis(); // sets timer at both ends of swingwave
    swingtimer=ttimer; // sets swingtime equal to previous swing

    digitalWrite(2, LOW); // outputs nothing at the ends of the wave
    digitalWrite(3, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    if (indexer==1){ // makes sure at least 50 clocks have happened to make sure 'indexer=3' happens at other end of swing
       if (swingtimer>50){
         
     indexer=3; 
     //Serial.println(indexer);
    }
    }
     
  }
  else {
   // Serial.println(millis());
    if (sensorValue<460){ttimer=millis()-timer; //swing going from left to right
        if(ttimer>98*sliver){ // right part of the swing
        counter=ttimer; // counter preserves ttimer value, ttimer gets reset on right side of wave
        start=timer; // start preserves timer value, timer gets reset on right side of wave
        }
      }
   
  
    else if (sensorValue>480){
  ttimer=(counter-(millis()-start-counter));} // swing from right to left
  
   c=ttimer-25*sliver; //gives loose value of column. i.e. 2.6
   column=(int)c; // converts approximate value of column to actual (2.6--->2)
    
    
    digitalWrite(2, H[0][column]);
    digitalWrite(3, H[1][column]);
    digitalWrite(5, H[2][column]);
    digitalWrite(6, H[3][column]);
    digitalWrite(7, H[4][column]);
    digitalWrite(8, H[5][column]);
    digitalWrite(9, H[6][column]);
    digitalWrite(10, H[7][column]);
    digitalWrite(11, H[8][column]);
    digitalWrite(12, H[9][column]);
   

  
  
  //Serial.println(indexer);
  if (indexer==3) {
    

   indexer=0;
   sliver=swingtimer/123;
   
   
  }
   indexer=1;
  }

 
  digitalWrite(22, HIGH);
digitalWrite(22, LOW);
 
}
