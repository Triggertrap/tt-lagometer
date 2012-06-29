  int focus = 9;
  int shutter = 8; 
  int auxport = A0; 
  int val = 0; 
  String Preamble = ""; 
  boolean focuson   = true;  // if true, trigger normally. if false, engage shutter first. 
  boolean verbose   = true; // If true, only output results
  
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
}


void loop() {
if (verbose)
  {
  Serial.println("\nWaiting for 3 seconds before triggering again...");
  }
 delay(2500); // Wait for x ms

if (focuson) 
  { 
    if (verbose)
      {
        Serial.println("Triggering normally...");
      }
  }
else
 {
    digitalWrite(focus, LOW);
    if (verbose)
      {
         Serial.println("Triggering with Focus already engaged...");
      }
    delay(1000);     
    if (verbose)
    {
      Serial.print(" NOW...");
    }
 }
 
 boolean waiting = true; 
 
 start = micros();
 digitalWrite(focus, LOW);
 digitalWrite(shutter, LOW);

 while(waiting){   
   val = analogRead(auxport); 
   if (val < 100)
     {
       finish = micros();                       // Stop the clock!
       duration = finish - start ;              // Duration in microseconds 
       
       String durationuS = String(duration); 
       duration = duration / 1000; // From microseconds to milliseconds
       String durationMS = String(duration); 
      
      if (focuson)
        {
           Preamble = "Shutter Lag, measured in normal mode: ";
        }
       else
        {
           Preamble = "Shutter Lag, measured in pre-focus mode: ";
        }
       
       Serial.println(Preamble + " " + durationMS + "ms / " + durationuS + " microseconds" );
       
       waiting = false; // Break out of while loop
     }
}
 digitalWrite(focus, HIGH);
 digitalWrite(shutter, HIGH);
}
