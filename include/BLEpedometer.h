class BLEpedometerController
{
private:
    bool _notify = false;
    uint16_t _value = 0;

public:
    memUint16_t *value;
    // BLE PEDOMETER CHARACTERISTIC
    BLECharacteristic BLEpedometerCharacteristic = BLECharacteristic(STEPCOUNTER_CAR_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);

    void init(BLEServer *server, memUint16_t *_value, bool notify = false)
    {
        try
        {
            // pedometer server
            // 1. CREATE SERVICE
            BLEService *BLEpedometerService = server->createService(PHYSICALACTIVITYMONITOR_SERVICE_UUID);
            // 2. CREATE CHARACTERISTIC
            BLEpedometerService->addCharacteristic(&BLEpedometerCharacteristic);

            if (notify)
            {
                BLEpedometerCharacteristic.addDescriptor(new BLE2902());
                _notify = true;
            }

            value = _value;

            BLEpedometerService->start();
            this->sendValue();
        }
        catch (const std::exception &e)
        {
            Serial.println(e.what());
        }
    }

    bool didValueChange()
    {
        return (value->current() != value->old());
    }

    void sendValue()
    {
        _value = value->current();

        Serial.print("REAL PEDO VALUE -> ");
        Serial.println(_value, HEX);

        swap(_value);

        BLEpedometerCharacteristic.setValue(_value);
        BLEpedometerCharacteristic.notify();
    }

    void refresh()
    {
        if (didValueChange())
            this->sendValue();
        return;
    }
};
