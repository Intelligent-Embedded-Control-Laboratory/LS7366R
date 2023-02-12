#include "LS7366R.h"

void LS7366R::begin(unsigned char _qei_cs)
{
    qei_cs = _qei_cs;

    pinMode(qei_cs, OUTPUT);
    SPI.begin();

    delay(100);

    digitalWrite(qei_cs, LOW);
    SPI.transfer(WR | MDR0);
    SPI.transfer(MDR0_CONF);
    digitalWrite(qei_cs, HIGH);

    delay(100);

    digitalWrite(qei_cs, LOW);
    SPI.transfer(WR | MDR1);
    SPI.transfer(MDR1_CONF);
    digitalWrite(qei_cs, HIGH);

    delay(100);
    
    reset();
}

void LS7366R::reset()
{
    digitalWrite(qei_cs, LOW);
    SPI.transfer(CLR | CNTR);
    digitalWrite(qei_cs, HIGH);
}

long LS7366R::read()
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
    pulse = count;

    return pulse;
}