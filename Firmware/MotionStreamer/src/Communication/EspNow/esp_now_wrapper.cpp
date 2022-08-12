#include "esp_now_wrapper.h"
#include <esp_now.h>
#include <WiFi.h>





// Setting up esp32 device as receiver
void setupEspNowReceiver(esp_now_recv_cb_t OnDataReceive)
{
    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK)
    {
        return;
    }

    // Register recv CB to get recv packer info
    // "OnDataReceive"
    esp_now_register_recv_cb(OnDataReceive);
}





// Setting up esp32 device as sender
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {}

void setupEspNowReceiver(uint8_t *broadcastAddress)
{
    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK)
    {
        return;
    }

    esp_now_peer_info_t peerInfo;

    // Register for Send CB to get the status of Trasnmitted packet
    esp_now_register_send_cb(OnDataSent);

    // Register peer
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    // Add peer
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        return;
    }
}





// Send until received
void guaranteeSend(const uint8_t *broadcastAddress, const uint8_t *myData_addr, const unsigned long myData_len)
{
    esp_err_t result;
    do{ result = esp_now_send(broadcastAddress, myData_addr, myData_len);
    } while (result != ESP_OK);
}



