// Sending/Receiving example
#include <Arduino.h>
#include <HardwareSerial.h>
#include <WiFiClientSecure.h>
#include <ESP_Line_Notify.h>

HardwareSerial Receiver(2); // Define a Serial port instance called 'Receiver' using serial port 2

#define Receiver_Txd_pin 17
#define Receiver_Rxd_pin 16

#define SSID "vvieww"     
#define PASSWORD "qwerty555"    
#define LINE_TOKEN  "ZUcJzVITHhNfX6PUVBZ8kWtA4BNJRIHz175BKs38us1" 

LineNotifyClient line;

int is_uart_recv=0;
int recv_state;

String mystring1 = "";

void NotifyLine(String t){
    line.token = LINE_TOKEN;
    line.message = t;
    LineNotifySendingResult result = LineNotify.send(line);
    if (result.status == LineNotify_Sending_Success){
      Serial.printf("Status: %s\n", "success");
    }else if (result.status == LineNotify_Sending_Error){
      Serial.printf("Status: %s\n", "error");
    }
}

void setup() {
  //Serial.begin(Baud Rate, Data Protocol, Txd pin, Rxd pin);
  Serial.begin(115200);                                                   // Define and start serial monitor
  Receiver.begin(115200, SERIAL_8N1, Receiver_Txd_pin, Receiver_Rxd_pin); // Define and start Receiver serial port

  // WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
  }
  
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());
}

void loop() {

 if (is_uart_recv == 0){
    while (Receiver.available()) {                         // Wait for the Receiver to get the characters
      recv_state = Receiver.parseInt(); // Display the Receivers characters
      Serial.println(recv_state);              // Display the result on the serial monitor
      is_uart_recv = 1;
    }
 }

 else if (is_uart_recv == 1){
  Serial.println(recv_state); 
  if (recv_state == 1){
    mystring1 = "เหรียญ 1 บาทหมดจ้า";
    NotifyLine(mystring1);
  }

  else if (recv_state == 2){
    mystring1 = "เหรียญ 5 บาทหมดจ้า";
    NotifyLine(mystring1);
  }

  else if (recv_state == 3){
    mystring1 = "เหรียญหมดตู้ทุกชนิดเลยจ้า";
    NotifyLine(mystring1);
  }

  else if (recv_state == 4){
    mystring1 = "ถังขยะโล่งแล้วจ้า";
    NotifyLine(mystring1);
  }

  else if (recv_state > 500){
    mystring1 = "ถังโลหะเต็มจ้า";
    NotifyLine(mystring1);
  }

  else if (recv_state > 100){
    mystring1 = "ถังพลาสติกเต็มจ้า";
    NotifyLine(mystring1);
  }

  is_uart_recv=0;
 }
  
}