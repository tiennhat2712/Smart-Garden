/*

The MIT License (MIT)

Copyright (c) 2018 Juan Carlos Galvez

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include <Arduino.h>
#include <SoftwareUART.h>

SoftwareUART::SoftwareUART(int receivePin, int transmitPin, bool inverse_logic, unsigned int buffSize) {
  Softuart_SetPinRx(&_softuart, receivePin);
  Softuart_SetPinTx(&_softuart, transmitPin);
  //Softuart_Init(&_softuart, 9600);
}

SoftwareUART::~SoftwareUART() {
}

void SoftwareUART::begin(long speed) {
  Softuart_Init(&_softuart, speed);
  _speed = speed;
}

long SoftwareUART::baudRate() {
  return _speed;
}

int SoftwareUART::read() {
  delay(0);
  return Softuart_Read(&_softuart);
}

int SoftwareUART::available() {
  delay(0);
  return Softuart_Available(&_softuart);
}

size_t SoftwareUART::write(uint8_t b) {
  Softuart_Putchar(&_softuart, b);
  return 1;
}

void SoftwareUART::flush() {
  delay(0);
  _softuart.buffer.receive_buffer_tail = _softuart.buffer.receive_buffer_head = 0;
}

bool SoftwareUART::overflow() {
  delay(0);
  return _softuart.buffer.buffer_overflow;
}

int SoftwareUART::peek() {
  delay(0);
  return _softuart.buffer.receive_buffer[_softuart.buffer.receive_buffer_head];
}

void SoftwareUART::enableRs485(uint8_t gpio_id)
{
  Softuart_EnableRs485(&_softuart, gpio_id);
}