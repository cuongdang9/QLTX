#include <WiFi.h>
#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
const char* ssid = "pornhub";
const char* password = "0327614010";
AsyncWebServer serverSmartPhone(80);
AsyncEventSource events("/events");
#include "web.h"
#include "web1.h"
const char* mDNSname = "esp";
#include <Ticker.h>
Ticker ticker;
//==========================================================================
unsigned long last = millis();
unsigned long LastQuetThe1 = millis();
int QuetThe1 = 0;
unsigned long LastQuetThe2 = millis();
int QuetThe2 = 0;

String  DataWeb = "";
const char* linkKiemtraThe = "http://192.168.12.54:8080/DATAESP32RFIDACS712/kiemtramathehethong.php";
const char* linkThemThe = "http://192.168.12.54:8080/DATAESP32RFIDACS712/themthe.php";
const char* linkLuuThongTin = "http://192.168.12.54:8080/DATAESP32RFIDACS712/luuthongtin.php";
const char* linkXoaThe = "http://192.168.12.54:8080/DATAESP32RFIDACS712/xoathe.php";
const char* linkSuaThongTin = "http://192.168.12.54:8080/DATAESP32RFIDACS712/suathongtin.php";
const char* linkReset = "http://192.168.12.54:8080/DATAESP32RFIDACS712/reset.php";
const char* linkLuuThongTinPhanCung = "http://192.168.12.38:80/DATAESP32RFIDACS712/luuthongtinphancung.php";
const char* linkKiemtraThePhanCung = "http://192.168.12.38:80/DATAESP32RFIDACS712/kiemtramathehethongphancung.php";
String DataWebKiemTra = "";
String MaThe1 = "";
String Data = "";
String DataWebThemThe = "{\"A\":\"123\"}";
String mathe = "...";
String hoten = "...";
String sdt = "...";
String biensoxe = "0";
String dongdien = "0";
String congsuat = "0";
String sotien = "0";
String Mathe2 = "";
String DataWebThemXoaThe = "";
String IP = "";
String str1 = "";
String str2 = "";
String str3 = "";
String str4 = "";
String dongdien1 = "";
String congsuat1 = "";
String sotien1 = "";
String mathe1 = "";
String DataWebKiemTraTheThemSuaXoa = "";
int StartPhanCung = 0;
unsigned long lastLCD = millis();
//==========================================================================
//RFID RC522
#include <SPI.h>
#include <MFRC522.h>
#define HSPI_MISO 12
#define HSPI_MOSI 13
#define HSPI_SCLK 14
#define HSPI_SS 15
#define RST_PIN  16
MFRC522 mfrc522(HSPI_SS, RST_PIN);
String MaThe = "null";
String LastMaThe = "";
String LastMaThe1 = "";
void Read_RFID(void);


//==========================================================================
//BUZZER
#define Buzzer 23
#define Buzzer_ON digitalWrite(Buzzer,HIGH)
#define Buzzer_OFF digitalWrite(Buzzer,LOW)
//==========================================================================
//RELAY
#define Relay 19
#define Relay_ON digitalWrite(Relay,HIGH)
#define Relay_OFF digitalWrite(Relay,LOW)
int TT_RELAY = 0;
//==========================================================================
//LED IO2
#define LED 2
//==========================================================================
//LCD I2C 2004
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#define I2C_SDA 21
#define I2C_SCL 22
//==========================================================================
//NÚT NHẤN
#define Nut1 4
#define Nut2 17
#define Nut3 5
#define Nut4 18
#define Data_Nut1 digitalRead(Nut1)
#define Data_Nut2 digitalRead(Nut2)
#define Data_Nut3 digitalRead(Nut3)
#define Data_Nut4 digitalRead(Nut4)

//==========================================================================
//ACS712 ĐỌC DÒNG TIÊU THỤ
const int Sensor_Pin = 32;
unsigned int Sensitivity = 185;   // 185mV/A for 5A, 100 mV/A for 20A and 66mV/A for 30A Module
float Vpp = 0; // peak-peak voltage
float Vrms = 0; // rms voltage
float Irms = 0; // rms current
float Supply_Voltage = 12.0;           // reading from DMM
float Vcc = 5.0;          // ADC reference voltage // voltage at 5V pin
float power = 0;          // power in watt
float Wh = 0 ;            // Energy in kWh
unsigned long last_time = 0;
unsigned long current_time = 0;
unsigned long interval = 66;
unsigned int calibration = 66;  // V2 slider calibrates this
unsigned int pF = 100;            // Power Factor default 95
float bill_amount = 0;           // 30 day cost as present energy usage incl approx PF
float energyTariff = 2.3;        // Energy cost in INR per unit (kWh)
const int sw = 4;               // Switch connect pin
float hieuchinh = 0.3;
/*==================================*/
//doc gia tri dong dien, tinh cong suat va tinh gia tien

void getACS712()
{
  /*
    Vpp = getVPP();
    Vrms = (Vpp / 2.0) * 0.707;//0.707
    //Vrms = Vrms - (calibration / 10000.0);     // calibtrate to zero with slider
    Irms = ((Vrms * 1000) / Sensitivity) - hieuchinh;
    Serial.print("Irms:  ");
    Serial.print(String(Irms + hieuchinh, 3));
    Serial.println(" A");
    if ((Irms > -0.3) && (Irms < 0.1))        // remove low end chatter
    {
    Irms = 0.0;
    }
    power = (Supply_Voltage * Irms) * (pF / 100.0); // P = u*i*cosphi
    last_time = current_time;
    current_time = millis();
    Wh = Wh +  power * (( current_time - last_time) / 3600000.0) ; // calculating energy in Watt-Hour
    bill_amount = Wh * (energyTariff);

    //eeprom_write_float((float*)Address_wh , Wh);
    delay(10);

    Serial.print("Irms:  ");
    Serial.print(String(Irms, 3));
    Serial.println(" A");
    Serial.print("Power: ");
    Serial.print(String(power, 3));
    Serial.println(" W");

    Serial.print("Wh: ");
    Serial.print(String(Wh, 3));
    Serial.println(" KWh");

    Serial.print("Tiền điện: ");
    Serial.print(String(bill_amount, 3));
    Serial.println(" Đồng");

    dongdien = String(Irms, 3);
    congsuat = String(Wh, 3);
    sotien = String(bill_amount, 3);

    Serial.print("dongdien: ");
    Serial.print(dongdien);
    Serial.print(" A");
    Serial.print(" - congsuat: ");
    Serial.print(congsuat);
    Serial.print(" Wh");
    Serial.print(" - sotien: ");
    Serial.print(sotien);
    Serial.println(" VND");
  */
  /*
    float average = 0;
    for(int i = 0; i < 1000; i++) {
    average = average + (.044 * analogRead(Sensor_Pin) -3.78) / 1000;

    //5A mode, if 20A or 30A mode, need to modify this formula to
    //(.19 * analogRead(A0) -25) for 20A mode and
    //(.044 * analogRead(A0) -3.78) for 30A mode

    delay(1);
    }
    Serial.println(average);
  */

  int mVperAmp = 66; // 66 mV/A output sensitivity
  unsigned long RawValue = 0;
  int ACSoffset = 5500 / 2;
  double Voltage = 0;
  double Amps = 0;
  int count1 = 0;
  for (int i = 0 ; i < 500; i++)
  {
    count1++;
    RawValue += analogRead(Sensor_Pin);
    delay(1);
  }
  RawValue = RawValue / count1;
  Voltage = (RawValue / 4095.0) * 5000; // Gets you mV
  Amps = ((Voltage - ACSoffset) / mVperAmp);
  Serial.print("Raw Value = " ); // shows pre-scaled value
  Serial.print(RawValue);
  Serial.print("\t mV = "); // shows the voltage measured
  Serial.print(Voltage, 3);
  Serial.print("\t Amps = ");
  Serial.println(Amps, 3);

  yield();


}

float getVPP()
{
  float result;
  int readValue;
  int maxValue = 0;
  int minValue = 4095;
  uint32_t start_time = millis();
  while ((millis() - start_time) < 950) //read every 0.95 Sec
  {
    readValue = analogRead(Sensor_Pin);
    if (readValue > maxValue)
    {
      maxValue = readValue;
    }
    if (readValue < minValue)
    {
      minValue = readValue;
    }
  }
  result = ((maxValue - minValue) * Vcc) / 4095.0;
  return result;
}

String DataWebXoaThe = "";
String MaTheXoa = "";
String  DataSuaThe = "";
String DataWebSuaThe = "";
String  mathesua = "";
String hotensua = "";
String sdtsua = "";
String biensoxesua = "";

String  MatheReset = "";
String DataWebReset = "";

int clientconnect = 0;
unsigned long LastClient = millis();

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  pinMode(Sensor_Pin, INPUT);

  Begin_OUTPUT();
  Begin_INPUT();
  BeginLCD();
  SPI.begin(HSPI_SCLK, HSPI_MISO, HSPI_MOSI);
  mfrc522.PCD_Init();
  delay(100);
  ConnectWiFi();
  serverSmartPhone.on("/", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    request->send_P(200, "text/html", index_smartphone);
    yield();
    clientconnect = 1;
    LastClient = millis();
    lastLCD = millis();
  });
  serverSmartPhone.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    request->send_P(200, "text/html", index_smartphone);
    yield();
    clientconnect = 1;
    LastClient = millis();
    lastLCD = millis();
  });

  serverSmartPhone.on("/Update", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    Serial.println("Update Hệ thống!!!");
    clientconnect = 1;
    LastClient = millis();
    lastLCD = millis();
    JsonSendWeb();
    request->send_P(200, "text/html", DataWeb.c_str());
    yield();
    MaThe = "null";

  });
  serverSmartPhone.on("/UpdateThemSuaXoa", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    Serial.println("Update Them Sua Xoa!!!");
    clientconnect = 1;

    JsonSendWebThemSuaXoa();
    request->send_P(200, "text/html", DataWebThemXoaThe.c_str());
    MaThe = "null";
    LastClient = millis();
    lastLCD = millis();
  });

  serverSmartPhone.on("/KiemTraTheThemSuaXoa", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    Serial.println("KiemTraTheThemSuaXoa!!!");
    int paramsNr = request->params();
    for (int i = 0; i < paramsNr; i++)
    {
      AsyncWebParameter* p = request->getParam(i);
      MaThe1 = "";
      MaThe1 = p->value();
      Serial.print("MaThe1: ");
      Serial.println(MaThe1);
    }
    clientconnect = 1;
    LastClient = millis();
    JsonSendWebKiemTraTheThemSuaXoa();
    request->send_P(200, "text/html", DataWebKiemTraTheThemSuaXoa.c_str());
    yield();
    LastClient = millis();
    lastLCD = millis();
  });

  serverSmartPhone.on("/XoaThe", HTTP_GET, [](AsyncWebServerRequest * request)
  {

    int paramsNr = request->params();
    for (int i = 0; i < paramsNr; i++)
    {
      AsyncWebParameter* p = request->getParam(i);
      MaTheXoa = "";
      MaTheXoa = p->value();
      Serial.print("MaTheXoa: ");
      Serial.println(MaTheXoa);
    }
    clientconnect = 1;
    LastClient = millis();
    JsonSendWebXoaThe();
    request->send_P(200, "text/html", DataWebXoaThe.c_str());
    yield();
    LastClient = millis();
    lastLCD = millis();

  });

  serverSmartPhone.on("/SuaThe", HTTP_GET, [](AsyncWebServerRequest * request)
  {

    int paramsNr = request->params();
    for (int i = 0; i < paramsNr; i++)
    {
      AsyncWebParameter* p = request->getParam(i);
      DataSuaThe = "";
      DataSuaThe = p->value();
      Serial.print("DataSuaThe: ");
      Serial.println(DataSuaThe);
      ParseJsonSuaThe(String(DataSuaThe));
    }
    clientconnect = 1;
    LastClient = millis();
    JsonSendWebSuaThe();
    request->send_P(200, "text/html", DataWebSuaThe.c_str());
    yield();
    LastClient = millis();
    lastLCD = millis();
  });


  serverSmartPhone.on("/Reset", HTTP_GET, [](AsyncWebServerRequest * request)
  {

    int paramsNr = request->params();
    for (int i = 0; i < paramsNr; i++)
    {
      AsyncWebParameter* p = request->getParam(i);
      MatheReset = "";
      MatheReset = p->value();
      Serial.print("MatheReset: ");
      Serial.println(MatheReset);

    }
    clientconnect = 1;
    LastClient = millis();
    JsonSendWebReset();

    request->send_P(200, "text/html", DataWebReset.c_str());
    yield();
    LastClient = millis();
    lastLCD = millis();
  });

  serverSmartPhone.on("/KiemTra", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    Serial.println("Kiểm tra thẻ");
    int paramsNr = request->params();
    for (int i = 0; i < paramsNr; i++)
    {
      AsyncWebParameter* p = request->getParam(i);
      MaThe1 = "";
      MaThe1 = p->value();
      Serial.print("MaThe1: ");
      Serial.println(MaThe1);
      Mathe2 = MaThe1;
    }
    clientconnect = 1;
    LastClient = millis();
    KiemTraThe();
    request->send_P(200, "text/html", DataWebKiemTra.c_str());
    yield();
    LastClient = millis();
    lastLCD = millis();
  });
  serverSmartPhone.on("/ThemThe", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    Serial.println("Thêm Thẻ?");
    int paramsNr = request->params();
    for (int i = 0; i < paramsNr; i++)
    {
      AsyncWebParameter* p = request->getParam(i);
      Data = "";
      Data = p->value();
      Serial.print("Data: ");
      Serial.println(Data);
      ParseJson(String(Data));
    }
    ThemThe();
    request->send_P(200, "text/html", DataWebThemThe.c_str());
    yield();
    LastClient = millis();
    lastLCD = millis();
  });
  serverSmartPhone.on("/Relay", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    Serial.println("Điều khiển Relay?");
    int paramsNr = request->params();
    for (int i = 0; i < paramsNr; i++)
    {
      AsyncWebParameter* p = request->getParam(i);
      MaThe1 = "";
      MaThe1 = p->value();
      Serial.print("MaThe1: ");
      Serial.println(MaThe1);
      ParseJson1(String(MaThe1));
    }
    if (mathe1 = Mathe2)
    {
      if (TT_RELAY == 0)
      {

        TT_RELAY = 1;
        Relay_ON;
        QuetThe1 = 0;
        QuetThe2 = 0;
        Serial.println("Relay ON");
        yield();
      }
      else if (TT_RELAY == 1)
      {

        TT_RELAY = 0;
        Relay_OFF;
        LuuThongTin();
        QuetThe1 = 0;
        QuetThe2 = 0;
        lcd.clear();  yield();
        Serial.println("Relay OFF");
      }
    }
    String TX = "{\"RL\":\"" + String(TT_RELAY) + "\"}";
    request->send_P(200, "text/html", TX.c_str());
    LastClient = millis();
    lastLCD = millis();
  });
  serverSmartPhone.begin();
  Serial.println("Server start connect wifi!!!");
  OpenDNS(); delay(200);
  HienThiLCD(); delay(200);
  lastLCD = millis();

}

void loop()
{
  if (clientconnect)
  {
    if (TT_RELAY == 0)
    {

      Read_RFID_1(); delay(100);
    }
    else if (TT_RELAY == 1)
    {

      Read_RFID_2(); delay(100);
    }


    if (millis() - last >= 1000)
    {
      if (TT_RELAY == 1)
      {
        getACS712();
        HienThiLCD();
        yield();
        Serial.println("===============================");
      }
      last = millis();
    }
  }
  KiemTraClient();
  PrintClient();
  delay(1);
  
  // PhanCungKiemTraThe();
  // PhanCungStopRelay();
}
void PrintClient()
{
  if (millis() - lastLCD >= 1000)
  {
    if (clientconnect)
    {
      Serial.println("Client Connect!!!");
    }
    else
    {
      Serial.println("Client Not Connect!!!");
    }
    yield();
    lastLCD = millis();
  }
}
void PhanCungStopRelay()
{
  if (clientconnect == 0)
  {
    if (QuetThe2 == 1)
    {
      if (millis() - LastQuetThe2 >= 2000)
      {
        //LastMaThe1
        LuuThongSoMySQLPhanCung();
        QuetThe2 = 0;
      }
    }
  }

}
void PhanCungKiemTraThe()
{
  if (clientconnect == 0)
  {
    if (QuetThe1 == 1)
    {
      if (millis() - LastQuetThe1 >= 5000)
      {
        MaThe1 = LastMaThe;
        KiemTraThePhanCung();
        QuetThe1 = 0;
        Serial.print(">>>>>>>>>Phan cứng Kiểm tra thẻ MaThe1:");
        Serial.println(MaThe1);
        Serial.println("=============================================");
      }
    }
  }


}
void KiemTraClient()
{
  if (clientconnect == 1)
  {
    if (millis() - LastClient >= 15000)
    {
      Serial.println("Client Disconnect!!!");
      clientconnect = 0;
    }
  }

}
void ButtonResset()
{
  if (Data_Nut1 == 0)
  {
    delay(200);
    Serial.println("Nút nhấn reset được nhấn!!!");
    while (1)
    {
      if (Data_Nut1 == 1)
      {

        delay(200);
        break;
      }
    }

  }
}
void LuuThongTin()
{
  //MaThe1: 90697721
  //linkLuuThongTin
  HTTPClient http;
  String serverPath = "";
  serverPath += linkLuuThongTin;
  serverPath += String("?mathe=");
  serverPath += String(mathe1);
  serverPath += String("&dongdien=");
  serverPath += String(dongdien1);
  serverPath += String("&congsuat=");
  serverPath += String(congsuat1);
  serverPath += String("&sotien=");
  serverPath += String(sotien1);
  Serial.print("serverPath:");
  Serial.println(serverPath);
  http.begin(serverPath.c_str());

  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code Luu thong tin: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);

  }
  else
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);

  }

  http.end();
  yield();

}
void KiemTraThe()
{
  DataWebKiemTra = "";
  HTTPClient http;
  String serverPath = "";
  serverPath += linkKiemtraThe;
  serverPath += String("?mathe=");
  serverPath += String(MaThe1);
  Serial.print("serverPath KiemTraThe:");
  Serial.println(serverPath);
  http.begin(serverPath.c_str());
  int httpResponseCode = http.GET();delay(100);
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
    ParseJson(String(payload));
    DataWebKiemTra = String(payload);

  }
  else
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    DataWebKiemTra = "{\"Data\":\"Err\"}";
  }

  http.end();


  yield();
  Serial.println("==================================================================");

}

void ThemThe()
{
  DataWebThemThe = "";
  HTTPClient http;
  String serverPath = "";
  serverPath += linkThemThe;
  serverPath += String("?mathe=");
  serverPath += String(MaThe1);
  serverPath += String("&hoten=");
  serverPath += String(hoten);
  serverPath += String("&sdt=");
  serverPath += String(sdt);
  serverPath += String("&biensoxe=");
  serverPath += String(biensoxe);
  serverPath += String("&dongdien=");
  serverPath += String(dongdien);
  serverPath += String("&congsuat=");
  serverPath += String(congsuat);
  serverPath += String("&sotien=");
  serverPath += String(sotien);
  Serial.print("serverPath:");
  Serial.println(serverPath);
  http.begin(serverPath.c_str());
  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
    DataWebThemThe = String(payload);
  }
  else
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    DataWebThemThe = "{\"Data\":\"AddErr\"}";
  }

  http.end();
  yield();
  Serial.println("==================================================================");
}
void ParseJson(String Data)
{
  const size_t capacity = JSON_OBJECT_SIZE(4) + 400;
  DynamicJsonDocument JSON(capacity);
  DeserializationError error = deserializeJson(JSON, Data);
  if (error)
  {
    return;
  }
  else
  {
    Serial.println();
    Serial.println("Data JSON Database ESP: ");
    serializeJsonPretty(JSON, Serial);
    Serial.println();
    mathe = "";
    hoten = "";
    sdt = "";
    biensoxe = "";
    dongdien = "";
    congsuat = "";
    sotien = "";
    if (JSON.containsKey("mathe"))
    {
      String Data_mathe = JSON["mathe"];
      mathe = Data_mathe;
      Serial.print("mathe:");
      Serial.println(mathe);
    }
    if (JSON.containsKey("hoten"))
    {
      String Data_hoten = JSON["hoten"];
      hoten = Data_hoten;
      Serial.print("hoten:");
      Serial.println(hoten);
    }

    if (JSON.containsKey("sdt"))
    {
      String Data_sdt = JSON["sdt"];
      sdt = Data_sdt;
      Serial.print("sdt:");
      Serial.println(sdt);
    }

    if (JSON.containsKey("biensoxe"))
    {
      String Data_biensoxe = JSON["biensoxe"];
      biensoxe = Data_biensoxe;
      Serial.print("biensoxe:");
      Serial.println(biensoxe);
    }

    if (JSON.containsKey("dongdien"))
    {
      String Data_dongdien = JSON["dongdien"];
      dongdien = Data_dongdien;
      Serial.print("dongdien:");
      Serial.println(dongdien);
    }

    if (JSON.containsKey("congsuat"))
    {
      String Data_congsuat = JSON["congsuat"];
      congsuat = Data_congsuat;
      Serial.print("congsuat:");
      Serial.println(congsuat);
    }

    if (JSON.containsKey("sotien"))
    {
      String Data_sotien = JSON["sotien"];
      sotien = Data_sotien;
      Serial.print("sotien:");
      Serial.println(sotien);
    }
    bill_amount = sotien.toFloat();
    Wh = congsuat.toFloat();
    Irms = dongdien.toFloat();
    Serial.print("Irms: ");
    Serial.print(Irms);
    Serial.print(" A");
    Serial.print(" - Wh: ");
    Serial.print(Wh);
    Serial.print(" Wh");
    Serial.print(" - bill_amount: ");
    Serial.print(bill_amount);
    Serial.println(" VND");
    yield();
    JSON.clear();
  }
}
void tick()
{
  digitalWrite(LED, !digitalRead(LED));
}
void OpenDNS(void)
{
  delay(500);
  if (MDNS.begin(mDNSname)) {
    Serial.println("mDNS Start:");
    Serial.print(String(mDNSname));
    Serial.println(".local");
    MDNS.addService("http", "tcp", 80);
  }
}
void JsonSendWeb()
{

  DataWeb = "";
  if (TT_RELAY == 0)
  {
    DataWeb  = "{\"MaThe\":\"" + String(MaThe) + "\",\"RL\":\"" + String(TT_RELAY) + "\"}";
  }
  else if (TT_RELAY == 1)
  {
    DataWeb  = "{\"MaThe\":\"" + String(MaThe) + "\"," +
               "\"MaThe1\":\"" + String(LastMaThe) + "\"," +
               "\"RL\":\"" + String(TT_RELAY) + "\"," +
               "\"hoten\":\"" + String(hoten) + "\"," +
               "\"sdt\":\"" + String(sdt) + "\"," +
               "\"biensoxe\":\"" + String(biensoxe) + "\"," +
               "\"dongdien\":\"" + String(dongdien) + "\"," +
               "\"congsuat\":\"" + String(congsuat) + "\"," +
               "\"sotien\":\"" + String(sotien) + "\"}";

  }
  yield();

}
void BeginLCD()
{
  Wire.begin(I2C_SDA , I2C_SCL);
  lcd.begin(20, 4);
  lcd.init();
  lcd.backlight();
  lcd.display();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" IOT SMART HOME -- 00");
  lcd.setCursor(0, 1);
  lcd.print("HELLO ESP32 -- 11");
  lcd.setCursor(0, 2);
  lcd.print("HELLO ESP32 -- 22");
  lcd.setCursor(0, 3);
  lcd.print("HELLO ESP32 -- 33");
  Serial.println("LCD OK!!!");
}
void Begin_OUTPUT()
{
  pinMode(Buzzer, OUTPUT); pinMode(Relay, OUTPUT); pinMode(LED, OUTPUT);
  Buzzer_OFF; Relay_OFF; digitalWrite(LED, HIGH);
}
void  Begin_INPUT()
{
  pinMode(Nut1, INPUT_PULLUP); pinMode(Nut2, INPUT_PULLUP); pinMode(Nut3, INPUT_PULLUP); pinMode(Nut4, INPUT_PULLUP);
}
void Read_RFID_1()
{
  if (mfrc522.PICC_IsNewCardPresent())
  {
    if (mfrc522.PICC_ReadCardSerial())
    {
      MaThe = "";
      for (byte i = 0; i < mfrc522.uid.size; i++)
      {
        MaThe.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
        MaThe.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
      QuetThe1 = 1;
      LastQuetThe1 = millis();
      if (TT_RELAY == 0)
      {
        LastMaThe = MaThe;
      }

      Serial.print("MaThe:");
      Serial.println(MaThe);
      Serial.print("LastMaThe:");
      Serial.println(LastMaThe);
      Buzzer_ON; delay(100); Buzzer_OFF;
      HienThiLCD();
      mfrc522.PICC_HaltA();
    }
  }
}
void Read_RFID_2()
{
  if (mfrc522.PICC_IsNewCardPresent())
  {
    if (mfrc522.PICC_ReadCardSerial())
    {
      LastMaThe1 = "";
      for (byte i = 0; i < mfrc522.uid.size; i++)
      {
        LastMaThe1.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
        LastMaThe1.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
      if (LastMaThe1 == LastMaThe)
      {
        MaThe = LastMaThe1;
        LastQuetThe2 = millis();
        QuetThe2 = 1;
      }

      Serial.print("MaThe:");
      Serial.println(MaThe);
      Buzzer_ON; delay(100); Buzzer_OFF;
      HienThiLCD();
      mfrc522.PICC_HaltA();
    }
  }
}
void ConnectWiFi()
{
  ticker.attach(0.3, tick);
  int count = 0;
  WiFi.mode(WIFI_AP_STA);
  Serial.print("Connecting");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    count++;
    Serial.print(".");
    delay(500);
    if (count >= 20)
    {
      ESP.restart();
    }
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  IP = WiFi.localIP().toString();
  ticker.detach();

}
void HienThiLCD()
{
  /*
    DÒNG 1: Ma: mã the
    Dòng 2: Họ Tên:
    Dòng 3: SDT - RELAY
    Dòng 4: DongDien - CongSuat - Tiền
  */
  str1 = "";
  str2 = "";
  str3 = "";
  str4 = "";


  str1 += "Ma:";
  str1 += String(LastMaThe);


  str2 += "DD:";
  str2 += String(dongdien);
  str2 += String(" A");

  str3 += "P:";
  str3 += String(congsuat);
  str3 += String(" KWh");

  str4 += "Tien:";
  str4 += String(sotien);
  str4 += String(" VND");


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(str1);
  if (TT_RELAY == 0)
  {
    lcd.setCursor(17, 0);
    lcd.print("OFF");
  }
  else if (TT_RELAY == 1)
  {
    lcd.setCursor(17, 0);
    lcd.print("ON");
  }
  lcd.setCursor(0, 1);
  lcd.print(str2);
  lcd.setCursor(0, 2);
  lcd.print(str3);
  lcd.setCursor(0, 3);
  lcd.print(str4);
  yield();
}
void JsonSendWebXoaThe()
{
  // DataWebXoaThe
  //linkXoaThe
  DataWebXoaThe = "";
  HTTPClient http;
  String serverPath = "";
  serverPath += linkXoaThe;
  serverPath += String("?mathe=");
  serverPath += String(MaTheXoa);
  Serial.print("serverPath:");
  Serial.println(serverPath);
  http.begin(serverPath.c_str());
  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
    DataWebXoaThe = String(payload);
  }
  else
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    DataWebXoaThe = "{\"Data\":\"ClearErr\"}";
  }

  http.end();
  yield();
  Serial.println("==================================================================");
}
void JsonSendWebThemSuaXoa()
{
  DataWebThemXoaThe = "";
  DataWebThemXoaThe = "{\"MaThe\":\"" + String(MaThe) + "\"}";
}
void ParseJson1(String Data1)
{
  const size_t capacity1 = JSON_OBJECT_SIZE(4) + 400;
  DynamicJsonDocument JSON1(capacity1);
  DeserializationError error1 = deserializeJson(JSON1, Data1);
  if (error1)
  {
    return;
  }
  else
  {
    Serial.println();
    Serial.println("Data JSON Lưu MYSQL: ");
    serializeJsonPretty(JSON1, Serial);
    Serial.println();
    dongdien1 = "";
    congsuat1 = "";
    sotien1 = "";
    mathe1 = "";
    if (JSON1.containsKey("mathe"))
    {
      String Data_mathe1 = JSON1["mathe"];
      mathe1 = Data_mathe1;
      Serial.print("mathe1:");
      Serial.println(mathe1);
    }

    if (JSON1.containsKey("dongdien"))
    {
      String Data_dongdien1 = JSON1["dongdien"];
      dongdien1 = String(Data_dongdien1);
      Serial.print("dongdien1:");
      Serial.println(dongdien1);
    }

    if (JSON1.containsKey("congsuat"))
    {
      String Data_congsuat1 = JSON1["congsuat"];
      congsuat1 = String(Data_congsuat1);
      Serial.print("congsuat1:");
      Serial.println(congsuat1);
    }

    if (JSON1.containsKey("sotien"))
    {
      String Data_sotien1 = JSON1["sotien"];
      sotien1 = String(Data_sotien1);
      Serial.print("sotien1:");
      Serial.println(sotien1);
    }
    yield();
    JSON1.clear();
  }
}

void JsonSendWebKiemTraTheThemSuaXoa()
{
  //DataWebKiemTraTheThemSuaXoa;
  //linkKiemtraThe

  DataWebKiemTra = "";
  HTTPClient http;
  String serverPath = "";
  serverPath += linkKiemtraThe;
  serverPath += String("?mathe=");
  serverPath += String(MaThe1);
  Serial.print("serverPath:");
  Serial.println(serverPath);
  http.begin(serverPath.c_str());
  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
    DataWebKiemTraTheThemSuaXoa = String(payload);

  }
  else
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    DataWebKiemTraTheThemSuaXoa = "{\"Data\":\"Err\"}";
  }

  http.end();
  yield();
}

void ParseJsonSuaThe(String Data2)
{
  const size_t capacity2 = JSON_OBJECT_SIZE(4) + 400;
  DynamicJsonDocument JSON2(capacity2);
  DeserializationError error2 = deserializeJson(JSON2, Data2);
  if (error2)
  {
    return;
  }
  else
  {
    Serial.println();
    Serial.println("Data JSON Sửa MYSQL: ");
    serializeJsonPretty(JSON2, Serial);
    Serial.println();
    mathesua = "";
    hotensua = "";
    sdtsua = "";
    biensoxesua = "";
    if (JSON2.containsKey("mathe"))
    {
      String Data_mathesua = JSON2["mathe"];
      mathesua = Data_mathesua;
      Serial.print("mathesua:");
      Serial.println(mathesua);
    }

    if (JSON2.containsKey("hoten"))
    {
      String Data_hotensua = JSON2["hoten"];
      hotensua = String(Data_hotensua);
      Serial.print("hotensua:");
      Serial.println(hotensua);
    }

    if (JSON2.containsKey("sdt"))
    {
      String Data_sdtsua = JSON2["sdt"];
      sdtsua = String(Data_sdtsua);
      Serial.print("sdtsua:");
      Serial.println(sdtsua);
    }

    if (JSON2.containsKey("biensoxe"))
    {
      String Data_biensoxe = JSON2["biensoxe"];
      biensoxesua = String(Data_biensoxe);
      Serial.print("biensoxesua:");
      Serial.println(biensoxesua);
    }
    yield();
    JSON2.clear();
  }
}
void JsonSendWebSuaThe()
{
  //DataSuaThe = "";
  //  DataWebSuaThe = "";
  // hotensua = "";
  //sdtsua = "";
  // biensoxesua = "";
  DataWebSuaThe = "";
  HTTPClient http;
  String serverPath = "";
  serverPath += linkSuaThongTin;
  serverPath += String("?mathe=");
  serverPath += String(mathesua);
  serverPath += String("&hoten=");
  serverPath += String(hotensua);
  serverPath += String("&sdt=");
  serverPath += String(sdtsua);
  serverPath += String("&biensoxe=");
  serverPath += String(biensoxesua);
  Serial.print("serverPath:");
  Serial.println(serverPath);
  http.begin(serverPath.c_str());

  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code Sửa thong tin: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
    DataWebSuaThe = String(payload);

  }
  else
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    DataWebSuaThe = "{\"Data\":\"SuaErr\"}";

  }

  http.end();
  yield();
  Serial.println("==================================================================");
}
void  JsonSendWebReset()
{
  //MatheReset = "";
  DataWebReset = "";
  HTTPClient http;
  String serverPath = "";
  serverPath += linkReset;
  serverPath += String("?mathe=");
  serverPath += String(MatheReset);
  Serial.print("serverPath:");
  Serial.println(serverPath);
  http.begin(serverPath.c_str());

  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code Reset: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
    DataWebReset = String(payload);

  }
  else
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    DataWebReset = "{\"Data\":\"RsErr\"}";

  }

  http.end();
  yield();
  Serial.println("==================================================================");
}

void  KiemTraThePhanCung()
{
  //MaThe1 = LastMaThe;
  //linkKiemtraThePhanCung
  HTTPClient http;
  String serverPath = "";
  serverPath += linkKiemtraThePhanCung;
  serverPath += String("?mathe=");
  serverPath += String(MaThe1);
  Serial.print("serverPath:");
  Serial.println(serverPath);
  http.begin(serverPath.c_str());
  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
    ParseJsonPhanCung(String(payload));
  }
  else
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
  yield();
  Serial.println("==================================================================");
}

void ParseJsonPhanCung(String Data3)
{
  const size_t capacity = JSON_OBJECT_SIZE(4) + 400;
  DynamicJsonDocument JSON(capacity);
  DeserializationError error = deserializeJson(JSON, Data3);
  if (error)
  {
    return;
  }
  else
  {
    Serial.println();
    Serial.println("Data JSON Database ESP: ");
    serializeJsonPretty(JSON, Serial);
    Serial.println();
    mathe = "";
    hoten = "";
    sdt = "";
    biensoxe = "";
    dongdien = "";
    congsuat = "";
    sotien = "";
    if (JSON.containsKey("mathe"))
    {
      String Data_mathe = JSON["mathe"];
      mathe = Data_mathe;
      Serial.print("mathe:");
      Serial.println(mathe);
    }
    if (JSON.containsKey("hoten"))
    {
      String Data_hoten = JSON["hoten"];
      hoten = Data_hoten;
      Serial.print("hoten:");
      Serial.println(hoten);
    }

    if (JSON.containsKey("sdt"))
    {
      String Data_sdt = JSON["sdt"];
      sdt = Data_sdt;
      Serial.print("sdt:");
      Serial.println(sdt);
    }

    if (JSON.containsKey("biensoxe"))
    {
      String Data_biensoxe = JSON["biensoxe"];
      biensoxe = Data_biensoxe;
      Serial.print("biensoxe:");
      Serial.println(biensoxe);
    }

    if (JSON.containsKey("dongdien"))
    {
      String Data_dongdien = JSON["dongdien"];
      dongdien = Data_dongdien;
      Serial.print("dongdien:");
      Serial.println(dongdien);
      Irms = dongdien.toFloat();
    }

    if (JSON.containsKey("congsuat"))
    {
      String Data_congsuat = JSON["congsuat"];
      congsuat = Data_congsuat;
      Serial.print("congsuat:");
      Serial.println(congsuat);
      Wh = congsuat.toFloat();
    }

    if (JSON.containsKey("sotien"))
    {
      String Data_sotien = JSON["sotien"];
      sotien = Data_sotien;
      Serial.print("sotien:");
      Serial.println(sotien);
      bill_amount = sotien.toFloat();
    }


    if (JSON.containsKey("DataOK"))
    {
      Serial.println(">>>>>>>>>>>>>>THẺ OKKKKKKKKKKKK");
      StartPhanCung = 1;
      TT_RELAY = 1;
      Relay_ON;
    }


    if (JSON.containsKey("DataErr"))
    {
      Serial.println(">>>>>>>>>>>>>>THẺ LỖI");
      StartPhanCung = 0;
      TT_RELAY = 0;
      Relay_OFF;
    }

    yield();

    JSON.clear();
  }
}
void  LuuThongSoMySQLPhanCung()
{
  //LastMaThe1
  //linkLuuThongTinPhanCung
  HTTPClient http;
  String serverPath = "";
  serverPath += linkLuuThongTinPhanCung;
  serverPath += String("?mathe=");
  serverPath += String(LastMaThe1);
  serverPath += String("&dongdien=");
  serverPath += String(dongdien);
  serverPath += String("&congsuat=");
  serverPath += String(congsuat);
  serverPath += String("&sotien=");
  serverPath += String(sotien);
  Serial.print("serverPath:");
  Serial.println(serverPath);
  http.begin(serverPath.c_str());

  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code Luu thong tin Phần cứng: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);

    if (payload.indexOf("UpdateOK") >= 0)
    {
      Serial.println("UpdateOK");
      StartPhanCung = 0;
      TT_RELAY = 0;
      HienThiLCD();
      Relay_OFF;
      LastMaThe = "null";
      LastMaThe1 = "null";
      MaThe = "null";
    }
    if (payload.indexOf("UpdateErr") >= 0)
    {
      Serial.println("UpdateErr");
    }

  }
  else
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);

  }

  http.end();
  yield();
}
