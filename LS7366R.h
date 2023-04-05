/**
 * @file LS7366R.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-02-07
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include <Arduino.h>
#include <SPI.h>

class LS7366R /* 2022-07-30 */
{
public:
    void begin(const unsigned char* _qei_cs, int _num_of_qei);
    void read();
    const long* get_pulse() { return pulse; }

    void reset_one_spi_device(const unsigned char& qei_cs);
protected:
    void init_one_spi_device(unsigned char& qei_cs)
    {
        digitalWrite(qei_cs, LOW);
        SPI.transfer(WR | MDR0);
        SPI.transfer(MDR0_CONF);
        digitalWrite(qei_cs, HIGH);


        digitalWrite(qei_cs, LOW);
        SPI.transfer(WR | MDR1);
        SPI.transfer(MDR1_CONF);
        digitalWrite(qei_cs, HIGH);
    }
    const long& read_one_spi_device(unsigned char& qei_cs)
    {
        digitalWrite(qei_cs, LOW);
        SPI.transfer(LOAD | OTR);
        digitalWrite(qei_cs, HIGH);

        digitalWrite(qei_cs, LOW);
        SPI.transfer(RD | OTR);
        count = SPI.transfer(0x00);
        count <<= 8;
        count |= SPI.transfer(0x00);
        count <<= 8;
        count |= SPI.transfer(0x00);
        count <<= 8;
        count |= SPI.transfer(0x00);
        digitalWrite(qei_cs, HIGH);

        return count;
    }
    unsigned char* qei_cs;
    long* pulse;
    int num_of_qei;
    long count;

    /* Register Map */
    const uint8_t MDR0_CONF = B00000011;
    const uint8_t MDR1_CONF = B00000000;
    const uint8_t CLR = B00000000;
    const uint8_t RD = B01000000;
    const uint8_t WR = B10000000;
    const uint8_t LOAD = B11000000;
    const uint8_t MDR0 = B00001000;
    const uint8_t MDR1 = B00010000;
    const uint8_t DTR = B00011000;
    const uint8_t CNTR = B00100000;
    const uint8_t OTR = B00101000;
    const uint8_t STR = B00110000;
};
