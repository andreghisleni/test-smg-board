/* 
   ADC121CXXX - Arduino library for ADC121CXXX, I2C 12-Bit Resolution ADC with Alert Function
   By: Chawin 'FaultyTwo' Treesugol <https://github.com/FaultyTwo/ADC121C-arduino-lib>
*/

#ifndef ADC121C_ft
#define ADC121C_ft

#include "Arduino.h"
#include "Wire.h"

/// @brief A ADC121CXXX class
class ADC121C{
  public:
    /// @brief Specify a ADC121XXX device
    /// @param adr The address of a ADC121XXX device
    ADC121C(uint8_t adr);
    /// @brief Initial a ADC121XXX device
    /// @param wire A TwoWire object, leave blank for default
    void begin(TwoWire &wire = Wire);
    /// @brief Read the ADC conversion value from the device, with alert condition overloading return
    /// @param boo A boolean variable to receive alert condition
    /// @return The reading result
    unsigned int readConversion(bool &boo);
    /// @brief Read the ADC conversion value from the device
    /// @return The reading result
    unsigned int readConversion(); //overloaded

    // setting stuffs
    // 2 bytes config

    /// @brief Get low limit value
    /// @return The low limit value
    unsigned int getLowLimit();
    /// @brief Set the low limit value
    /// @param val The low limit value
    void setLowLimit(uint16_t val);
    /// @brief Get high limit value
    /// @return The high limit value
    unsigned int getHighLimit();
    /// @brief Set high limit value
    /// @param val The high limit value
    void setHighLimit(uint16_t val);
    /// @brief Get alert hysteresis value
    /// @return The alert hysteresis value
    unsigned int getAlertHyst();
    /// @brief Set alert hysteresus value
    /// @param val The alert hysteresus value
    void setAlertHyst(uint16_t val);
    /// @brief Get the lowest conversion result when in automatic conversion mode
    /// @return The lowest conversion value
    unsigned int getLowConv();
    /// @brief Set the lowest conversion result
    /// @param val The lowest conversion value
    void setLowConv(uint16_t val);
    /// @brief Get the highest conversion result when in automatic conversion mode
    /// @return The highest conversion value
    unsigned int getHighConv();
    /// @brief Set the highest conversion result
    /// @param val The highest conversion value
    void setHighConv(uint16_t val);
    
    // alert status config

    /// @brief Get the alert status register value
    /// @return The alert status value
    uint8_t getAlertStatus();

    /// @brief Configure the alert status register
    /// @param val The register value
    void setAlertStatus(uint8_t val);

    // .. configuration register

    /// @brief Configure the polarity output of ALERT pin
    /// @param val The boolean value (logic 0 = ACTIVE LOW, logic 1 = ACTIVE HIGH)
    void setPolarity(bool val);
    /// @brief Enable or disable the alert pin
    /// @param val The boolean value (logic 0 = DISABLE, logic 1 = ENABLE)
    void setAlertPinEnable(bool val);
    // Enable or disable the ALERT flag in conversion result
    /// @brief Enable or disable the ALERT flag in conversion result
    /// @param val The boolean value (logic 0 = DISABLE, logic 1 = ENABLE)
    void setAlertFlagEnable(bool val);
    /// @brief Enable or disable the ALERT hold logic in alert status register
    /// @param val The boolean value (logic 0 = SELF-CLEAR, logic 1 = NO SELF-CLEAR)
    void setAlertHold(bool val);
    /// @brief Configure automatic conversion mode
    /// @param val Conversion time
    /// @note https://github.com/FaultyTwo/ADC121C-arduino-lib
    void setCycleTime(uint8_t val);
    /// @brief Check a configure
    /// @param op Operation code
    /// @return The value of a config
    /// @note https://github.com/FaultyTwo/ADC121C-arduino-lib
    int8_t checkConfig(uint8_t op);
    
  private:
    TwoWire *_wire;
    uint8_t _adr;
    uint16_t readRegister(uint8_t reg); //some register returns two bytes
    void writeRegister(uint8_t reg, uint16_t val); //some register needs only one byte
};

// I'm debating whether to include ailas too since it's insignificant

#endif
