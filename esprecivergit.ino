#include <WiFi.h>
#include <esp_now.h>

// Structure to match sender's data
typedef struct struct_message {
  int angle;
  int distance;
} struct_message;

struct_message incomingData;

// Callback function when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingDataBytes, int len) {
  memcpy(&incomingData, incomingDataBytes, sizeof(incomingData));

  Serial.print("Receiver Received -> Angle: ");
  Serial.print(incomingData.angle);
  Serial.print("°, Distance: ");
  Serial.print(incomingData.distance);
  Serial.println(" cm");
}

void setup() {
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(); // Not connecting to any WiFi network

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register the receive callback function
  esp_now_register_recv_cb(OnDataRecv);

  Serial.println("ESP-NOW Receiver Ready");
}

void loop() {
  // Nothing to do in loop; data is handled via callback
}