bool initializeSD(int _chipSelect) {
  if (!SD.begin(_chipSelect)) {
    if (Serial) {
      Serial.println("SD card initializing failed.");
    }
    return false;
  }
  if (Serial) {
    Serial.println("SD card ready to log.");
  }
  return true;
}

void logRaw(fs::FS &fs) {
  bool newReading = true;
  String incoming;
  int i = 0;
  int j = 0;
  const int N = 200;
  String dataString = "";
  File dataFile = fs.open("/data.csv", FILE_WRITE);

  int fileSize = dataFile.size();
  dataFile.seek(fileSize);

  if (dataFile) {
    dataString = "";

    long temp = cell.read();
    temp = cell.read();
    temp = cell.read();
    temp = cell.read();
    temp = cell.read();

    for (i = 0; i < N; i++) {
      long reading = cell.read() - offset;
      dataString += String(reading);
      dataString += ",";
      Serial.println("Reading " + String(i) + ": " + String(reading));
    }
    //cell.power_down();
    dataFile.println(dataString);
    Serial.println("Writing successful.");
    dataFile.close();
    Serial.println("File closed.");
  } else {
    Serial.println("Can not open the file.");
  }
}
