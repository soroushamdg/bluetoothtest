
class BLEledController
{
private:
    bool _notify = false;
    uint8_t _value = 0;

public:
    String *value;
    // BLE BATTERY CHARACTERISTIC
    BLECharacteristic BLEledCharacteristic = BLECharacteristic(LEDCONTROLLER_CAR_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);

    void init(BLEServer *server, String *_value, BLECharacteristicCallbacks *pCallbacks, bool notify = false)
    {
        try
        {
            // battery server
            // 1. CREATE SERVICE
            BLEService *BLEledService = server->createService(LEDCONTROLLER_SERVICE_UUID);
            // 2. CREATE CHARACTERISTIC
            BLEledCharacteristic.setCallbacks(pCallbacks);
            BLEledService->addCharacteristic(&BLEledCharacteristic);

            if (notify)
                BLEledCharacteristic.addDescriptor(new BLE2902());
            _notify = true;

            value = _value;

            BLEledService->start();

        }
        catch (const std::exception &e)
        {
            Serial.println(e.what());
        }
    }

    void refresh()
    {
       
    }

    String fetch()
    {
        String led_read;
        std::string val = BLEledCharacteristic.getValue();
        led_read.clear();
        for (int i = 0; i < val.length(); i++)
        {
            led_read += value[i];
        }
        return led_read;
    }
};
