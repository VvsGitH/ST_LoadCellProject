#include <SPI.h>
#include <SD.h>
#include <FS.h>
#include <HX711.h>

#define SD_CS 5
#define DT 0
#define SCK 15

long offset = 0;
float scale = 0;

HX711 cell;

void setup() {
  Serial.begin(115200);
  while (!Serial){
    ;
  }
  initializeSD(SD_CS);
  initializeLoadCell(DT, SCK, SD);
  Serial.println("Arduino is ready");
}

void loop() {
  // Serial.println("Enter t for new tare, p for new samples, w for new weigh, s for new scale.");
  Serial.println("Waiting for new command.");
  while ( !Serial.available() ) {
    delay(1);
  }
  if ( Serial.available() > 0 ) {
    String menu = Serial.readStringUntil('\n');
    Serial.flush();

    if ( menu[0] == 't' ) {
      tare(SD);
      Serial.println(String(offset));
      delay(5);
      Serial.println(String(scale));
    }

    if ( menu[0] == 'p' ) {
      logRaw(SD);
    }

    if ( menu[0] == 'w' ) {
      weight(SD);
    }

    if ( menu[0] == 's' ) {
      setScale(SD);
    }
  }
  delay(10);
}
