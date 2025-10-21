#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "@iot";
const char* password = "12345678";

const char* serverName = "http://192.168.20.48/iot/insert_data.php";

void setup() {
  Serial.begin(115200);

  // Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String fullname = "สมชาย ใจดี";
    String number = "12345";

    // สร้าง URL พร้อมส่งค่า GET
    String url = String(serverName) + "?fullname=" + urlencode(fullname) + "&number=" + number;

    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("Response: " + payload);
    } else {
      Serial.println("Error in sending request");
    }

    http.end();
  } else {
    Serial.println("WiFi disconnected!");
  }

  delay(10000); // ส่งทุกๆ 10 วินาที
}

// ฟังก์ชัน urlencode สำหรับรองรับข้อความไทย
String urlencode(String str) {
  String encodedString = "";
  char c;
  char code0;
  char code1;
  char code2;
  for (int i = 0; i < str.length(); i++) {
    c = str.charAt(i);
    if (isalnum(c)) {
      encodedString += c;
    } else {
      encodedString += '%';
      code1 = (c >> 4) & 0xF;
      if (code1 > 9) code1 += 'A' - 10;
      else code1 += '0';
      encodedString += code1;
      code0 = c & 0xF;
      if (code0 > 9) code0 += 'A' - 10;
      else code0 += '0';
      encodedString += code0;
    }
  }
  return encodedString;
}
