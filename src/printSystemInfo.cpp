  #include <Arduino.h>
  /**
   * Prints system info to the serial monitor as shown below:
   * 
   *  --- System Info ---
   *  model          ESP32
   *  cores          2
   *  features       WIFI b/g/n   BLE   BT
   *  revision       3
   *  full_revision  301
  */
  void printSystemInfo()
  {
    const char *chipModel[] = {"UNKOWN", "ESP32", "ESP32-S", "ESP32-S3", "ESP32-C3", "ESP32-H2"};
    const char *chipFeatures[] = {"FLASH", "WIFI b/g/n", "", "", "BLE", "BT", "IEEE 802.15.4", "PSRAM"};
    esp_chip_info_t chipInfo;
    esp_chip_info(&chipInfo);
    uint32_t b = 1;
    
    Serial.println("\nSystem Info\n-----------");
    Serial.printf("model          %s\ncores          %d\n", chipModel[chipInfo.model], chipInfo.cores);
    Serial.print("features       ");
    for (int i = 0; i < 8; i++)
    { // output the bit-coded features
      if (chipInfo.features & b) Serial.printf("%s   ", chipFeatures[i]);
      b <<= 1; // mask the next bit
    }
    Serial.printf("\nrevision       %d\nfull_revision  %d\n\n", chipInfo.revision, chipInfo.full_revision);
  }