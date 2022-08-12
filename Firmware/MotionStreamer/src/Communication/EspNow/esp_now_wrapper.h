#include <esp_now.h>
#include <WiFi.h>

void setupEspNowReceiver(esp_now_recv_cb_t OnDataReceive);

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

void setupEspNowReceiver(uint8_t *broadcastAddress);

void guaranteeSend(const uint8_t *broadcastAddress, const uint8_t *myData_addr, const unsigned long myData_len);