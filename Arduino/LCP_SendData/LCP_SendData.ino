void setup() { 
  Serial.begin(9600); 
  
  while (!Serial) {
    ; // wait 
  }
  Serial.setTimeout(100);
  for(int i=0; i<10; i++)
    Serial.println("Cose a caso");
  Serial.flush(); // ASPETTO LA FINE DELLA TRASMISSIONE
  delay(10);  // METTO UN DELAY
  Serial.println("Arduino is ready!");               
}

void loop() {
  Serial.println("Insert command operation:");
  char command = 'N';
  do {
    command = checkchar();
  } while(command == 'N'); 
  if(command == 'p') {
    for(int i=0; i<200; i++) {
      Serial.print("Reading[");
      Serial.print(String(i));
      Serial.print("]: ");
      Serial.println(readCell(),5);
    }
    Serial.println("Operation Complete");  
  }
  else if(command == 't') {
    Serial.println("Taring...");
    delay(10000);
    Serial.println("Taring is complete");                                          
  }
  else if(command == 'w') {
    for(int i=0; i<200; i++) {
      Serial.println(readCell(),5);
    }
  }
  else if(command == 's') {
    String scale;
    Serial.println("Insert scale:");
    Serial.flush();
    while (Serial.available() <= 0) {
      ;
    }
    scale = Serial.readStringUntil('\n');
    scale = "Scale updated to " + scale;
    Serial.println(scale); 
  }
  delay(10);                                  
}

float readCell(){
  return random(10,100);
}

char checkchar(){
  String recvchar = "0";
  if (Serial.available() > 0) {
    recvchar = Serial.readStringUntil('\n');
    if(recvchar[0] == 'p' or recvchar[0] == 't' or recvchar[0] == 'w' or recvchar[0] == 's')
      return recvchar[0];
    else
      return 'N';
  }
  else
    return 'N';
}
