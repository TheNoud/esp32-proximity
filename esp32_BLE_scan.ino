#include <BLEAdvertisedDevice.h>
#include <BLEDevice.h>
#include <BLEScan.h>

const int PIN0 = 2;
const int PIN1 = 16;
const int PIN2 = 5;
const int PIN3 = 19;
const int PIN4 = 22;
const int CUTOFF0 = -200;
const int CUTOFF1 = -110;
const int CUTOFF2 = -93;
const int CUTOFF3 = -82;
const int CUTOFF4 = -73;

void setup() {
  pinMode(PIN0, OUTPUT);
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, OUTPUT);
  pinMode(PIN3, OUTPUT);
  pinMode(PIN4, OUTPUT);
  BLEDevice::init("");
  //BLEDevice::init("esp32_server");
  

  Serial.begin(115200);

}


// trying something from the BLE_Beacon_Scanner template:
/*
BLEScan *pBLEScan;

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
{
  void onResult(BLEAdvertisedDevice advertisedDevice)
    {
      if (advertisedDevice.haveName())
      {
        Serial.print("Device name: ");
        Serial.println(advertisedDevice.getName().c_str());
        Serial.println("");
        if (advertisedDevice.getName()=="esp32_server")
          {
            Serial.print("You're the man now dog");
          }
      }
    }
};
*/

void loop() {
  BLEScan *scan = BLEDevice::getScan();
  scan->setActiveScan(true);
  BLEScanResults results = scan->start(1);

// trying something from the BLE_Beacon_Scanner template:
//  BLEDevice::init("");
//  pBLEScan = BLEDevice::getScan(); //create new scan
//  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
//  scan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());

  
  int startPin0 = CUTOFF0;
  int best1 = CUTOFF1;
  int best2 = CUTOFF2;
  int best3 = CUTOFF3;
  int best4 = CUTOFF4;
  for (int i = 0; i < results.getCount(); i++) {
    BLEAdvertisedDevice device = results.getDevice(i);
//    Serial.println(results);
    int rssi = device.getRSSI();
//    Serial.println(rssi);
/*    
    if (rssi > best1) {
      best1 = rssi;
    }
    if (rssi > best2) {
      best2 = rssi;
    }
    if (rssi > best3) {
      best3 = rssi;
    }
*/



  if (device.haveName())
      {
        Serial.print("Device name: ");
        Serial.println(device.getName().c_str());
        Serial.println("");
        if (device.getName()=="esp32_server")
          {
            // Serial.print("You're the REAL man now dog");
            startPin0 = rssi;
            Serial.print("StartPin0");
            
             if (rssi > best1) {
                best1 = rssi;
                Serial.print("Pin1");
              }
              if (rssi > best2) {
                best2 = rssi;
                Serial.print("Pin2");
              }
              if (rssi > best3) {
                best3 = rssi;
                Serial.print("Pin3");
              }
              if (rssi > best4) {
                best4 = rssi;
                Serial.print("Pin4");
              }
            
          }
      }


  }
  digitalWrite(PIN0, startPin0 > CUTOFF0 ? HIGH : LOW);
  digitalWrite(PIN1, best1 > CUTOFF1 ? HIGH : LOW);
  digitalWrite(PIN2, best2 > CUTOFF2 ? HIGH : LOW);  
  digitalWrite(PIN3, best3 > CUTOFF3 ? HIGH : LOW); 
  digitalWrite(PIN4, best4 > CUTOFF4 ? HIGH : LOW);

}


/* THIS WORKS

void loop() {
  BLEScan *scan = BLEDevice::getScan();
  scan->setActiveScan(true);
  BLEScanResults results = scan->start(1);

// trying something from the BLE_Beacon_Scanner template:
//  BLEDevice::init("");
//  pBLEScan = BLEDevice::getScan(); //create new scan
//  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  scan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());

  
  
  int best1 = CUTOFF1;
  int best2 = CUTOFF2;
  int best3 = CUTOFF3;
  for (int i = 0; i < results.getCount(); i++) {
    BLEAdvertisedDevice device = results.getDevice(i);
//    Serial.println(results);
    int rssi = device.getRSSI();
//    Serial.println(rssi);
    if (rssi > best1) {
      best1 = rssi;
    }
    if (rssi > best2) {
      best2 = rssi;
    }
    if (rssi > best3) {
      best3 = rssi;
    }
  }
  digitalWrite(PIN1, best1 > CUTOFF1 ? HIGH : LOW);
  digitalWrite(PIN2, best2 > CUTOFF2 ? HIGH : LOW);  
  digitalWrite(PIN3, best3 > CUTOFF3 ? HIGH : LOW); 

}
*/
