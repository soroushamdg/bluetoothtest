#include <Arduino.h>

#include <Time.h>
#include <TimeAlarms.h>

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#include <valuetimelapse.h>
#include <def_bleuuid.h>

#include <BLEbattery.h>
#include <BLEpedometer.h>

#define ONBOARD_LED_PIN 2

TaskHandle_t handle_pedometerTask;

bool deviceConnected = false;
memUint8_t batteryPercentage = 30;
memUint16_t pedometerCounter = 0;

// battery, something counter, on/off led, serial communicate.

class BLECallbacks : public BLEServerCallbacks
{

  void onConnect(BLEServer *server)
  {
    deviceConnected = true;
    Serial.println("Connected device.");
  }

  void onDisconnect(BLEServer *server)
  {
    deviceConnected = false;
    Serial.println("Disonnected device.");
    server->getAdvertising()->start();
  }
};

BLEbatteryController BLEbattery = BLEbatteryController();
BLEpedometerController BLEpedometer = BLEpedometerController();

void refreshBLEvalues()
{
  Serial.println("RUNNING REFRESH.");
  if (!deviceConnected)
    return;

  BLEbattery.refresh();
  BLEpedometer.refresh();
}

void changerandomvalues()
{
  pedometerCounter = (uint16_t)(random(65533));
  batteryPercentage = (uint8_t)(random(100));
}

void setup()
{
  Serial.begin(115250);
  BLEDevice::init("BlueTest");
  pinMode(ONBOARD_LED_PIN, OUTPUT); // Declare the LED as an output

  setTime(0, 0, 0, 0, 0, 0);

  BLEServer *server = BLEDevice::createServer();
  server->setCallbacks(new BLECallbacks());

  // INITIATE SERVERS
  BLEbattery.init(server, &batteryPercentage, false);
  BLEpedometer.init(server, &pedometerCounter, true);

  server->getAdvertising()->addServiceUUID(PHYSICALACTIVITYMONITOR_SERVICE_UUID);
  server->getAdvertising()->start();
  Serial.println("Bluetooth init. Waiting for client...");

  Alarm.timerRepeat(5, refreshBLEvalues);
  Alarm.timerRepeat(3, changerandomvalues);
}

void printDigits(int digits)
{
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
void systemup_time()
{
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println();
}
void loop()
{

  digitalWrite(ONBOARD_LED_PIN, HIGH); // Turn the LED on
  Alarm.delay(500);
  digitalWrite(ONBOARD_LED_PIN, LOW); // Turn the LED on
  Alarm.delay(500);
}
