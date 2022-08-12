/*
  Name: ESP NOW receiver with USB UART
  Purpose: Receives stream data from sender and sends it over USB UART to computer
  For catching
  Credits: Based off Rui Santos's ESP_NOW library: https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/
  @author Meng Lin
  @version 1.1 20/04/22
*/

#include "src/esp_now_wrapper.h"

// REPLACE WITH YOUR RECEIVER MAC Address
// uint8_t broadcastAddress[] = {0x78, 0x21, 0x84, 0x88, 0xBB, 0x94};

float D[30];





void OnDataRec(const uint8_t *mac, const uint8_t *incomingData, int len){
  memcpy(&D, incomingData, sizeof(D));
  char string_buff[300];
  sprintf(string_buff, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
  D[0], D[1], D[2], D[3], D[4], D[5], D[6], D[7], D[8], D[9],
  D[10], D[11], D[12], D[13], D[14], D[15], D[16], D[17], D[18], D[19],
  D[20], D[21], D[22], D[23], D[24], D[25], D[26], D[27], D[28], D[29]);
  Serial.println(string_buff);
}





void setup(){
  Serial.begin(1000000);
  setupEspNowReceiver(OnDataRec);
} 

void loop(){}
