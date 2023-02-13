# LS7366R QEI Pulse Decoder

Feb 07, 2023

## How to use

```cpp
#include <Arduino.h>
#include <LS7366R.h>

const uint8_t PIN_QEI[4] = { 32, 33, 30, 31 };

LS7366R encoder;

void setup()
{
    Serial.begin(115200);

    encoder.begin(PIN_QEI, 4);
}

void loop()
{
    encoder.read();

    for (int i = 0; i < 4; i++)
    {
        Serial.printf("%d ", encoder.get_pulse()[i]);
    }
    Serial.println();
    Serial.flush();

    delay(1);
}
```
