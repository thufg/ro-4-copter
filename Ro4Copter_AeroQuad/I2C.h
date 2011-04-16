/*
  AeroQuad v2.4 - April 2011
  www.AeroQuad.com
  Copyright (c) 2011 Ted Carancho.  All rights reserved.
  An Open Source Arduino based multicopter.
 
  This program is free software: you can redistribute it and/or modify 
  it under the terms of the GNU General Public License as published by 
  the Free Software Foundation, either version 3 of the License, or 
  (at your option) any later version. 

  This program is distributed in the hope that it will be useful, 
  but WITHOUT ANY WARRANTY; without even the implied warranty of 
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
  GNU General Public License for more details. 

  You should have received a copy of the GNU General Public License 
  along with this program. If not, see <http://www.gnu.org/licenses/>. 
*/

/*
Edited for Ro4Copter by frank26080115 on 20100416
*/

#ifdef Ro4Copter

#ifdef __cplusplus
extern "C"{
#endif
// this is placed in the core specially for Ro4Copter
#include "TwiRaw.h"
#ifdef __cplusplus
}
#endif

// speed boost over Wire library with no penalty, works great as long as we are using master mode only

void sendByteI2C(int deviceAddress, byte dataValue) {
  twi_writeTo(deviceAddress, &dataValue, 1, 1);
}

byte readByteI2C(int deviceAddress) {
  byte readResult;
  twi_readFrom(deviceAddress, &readResult, 1);
  return readResult;
}

int readWordI2C(int deviceAddress) {
  byte readResult[2];
  twi_readFrom(deviceAddress, readResult, 1);
  return (((int)readResult[1]) << 8) | (int)readResult[0];
}

int readWordWaitI2C(int deviceAddress) {
  byte readResult[2];
  twi_readFrom(deviceAddress, readResult, 1);
  return (((int)readResult[1]) << 8) | (int)readResult[0];
}

int readReverseWordI2C(int deviceAddress) {
  byte readResult[2];
  twi_readFrom(deviceAddress, readResult, 1);
  return (((int)readResult[0]) << 8) | (int)readResult[1];
}

byte readWhoI2C(int deviceAddress) {
  byte readResult;

  sendByteI2C(deviceAddress, 0);

  delay(100);
  twi_readFrom(deviceAddress, &readResult, 1);
  return readResult;
}

void updateRegisterI2C(int deviceAddress, byte dataAddress, byte dataValue) {
  byte arr[2] = {dataAddress, dataValue};
  twi_writeTo(deviceAddress, arr, 2, 1);
}

#else // old version retained since only the Ro4Copter core contains TwiRaw.h

// I2C functions

void sendByteI2C(int deviceAddress, byte dataValue) {
  Wire.beginTransmission(deviceAddress);
  Wire.send(dataValue);
  Wire.endTransmission();
}

byte readByteI2C(int deviceAddress) {
    Wire.requestFrom(deviceAddress, 1);
    return Wire.receive();
}

/*
comment from frank26080115 - calling "receive" like that is bad practice
see http://en.wikipedia.org/wiki/Sequence_point
also note that binary OR is not the same as boolean/logical OR
*/
int readWordI2C(int deviceAddress) {
  Wire.requestFrom(deviceAddress, 2);
  return (Wire.receive() << 8) | Wire.receive();
}

/*
comment from frank26080115 - I'm not sure why this is here
if you are performing a request, then you are being master
which means the data is guaranteed to be available immediantly after "requestFrom"
there's never going to be a need to check "available"
*/
int readWordWaitI2C(int deviceAddress) {
  unsigned char msb, lsb;
  Wire.requestFrom(deviceAddress, 2); // request two bytes
  while(!Wire.available()); // wait until data available
  msb = Wire.receive();
  while(!Wire.available()); // wait until data available
  lsb = Wire.receive();
  return (((int)msb<<8) | ((int)lsb));
}

int readReverseWordI2C(int deviceAddress) {
  byte lowerByte;
  Wire.requestFrom(deviceAddress, 2);
  lowerByte = Wire.receive();
  return (Wire.receive() << 8) | lowerByte;
}

/*
comment from frank26080115 - 100ms delay??
*/
byte readWhoI2C(int deviceAddress) {
  // read the ID of the I2C device
  Wire.beginTransmission(deviceAddress);
  Wire.send(0x00);
  Wire.endTransmission();
  delay(100);
  Wire.requestFrom(deviceAddress, 1);
  return Wire.receive();
}

void updateRegisterI2C(int deviceAddress, byte dataAddress, byte dataValue) {
  Wire.beginTransmission(deviceAddress);
  Wire.send(dataAddress);
  Wire.send(dataValue);
  Wire.endTransmission();
}  

#endif


