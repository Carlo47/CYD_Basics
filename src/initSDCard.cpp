#include <Arduino.h>
#include <SD.h>


/**
 * Initialize the SD card (Trans Flash) using VSPI (SPI3_HOST) or HSPI_HOST 
 * with standard pins CS = 5, SCK = 18, MISO = 19, MOSI = 23 
 * These pins are determined by the layout of the board ESP32_2432S028
 * Define 
 * SPIClass sdcardSPI(VSPI);
 * or
 * SPIClass sdcardSPI(HSPI);
 * in main.cpp 
 * and pass sdcardSPI as argument to initSDcard()
*/
void initSDCard(SPIClass &spi)
{
    spi.begin(TF_SPI_SCLK, TF_SPI_MISO, TF_SPI_MOSI, TF_CS);
    if (!SD.begin(TF_CS, spi)) // 👉 Use default frequency of 4MHz
        log_e("==> SD.begin failed!");
    else
        log_e("==> done");
}


/**
 * Use a raw string literal to print a formatted string of SD card details
*/
void printSDCardInfo()
{
  const char *knownCardTypes[] = {"NONE", "MMC", "SDSC", "SDHC", "UNKNOWN"};
  sdcard_type_t cardType = SD.cardType();
  //uint64_t numSectors= SD.numSectors();
  //uint64_t sectorSize= SD.sectorSize(); 
  uint64_t cardSize  = SD.cardSize() >> 20; // divide by 2^20 = 1'048'576 to get size in MB
  uint64_t cardTotal = SD.totalBytes() >> 20;
  uint64_t cardUsed  = SD.usedBytes() >>  20;
  uint64_t cardFree  = cardTotal - cardUsed; 
  Serial.printf(R"(
SDCard Info
-----------
  type     %s
  size   %6llu MB
  total  %6llu MB
  used   %6llu MB
  free   %6llu MB
)", knownCardTypes[cardType], cardSize, cardTotal, cardUsed, cardFree); 
}


/**
 * Recursively lists all directories/files of 
 * the file system starting at direcory dir
 * 
 * Usage    listFiles(SD.open("/"));            // show content starting at root
 *          listFiles(SD.open("/SCREENSHOTS"))  // show content of directory SCREENSHOTS
 * 
 * Code borrowed from:
 * https://wiki-content.arduino.cc/en/Tutorial/LibraryExamples/Listfiles * 
*/
void listFiles(File dir, int indent=0) 
{
  while (true) 
  {
    File entry =  dir.openNextFile();

    if (! entry) break; // no more files
    
    Serial.printf("%*c", indent*4, ' ');

    if (entry.isDirectory()) 
    {
      Serial.printf("%s/\n", entry.name());
      listFiles(entry, indent + 1);
    } 
    else 
    {
      // files have sizes, directories do not
      Serial.printf("%s, %d\n", entry.name(), entry.size());
    }
    entry.close();
  }
}