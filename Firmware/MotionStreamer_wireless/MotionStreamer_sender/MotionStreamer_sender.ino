/*
  Testing communication with sensors
*/

#include "src/BodyModel/BodyModel.h"
#include "src/Communication/EspNow/esp_now_wrapper.h"

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x30, 0xAE, 0xA4, 0x9B, 0xF5, 0x44};

// Change data rate
const long frequency = 50;
const long ideal_period = round(1000000.0/frequency);
static SemaphoreHandle_t timer_sem;

BodyModel model;





void sample_timer_task(void *param)
{
  timer_sem = xSemaphoreCreateBinary();
  while (1) {
    xSemaphoreTake(timer_sem, portMAX_DELAY);



    model.filter();
    float D[30];
    model.getFlattenedData(D);
    guaranteeSend(broadcastAddress, (uint8_t*) &D, sizeof(D));

    /*/
    char string_buff[300];
    sprintf(string_buff, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
    D[0], D[1], D[2], D[3], D[4], D[5], D[6], D[7], D[8], D[9],
    D[10], D[11], D[12], D[13], D[14], D[15], D[16], D[17], D[18], D[19],
    D[20], D[21], D[22], D[23], D[24], D[25], D[26], D[27], D[28], D[29]);
    Serial.println(string_buff);
    //*/

    
  }
}

void IRAM_ATTR onTimer(){
  static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  xSemaphoreGiveFromISR(timer_sem, &xHigherPriorityTaskWoken);
  if( xHigherPriorityTaskWoken) {
    portYIELD_FROM_ISR(); // this wakes up sample_timer_task immediately
  }
}





void setup(){
  //Serial.begin(2000000);
  model.begin(frequency);
  setupEspNowReceiver(broadcastAddress);

  // Create timer interrupt
  hw_timer_t *ticker = NULL;
  ticker = timerBegin(0, 2, true);
  timerAttachInterrupt(ticker, onTimer, true);
  timerAlarmWrite(ticker, 40*ideal_period, true);
  timerAlarmEnable(ticker);

  xTaskCreatePinnedToCore(sample_timer_task, "sample_timer", 4096, NULL, configMAX_PRIORITIES - 1, NULL, 1);
}

void loop(){}
