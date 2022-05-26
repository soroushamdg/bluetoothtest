
class BLEbatteryController
{
private:
    bool _notify = false;
    uint8_t _value = 0;

public:
    memUint8_t *value;
    // BLE BATTERY CHARACTERISTIC
    BLECharacteristic BLEbatteryCharacteristic = BLECharacteristic(BATTERYLEVEL_CAR_UUID, BLECharacteristic::PROPERTY_READ);

    void init(BLEServer *server, memUint8_t *_value, bool notify = false)
    {
        try
        {
            // battery server
            // 1. CREATE SERVICE
            BLEService *BLEbatteryService = server->createService(BATTERYLEVEL_SERVICE_UUID);
            // 2. CREATE CHARACTERISTIC
            BLEbatteryService->addCharacteristic(&BLEbatteryCharacteristic);
            // 3. ADD DESCRIPTOR
            BLEDescriptor BLEbatteryDescriptor(BLEUUID((uint16_t)0x2906));
            BLEbatteryDescriptor.setValue("Battery percentage");
            BLEbatteryCharacteristic.addDescriptor(&BLEbatteryDescriptor);

            if (notify)
                BLEbatteryCharacteristic.addDescriptor(new BLE2902());
            _notify = true;

            value = _value;

            BLEbatteryService->start();

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

        Serial.print("SENDING BATTERY VALUE -> ");
        Serial.println(_value);

        BLEbatteryCharacteristic.setValue((uint8_t *)&_value, 1);
    }

    void refresh()
    {
        if (didValueChange())
            this->sendValue();
        return;
    }
};