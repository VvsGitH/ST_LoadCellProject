void initializeLoadCell(const int _DT, const int _SCK, fs::FS &fs) {
  cell.begin(_DT, _SCK, 128);
  //cell.power_down();

  if (fs.exists("/offset.txt")) {
    File offsetFile = fs.open("/offset.txt", FILE_READ);
    offset = offsetFile.parseInt();
    cell.set_offset(offset);
    Serial.println("Offset set to: " + String(offset));
  }

  if (fs.exists("/scale.txt")) {
    File scaleFile = fs.open("/scale.txt", FILE_READ);
    scale = scaleFile.parseFloat();
    Serial.println("Current scale is: " + String(scale));
  }
  
  if (Serial) {
    Serial.println("Load cell initialized.");
  }
}

void tare(fs::FS &fs) {
  int i = 0;
  int j = 0;
  int temp;
  long sum = 0;
  long reading;
  const int N = 200;
  File offsetFile = fs.open("/offset.txt", FILE_WRITE);

  if (offsetFile) {
    //cell.power_up();
    if (Serial) {
      Serial.println("Taring... ");
    }
    for (i = 0; i < 5; i++) {
      temp = cell.read();
    }
  
    for (i = 0; i < N; i++) {
      reading = cell.read();
      sum += reading;
      //Serial.println("Taring sample " + String(i) + ": " + String(reading));
    }
    offset = sum/N;
    offsetFile.print(String(offset));
    offsetFile.close();
    // Serial.println("Offset: " + String(offset));
    Serial.println("Taring completed.");
    cell.set_offset(offset);
    //cell.power_down();
  } else {
    Serial.println("Can not open the file.");
  }
}

void weight(fs::FS &fs) {
  int N = 200;
  
  if ( scale == 0) {
    if (fs.exists("/scale.txt")) {
      File scaleFile = fs.open("/scale.txt", FILE_READ);
      scale = scaleFile.parseFloat();
      scaleFile.close();
    } else {
      Serial.println("Can not open the file and weigh.");
      return;
    }
  }

  File wFile = fs.open("/wlog.txt", FILE_WRITE);
  if(wFile) {
    float mean_w = 0;
    float temp;
    float reading;
    int i;
    const int N = 200;
    
    for (i = 0; i < 5; i++) {
      temp = cell.read();
    }

    float weight = 0;
    for (i = 0; i < N; i++) {
      reading = cell.read() - offset;
      mean_w += reading/scale;
      // Serial.println("Reading " + String(i) + ": " + String(reading));
      weight = reading/scale;
      Serial.println(weight,5);
    }
    mean_w /= float(N);
    wFile.println(String(mean_w));
   /*  Serial.print("Weight is: ");
    Serial.print(weight,3);
    Serial.println(" g");*/
    wFile.close();
  } else {
    Serial.println("Can not open the file.");
    return;
  }
}

void setScale(fs::FS &fs) {
  String scale_str;
  File scaleFile = fs.open("/scale.txt", FILE_WRITE);

  if(scaleFile) {
    Serial.println("Enter new scale: ");
    while( !Serial.available() ) {
      delay(1);
    }
    scale_str = Serial.readStringUntil('\n');
    scale = scale_str.toFloat();
    // Serial.println(scale,4);
    scaleFile.println(scale,4);
    scaleFile.close();
    scale_str = "Scale updated to " + String(scale);
    Serial.println(scale_str);
  } else {
    Serial.println("Can not open the file.");
    return;
  }
}
