#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

DynamicJsonDocument doc(1024);

const char *ssid = "Ai-Photonics"; // Enter your WiFi name
const char *password = "ptit@123";  // Enter WiFi password
const char *mqtt_broker = "Mqtt.mysignage.vn";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

char count_string = 0;
char arr_received1[50], count_string1 = 0;
unsigned int Count_Time = 0, Split_count = 0;
char temp_char, arr_received[15], *temp[15];

void Send_ControlRelay(unsigned char Relay1_Stt, unsigned char Relay2_Stt);
void callback(char *topic, byte *payload, unsigned int length);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.println("Connecting to WiFi..");
  }
  //Serial.println("Connected to the WiFi network");

  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);

  while (!client.connected()) {
    //Serial.println("Connecting to public emqx mqtt broker.....");
    if (client.connect("esp8266-client")) {
      //Serial.println("Public emqx mqtt broker connected");
    } else {
      //Serial.print("failed with state ");
      //Serial.print(client.state());
      delay(2000);
    }
  }
  client.subscribe("hethongnhung/control");
}

void callback(char *topic, byte *payload, unsigned int length) {
  for (int i = 0; i < length; i++) 
  {
    char temp_char1 =  (char)payload[i];
    arr_received1[count_string1++] = temp_char1;
  }
  if(arr_received1[0] == '0' && arr_received1[2] == '0')
  {
    Send_ControlRelay(0,0);
  }
  else  if(arr_received1[0] == '1' && arr_received1[2] == '0')
  {
    Send_ControlRelay(1,0);
  }
  else  if(arr_received1[0] == '0' && arr_received1[2] == '1')
  {
    Send_ControlRelay(0,1);
  }
  else  if(arr_received1[0] == '1' && arr_received1[2] == '1')
  {
    Send_ControlRelay(1,1);
  }
  memset(arr_received1, 0, sizeof(arr_received1));
  count_string1 = 0;
}

void loop() {
if (Serial.available())
  {
    char temp_char = Serial.read();
    if (temp_char == '!')
    {
      char Buffer[1000];
      unsigned int Len_Buffer;
      String ESP32_to_Web_Json = "";
      Split_count = 0;
      count_string = 0;
      temp[0] = strtok(arr_received, " ");
      while (temp[Split_count] != NULL)
      {
        Split_count++;
        temp[Split_count] = strtok(NULL, " ");
      }
      ESP32_to_Web_Json = "{\"Temp\":\"" + String(temp[0]) + "\"," "\"Humi\":\"" + String(temp[1]) + "\"," "\"Soil\":\"" + String(temp[2]) + "\"," "\"Light\":\"" + String(temp[3]) + "\"}";
      Len_Buffer = ESP32_to_Web_Json.length()+1;
      ESP32_to_Web_Json.toCharArray(Buffer,Len_Buffer);
      client.connect("ESP8266Client1");
      client.publish("hethongnhung/sensor", Buffer);
      memset(arr_received, 0, sizeof(arr_received));
      
    }
    else
    {
       arr_received[count_string++] = temp_char;
    }
  }

  client.loop();
}

void Send_ControlRelay(unsigned char Relay1_Stt, unsigned char Relay2_Stt)
{
  char ArrData[10] = "";
  sprintf(ArrData, "%d %d!", Relay1_Stt, Relay2_Stt);
  Serial.print(ArrData);
}