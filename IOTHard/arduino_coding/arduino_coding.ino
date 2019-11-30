#include <ESP8266WiFi.h>
#include <SocketIOClient.h>
#include <ArduinoJson.h>

//CONVERT JSON DATA______________________________________________________________________________________________________________________-
typedef struct belt{
  bool status = false;
  int speed = 0;
}AZBelt;

typedef struct arm{
  int x = 0;
  int y = 0;
  int z = 0;
  int joint1 = 0;
  int joint2 = 0;
  int joint3 = 0;
  int joint4 = 0;
  int joint5 = 0;
  int joint6 = 0;
}AZArm;

typedef struct Bot {
  AZBelt belt;
  AZArm arm;
} AZBot;

AZBot bot;

void printTest(AZBot botx){
  Serial.print("Bot belt status : "); Serial.println(botx.belt.status);
  Serial.print("Bot belt speed : "); Serial.println(botx.belt.speed);
  Serial.print("Bot arm x : "); Serial.println(botx.arm.x);
  Serial.print("Bot arm y : "); Serial.println(botx.arm.y);
  Serial.print("Bot arm z : "); Serial.println(botx.arm.z);
  Serial.print("Bot arm joint1 : "); Serial.println(botx.arm.joint1);
  Serial.print("Bot arm joint2 : "); Serial.println(botx.arm.joint2);
  Serial.print("Bot arm joint3 : "); Serial.println(botx.arm.joint3);
  Serial.print("Bot arm joint4 : "); Serial.println(botx.arm.joint4);
  Serial.print("Bot arm joint5 : "); Serial.println(botx.arm.joint5);
  Serial.print("Bot arm joint6 : "); Serial.println(botx.arm.joint6);
  Serial.println("_________________________________END STEP________________________________");
}


bool convertJson2Data(String json){
  DynamicJsonDocument doc(1400);
  deserializeJson(doc, json);
  serializeJson(doc,Serial);
  // Set Value to bot iot struct
  // belt
  bot.belt.status = doc["beltObj"]["status"];
  bot.belt.speed = doc["beltObj"]["speed"];
  // arm
  bot.arm.x = doc["armObj"]["x"];
  bot.arm.y = doc["armObj"]["y"];
  bot.arm.z = doc["armObj"]["z"];
  bot.arm.joint1 = doc["armObj"]["joint1"];
  bot.arm.joint2 = doc["armObj"]["joint2"];
  bot.arm.joint3 = doc["armObj"]["joint3"];
  bot.arm.joint4 = doc["armObj"]["joint4"];
  bot.arm.joint5 = doc["armObj"]["joint5"];
  bot.arm.joint6 = doc["armObj"]["joint6"];
  Serial.println("");
  printTest(bot);
  doc.clear();
}
//SOCKET SERVER__________________________________________________________________________________________________________________

SocketIOClient client;
const char* ssid = "LovingU";          //Tên mạng Wifi mà Socket server của bạn đang kết nối
const char* password = "10051999";  //Pass mạng wifi ahihi, anh em rãnh thì share pass cho mình với.

 char host[] = "192.168.43.151"; int port = 5000;
//char host[] = "azbot-iot-demo.herokuapp.com"; int port = 80;//Cổng dịch vụ socket server do chúng ta tạo!
 
//từ khóa extern: dùng để #include các biến toàn cục ở một số thư viện khác. Trong thư viện SocketIOClient có hai biến toàn cục
// mà chúng ta cần quan tâm đó là
// RID: Tên hàm (tên sự kiện
// Rfull: Danh sách biến (được đóng gói lại là chuối JSON)
extern String RID;
extern String Rfull;
 
 
//Một số biến dùng cho việc tạo một task
 
void setup()
{
    //Bật baudrate ở mức 115200 để giao tiếp với máy tính qua Serial
    Serial.begin(115200);
    delay(10);
 
    //Việc đầu tiên cần làm là kết nối vào mạng Wifi
    Serial.print("Ket noi vao mang ");
    Serial.println(ssid);
 
    //Kết nối vào mạng Wifi
    WiFi.begin(ssid, password);
 
    //Chờ đến khi đã được kết nối
    while (WiFi.status() != WL_CONNECTED) { //Thoát ra khỏi vòng 
        delay(500);
        Serial.print('.');
    }
 
    Serial.println();
    Serial.println(F("Da ket noi WiFi"));
    Serial.println(F("Di chi IP cua ESP8266 (Socket Client ESP8266): "));
    Serial.println(WiFi.localIP());
 
    if (!client.connect(host, port)) {
        Serial.println(F("Ket noi den socket server that bai!"));
        return;
    }
 
    //Khi đã kết nối thành công
    if (client.connected()) {
        Serial.println(F("Ket noi den socket server thanh cong!"));
        //Thì gửi sự kiện ("connection") đến Socket server ahihi.
        client.send("espid", "message", "ESP8266 Connected !!!!");
    }
}
void loop()
{
  
    if (client.monitor()) {
      convertJson2Data(Rfull);
    }
 
    //Kết nối lại!
    if (!client.connected()) {
      client.reconnect(host, port);
    }
}
