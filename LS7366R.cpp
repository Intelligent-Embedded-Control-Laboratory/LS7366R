#include "LS7366R.h"

void LS7366R::begin(const unsigned char* _qei_cs, int _num_of_qei, Resolution _resolution)
{
    MDR0_CONF = _resolution;
    num_of_qei = _num_of_qei;
    qei_cs = new unsigned char[_num_of_qei];
    pulse = new long int[_num_of_qei];
    memset(pulse, 0, sizeof(long) * _num_of_qei);
    memcpy(qei_cs, _qei_cs, _num_of_qei);

    for (int i = 0; i < _num_of_qei; i++)
    {
        pinMode(qei_cs[i], OUTPUT);
        digitalWrite(qei_cs[i], HIGH);
    }
    delay(1000);

    // Begin SPI
    SPI.begin();

    // 
    for (int i = 0; i < _num_of_qei; i++)
    {
        init_one_spi_device(qei_cs[i]);
        reset_one_spi_device(qei_cs[i]);
    }
}

void LS7366R::reset_one_spi_device(const unsigned char& qei_cs)
{
    digitalWrite(qei_cs, LOW);
    SPI.transfer(CLR | CNTR);
    digitalWrite(qei_cs, HIGH);
}

void LS7366R::read()
{
    for (int i = 0; i < num_of_qei; i++)
    {
        pulse[i] = read_one_spi_device(qei_cs[i]);
    }
}