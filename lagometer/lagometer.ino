  int focus = 9;
  int shutter = 8; 
  int auxport = A0; 
  int val = 0; 
  String Preamble = ""; 
  boolean focuson   = true;  // if true, trigger normally. if false, engage shutter first. 
  boolean verbose   = false; // If true, only output results
  int exposurecount = 0; 
  
  
  int pfexposure = 0; 
  int pfexposurecount = 0; 
  int normalexposure = 0; 
  int normalexposurecount = 0; 
  
  
 unsigned long start, finish, duration;
 String LagDuration; 


void setup() {
  // put your setup code here, to run once:
  
  unsigned long start, finished, elapsed, auxport;
  boolean waiting = true; 

  pinMode(focus, OUTPUT); // Focus
  pinMode(shutter, OUTPUT); // Shutter  
  pinMode(auxport, INPUT); // AUX
  Serial.begin(9600);
  Serial.println("\nStarting Lag-o-Meter...");
  val = analogRead(auxport); 
  delay(1000); 
  val = analogRead(auxport); 
  digitalWrite(focus, HIGH);
  digitalWrite(shutter, HIGH);
}


void loop() {
  exposurecount++; 
  
 if (exposurecount > 10)
   {
     focuson = false; 
   }  
 if (exposurecount == 11)
   {
    Serial.println("Average exposure with normal focus signal mode: " + String(normalexposure/normalexposurecount) + "ms\n");
      int normalexposure = 0; 
      int normalexposurecount = 0; 
   }  
 if (exposurecount > 20)
  {
    focuson = true;
    exposurecount = 1; 
    Serial.println("\nAverage exposure with pre-focused mode: " + String(pfexposure/pfexposurecount) + "ms\n");   
    Serial.println("\n\nCompleted 20 exposures... Waiting 10 seconds");
    int pfexposure = 0; 
    int pfexposurecount = 0; 
    delay(10000);
  } 
  
 delay(1000); // Wait for x ms between shots

if (focuson) 
  { 
  }
else
 {
    digitalWrite(focus, LOW);
    delay(1000);     
 }
 
 boolean waiting = true; 
 
 start = micros();
 digitalWrite(focus, LOW);
 digitalWrite(shutter, LOW);    

   val = analogRead(auxport); 
 while(waiting){   
   if (val < 150)
     {
       finish = micros();                       // Stop the clock!
       duration = finish - start ;              // Duration in microseconds 
       
      int durationMS = duration / 1000; // From microseconds to milliseconds
      
      if (focuson)
        {
           Preamble = "Shutter Lag, exposure " + String(exposurecount)  + " measured in normal mode: ";
           normalexposure = normalexposure + durationMS;
           normalexposurecount++;  
        }
       else
        {
           Preamble = "Shutter Lag, exposure " + String(exposurecount)  + " measured in pre-focus mode: ";
           pfexposure = pfexposure + durationMS; 
           pfexposurecount++; 
        }
       
      if (durationMS > 3000)
        {
          Serial.println("Shutter lag was " + String(durationMS) + "ms, so let's ignore this one...\n" );
          exposurecount = 0; 
          int pfexposure = 0; 
          int pfexposurecount = 0; 
          int normalexposure = 0; 
          int normalexposurecount = 0; 
        }
      else
        {
          Serial.println(Preamble + " " + String(durationMS) + "ms / " + String(duration) + " microseconds" );
        }
       waiting = false; // Break out of while loop
     }
  val = analogRead(auxport); 

}
 digitalWrite(focus, HIGH);
 digitalWrite(shutter, HIGH);
 

 
}
