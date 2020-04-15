bool mode = false;
bool newData = false;
String receivedString;

void setup() { 
  Serial.begin(9600);                             // STARTING SERIAL COMMUNICATION
  while (!Serial) {                               // WAITING FOR ARDUINO TO CONNECT
    ; // wait 
  }
  Serial.setTimeout(100);                        // SETTING TIMEOUT
  Serial.println("Arduino is ready!");
}

void loop() {
  // Local variables
  float data;
  float reference;
  float result;
  
  recvOneString();                                                         // Receiving control string from LabVIEW
  
  if (newData == true) {
    
    modeSelect();                                                         // MODE SELECTION from LabVIEW string
    // Serial.print("Selected mode: "); 
    // Serial.println(mode);                                              // Sending mode back to LabVIEW - DELETE THIS 
    switch (mode) {
      
      case true:                                                          // MODALITA' BILANCIA
        
        data = readCell();                                                // Reading data from Load Cell
        // Serial.print("Peso rilevato: "); 
        Serial.println(data,5);                                           // Sending data to LabVIEW
      break;
      
      case false:                                                         // MODALITA' DI TARATURA
      
        data = readCell();                                                // Reading data from Load Cell
        // Serial.print("Peso rilevato: "); 
        Serial.print(data,5);                                             // Sending data to LabVIEW
        reference = readRef();                                            // Extracting reference weight from LabVIEW string
        // Serial.print("Peso corretto: "); 
        // Serial.println(reference,5);                                   // Sending it back to LabVIEW - DELETE THIS
        result = calibration(data,reference);                             // Calibration
        //Serial.print("Peso tarato: "); 
        Serial.print(" - ");
        Serial.println(result,5);                                         // Sending correct weight to LabVIEW
      break;
      
    } // end switch
    newData = false;                                                      // Resetting newData
    
  } // end if
  delay(10);
}

void recvOneString() {                        // READ STRING FUNCTION - Read LabVIEW control string
 if (Serial.available() > 0) {                // if any data is received
  receivedString = Serial.readString();
  newData = true;
 }
}

void modeSelect() {                           // MODE SELECTION FUNCTION - Extract mode from LabVIEW string
  if (receivedString[0] == '1')               // The first element of the string contain the mode of operation
     mode = true; 
  else
     mode = false;
}

float readCell() {                            // READ CELL FUNCTION - TODO
  return 33.33;
}

float readRef() {                             // EXTRACT REFERENCE WEIGHT FUNCTION 
  int n = int(receivedString.length());       
  for (int i=1; i< n-1; i++) {
    receivedString[i-1] = receivedString[i];  // Delete the first element of the string (mode)
  }
  return receivedString.toFloat();            // Transform the resulting string into a float and return it
}

float calibration (float D, float R) {        // CALIBRATION FUNCTION - TODO
  return D+R;
}
