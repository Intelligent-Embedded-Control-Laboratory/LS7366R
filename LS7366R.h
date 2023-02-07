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
    void begin(unsigned char _qei_cs);
    void reset();
    long read();
    
protected:
    unsigned char qei_cs;
    long count;
    long pulse;

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
