#ifndef SoftServo_h
#define SoftServo_h

#ifdef __cplusplus 
extern "C"{
#endif

#include <inttypes.h>

void SoftServo_onOverflow();

void SoftServo_onCompareMatch();

void SoftServo_detachAll();

void SoftServo_attach(uint8_t channel, volatile uint8_t * portPtr, volatile uint8_t * ddrPtr, uint8_t pinNum);

void SoftServo_detach(uint8_t channel);

void SoftServo_set(uint8_t channel, uint16_t ticks);

void SoftServo_engageInterrupts();

void SoftServo_startTimer();

#ifdef __cplusplus
}
#endif

#endif