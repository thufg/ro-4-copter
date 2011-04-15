/*
Timer0 software based servo control
Frank Zhao 20110412

Copyright (c) 2005-2006 David A. Mellis

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General
Public License along with this library; if not, write to the
Free Software Foundation, Inc., 59 Temple Place, Suite 330,
Boston, MA  02111-1307  USA

This is designed specifically to work with the Arduino and for Ro4Copter
The millis() function of Arduino depends on timer0 to run with a clock divider of 64
I wanted to use timer0 because timer1 and timer2 are occupied for controlling ESCs
The original AeroQuad used timer3 and beyond to control additional servos for things such as cameras
These timers that are not timer0 ran on a clock divider larger than 64 (slower timer, less resolution)
This made implementing additional servos almost impossible on AVRs with only timer0 timer1 and timer2
I did not want to change the divider of timer0 just in case if any application required the resolution
So I wrote this code, which basically uses interrupt service routines instead of dedicated compare match PWM pins
Doing it this way allows timer0 to run at the same speed, the servos will have more resolution, and can be connected
to any pin on the AVR instead of the ones designated for timer0's PWM output

The Arduino core must be modified such that the timer0 overflow interrupt ISR vector calls the onOverflow event
I have done this by modifying "wiring.c" and "wiring.h" to include a "attachTimer0OverflowEvent" function
The onCompareMatch event is called by the COMPA interrupt vector ISR in the sketch

Using AnalogWrite on the pin for OC0A will cause this to fail as it will write to OCR0A and cause incorrect timing for the servo

Setting the ticks is done in raw timer tick values, not angles, with 16 MHz divided by 64, one tick of timer0 is 4 microseconds
*/

#include <avr/io.h>

#include "SoftServo.h"

typedef struct
{
	uint8_t* portPtr; // pointer to IO port
	uint8_t pinNum; // pin number in IO port
	uint16_t ticks; // read by interrupt routine
	uint16_t ticksStored; // write to this from main thread
} SoftServo_t;

#define SERVO_TIMER_DIVIDER 64

#define SERVO_COUNT 8
SoftServo_t servoList[SERVO_COUNT]; // list of servos
uint8_t servoCurIdx = 0; // the current channel
uint8_t nextServoFlag = 0; // indicates to the overflow event to start the next channel
uint16_t curTicksPassed = 0; // this counts the time for the current channel
uint16_t totalTicksPassed = 0; // this counts the total period for all channels

// this event must be called in the overflow ISR
inline void SoftServo_onOverflow()
{
	totalTicksPassed += 256;
	curTicksPassed += (256 - OCR0A);
	if (nextServoFlag)
	{
		if (servoCurIdx < SERVO_COUNT - 1) // if not almost end of list
		{
			servoCurIdx++;
		}
		else if (totalTicksPassed >= (F_CPU / (SERVO_TIMER_DIVIDER * 75))) // about 15 ms
		{
			totalTicksPassed = 0;
			servoCurIdx = 0;
		}
		else // end of list but total period insufficient, do not start new channel
		{
			return;
		}
		
		curTicksPassed = 0;
		
		SoftServo_t* theServo = &servoList[servoCurIdx];
		
		// start the pulse if channel exists and is enabled
		if (theServo->portPtr != 0 && theServo->ticks)
			*(theServo->portPtr) |= _BV(theServo->pinNum);
		
		theServo->ticks = theServo->ticksStored;
		
		OCR0A = theServo->ticks & 0xFF;
		
		nextServoFlag = 0;
	}
}

// this event must be called in the compare match A ISR
inline void SoftServo_onCompareMatch()
{
	if (nextServoFlag == 0)
	{
		SoftServo_t* theServo = &servoList[servoCurIdx];
		
		curTicksPassed += OCR0A;
		
		// if pulse has been long enough
		if (curTicksPassed >= theServo->ticks)
		{
			// end the pulse if channel exists
			if (theServo->portPtr != 0)
				*(theServo->portPtr) &= ~_BV(theServo->pinNum);
				
			nextServoFlag = 1;
		}
	}
}

void SoftServo_detachAll()
{
	servoCurIdx = 0;
	nextServoFlag = 0;
	curTicksPassed = 0;
	totalTicksPassed = 0;

	int i;
	for (i = 0; i < SERVO_COUNT; i++)
	{
		SoftServo_detach(i);
	}
}

void SoftServo_attach(uint8_t channel, volatile uint8_t * portPtr, volatile uint8_t * ddrPtr, uint8_t pinNum)
{
	SoftServo_t* theServo = &servoList[channel];
	theServo->ticksStored = (F_CPU / ((SERVO_TIMER_DIVIDER * 20000) / 3)); // 1500 us
	theServo->ticks = theServo->ticksStored;
	theServo->portPtr = portPtr;
	theServo->pinNum = pinNum;
	
	*portPtr &= ~_BV(pinNum);
	*ddrPtr |= _BV(pinNum);
}

void SoftServo_detach(uint8_t channel)
{
	SoftServo_t* theServo = &servoList[channel];
	theServo->portPtr = 0;
	theServo->pinNum = 0;
	theServo->ticks = 0;
	theServo->ticksStored = 0;
}

inline void SoftServo_set(uint8_t channel, uint16_t ticks)
{
	servoList[channel].ticksStored = ticks;
}

inline void SoftServo_engageInterrupts()
{
	TIMSK0 |= _BV(TOIE0) | _BV(OCIE0A);
}

inline void SoftServo_startTimer()
{
	TCCR0B = _BV(CS00) | _BV(CS01);
}