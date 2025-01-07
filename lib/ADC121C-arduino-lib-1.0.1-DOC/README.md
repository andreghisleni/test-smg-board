# ADC121CXXX
Arduino library for ADC121CXXX, I2C 12-Bit Resolution ADC with Alert Function

For technical informations, please refer to this [datasheet.](https://www.ti.com/lit/ds/symlink/adc121c021.pdf?ts=1639027374303&ref_url=https%253A%252F%252Fwww.google.com.sg%252F)

## Supported Devices
- ADC121C021
- ADC121C021Q
- *ADC121C027*

## How To Use The Library
Include the library, then simply create an object like this:
```C
#include <ADC121C.h>
ADC121C adc(*i2c device address*);
```

Then, in the setup function of Arduino:
```C
void setup(){
  adc.begin();
  ...
```

To use this library with other I2C ports, you can simply create a TwoWire object then parse it into the 'begin' function:
```C
// ESP32
#define I2C_SDA 33
#define I2C_SCL 32

TwoWire esp = TwoWire(0);
ADC121C adc(*i2c device address*);

void setup(){
  esp.begin(I2C_SDA, I2C_SCL, 1000000);
  adc.begin(&esp);
}
```

# Methods
```C
void begin(TwoWire &wirePort = Wire);
```
Initiate the ADC121C library

Can be configured to use other I2C ports from a 'TwoWire' object. For default I2C port, just leave the parameter blank.

```C
unsigned int readConversion();
unsigned int readConversion(bool &boo);
```
Read the ADC conversion value from the device. Return as decimal within the resolution of 12-bit (0 to 4095).

This method also can be overloaded with a variable to check if alert condition has occured or not too.

```C
unsigned int getLowLimit();
```
Get low limit value.<br>
Default value: 0000h (0)

```C
void setLowLimit(uint16_t val);
```
Set low limit value.<br>
**^Shouldn't exceed 4095, otherwise will be set back to 4095.**

```C
unsigned int getHighLimit();
```
Get high limit value.<br>
Default value: 0FFFh (4095)

```C
void setHighLimit(uint16_t val);
```
Set high limit value.<br>
**^Shouldn't exceed 4095, otherwise will be set back to 4095.**

```C
unsigned int getAlertHyst();
```
Get alert hysteresis value.

```C
void setAlertHyst(uint16_t val);
```
Set alert hysteresis value.<br>
**^Shouldn't exceed 4095, otherwise will be set back to 4095.**

```C
unsigned int getLowConv();
```
Get the lowest conversion result when in automatic conversion mode.<br>
Default value: 0FFFh (0)

**^The value is not updated in the normal conversion mode.**

```C
void setLowConv(uint16_t val);
```
Set the lowest conversion result.<br>
**^Shouldn't exceed 4095, otherwise will be set back to 4095.**

```C
unsigned int getHighConv();
```
Get the highest conversion result when in automatic conversion mode.<br>
Default value: 0000h (0)

**^The value is not updated in the normal conversion mode.**

```C
void setHighConv(uint16_t val);
```
Set the highest conversion result.<br>
**^Shouldn't exceed 4095, otherwise will be set back to 4095.**

```C
uint8_t getAlertStatus();
```
Get the alert status register value.<br>

```C
void setAlertStatus(uint8_t val);
```
Configure the alert status register.


**Alert Status Table:**<br>
|Value|Over Range Alert|Under Range Alert|
|----|----------------|-----------------|
|0x00| false | false |
|0x01| false | true |
|0x02| true | false |
|0x03| true | true |

****^Beyond than 0x03, this function won't do anything to the alert status register.****

```C
void setPolarity(bool val);
```
Configure the polarity output of ALERT pin.

|Value|Description|
|-----|----------------------------------|
|logic 0|Sets the ALERT pin to ACTIVE LOW|
|logic 1|Sets the ALERT pin to ACTIVE HIGH|

**^This bit doens't apply to ADC121C027, and is "don't care" for it.**

```C
void setAlertPinEnable(bool val)
```
Enable or disable the ALERT pin.

|Value|Description|
|-----|----------------------------------|
|logic 0|Disable the ALERT pin|
|logic 1|Enable the ALERT pin|

**^This bit doens't apply to ADC121C027, and is "don't care" for it.**

```C
void setAlertFlagEnable(bool val);
```
Enable or disable the ALERT flag in conversion result.

|Value|Description|
|-----|----------------------------------|
|logic 0|Disable alert status bit in conversion result|
|logic 1|Enable alert status bit in conversion result|

```C
void setAlertHold(bool val);;
```
Enable or disable the ALERT hold logic in alert status register.

|Value|Description|
|-----|----------------------------------|
|logic 0|Alert will self-clear when measured value is more than hysteresis|
|logic 1|Alert will not self-clear unless a one is written to the alert status register, either high or low|

```C
void setCycleTime(uint8_t val);
```
Configure automatic conversion mode.

|Cycle Time|Conversion Interval|Typical conversion frequency (ksps)|
|----------|-------------------|------------------------|
|0x00|Automatic Mode Disable| 0 |
|0x01|Tconvert x 32 | 27 |
|0x02|Tconvert x 64 | 13.5 |
|0x03|Tconvert x 128 | 6.7 |
|0x04|Tconvert x 256 | 3.4 |
|0x05|Tconvert x 512 | 1.7 |
|0x06|Tconvert x 1024 | 0.9 |
|0x07|Tconvert x 2048 | 0.6 |

```C
int8_t checkConfig(uint8_t op);
```
Check a configure.

|'op'|Features|
|----------|-------------------|
|0x00|Polarity|
|0x01|'Invalid' (return as -1)|
|0x02|Alert Pin Enable|
|0x03|Alert Flag Enable|
|0x04|Alert Hold|
|0x05|Cycle Time|

**^Beyond than 0x05 will return as -1**


