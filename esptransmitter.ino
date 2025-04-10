#include <WiFi.h>
#include <esp_now.h>

// Structure to hold radar data
typedef struct struct_message {
  int angle;
  int distance;
} struct_message;

struct_message myData;

// Callback when data is sent via ESP‑NOW
void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("ESP‑NOW Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void setup() {
  Serial.begin(115200);                // For debugging output
  Serial2.begin(9600, SERIAL_8N1, 16, 17); // Use Serial2: RX = GPIO 16 (from Arduino TX), TX = GPIO 17 (unused here)

  // Set ESP32 in STA mode
  WiFi.mode(WIFI_STA);
  
  // Initialize ESP‑NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP‑NOW");
    return;
  }
  
  // Register send callback
  esp_now_register_send_cb(onDataSent);
  
  // Set up a broadcast peer (send to all)
  esp_now_peer_info_t peerInfo;
  memset(&peerInfo, 0, sizeof(peerInfo));
  uint8_t broadcastAddress[] = {0x78, 0x42, 0x1C, 0x6D, 0x32, 0xB8};
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  // Read data from Arduino via Serial2. Data format: "angle,distance."
  if (Serial2.available()) {
    String dataStr = Serial2.readStringUntil('.');  // Read until '.' marker
    dataStr.trim();  // Remove whitespace
    
    int commaIndex = dataStr.indexOf(',');
    if (commaIndex != -1) {
      String angleStr = dataStr.substring(0, commaIndex);
      String distanceStr = dataStr.substring(commaIndex + 1);
      
      myData.angle = angleStr.toInt();
      myData.distance = distanceStr.toInt();
      
      // Print the received data on the transmitter ESP32
      Serial.print("Transmitter Received -> Angle: ");
      Serial.print(myData.angle);
      Serial.print("°, Distance: ");
      Serial.print(myData.distance);
      Serial.println(" cm");
      
      // Send the data via ESP‑NOW (broadcast)
      esp_err_t result = esp_now_send(NULL, (uint8_t *)&myData, sizeof(myData));
      if (result == ESP_OK) {
        Serial.println("ESP‑NOW send: Success");
      } else {
        Serial.println("ESP‑NOW send: Fail");
      }
    }
  }
}
