#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>

#include "config.h"
#include "pindef.h"
#include "macros.h"

#include "ser.h"

void ser_buff_init(ser_buff_s *, uint8_t);

static volatile ser_buff_s ser_tx_buff_0;
static volatile ser_buff_s ser_tx_buff_1;
static volatile ser_buff_s ser_rx_buff_0;
static volatile ser_buff_s ser_rx_buff_1;

void ser0_init(uint16_t ubrr, uint8_t rxs, uint8_t txs)
{
	UBRR0 = ubrr; // set baud

	// initialize circular buffer
	ser_buff_init(&ser_tx_buff_0, txs);
	ser_buff_init(&ser_rx_buff_0, rxs);

	// initialize port and associated interrupts
	UCSR0B = _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0) | _BV(TXCIE0);
}

#ifdef __AVR_ATmega644P__
void ser1_init(uint16_t ubrr, uint8_t rxs, uint8_t txs)
{
	UBRR1 = ubrr;

	ser_buff_init(&ser_tx_buff_1, txs);
	ser_buff_init(&ser_rx_buff_1, rxs);

	UCSR1B = _BV(RXEN1) | _BV(TXEN1) | _BV(RXCIE1) | _BV(TXCIE1);
}
#endif

void ser_buff_init(ser_buff_s * b, uint8_t s)
{
	// reset head and tail, flag
	b->h = 0;
	b->t = 0;
	b->f = 0;
	
	// set size and allocate memory
	b->s = s;
	free(b->d);
	b->d = calloc(sizeof(uint8_t), s);
}

void ser_tx(uint8_t p, uint8_t c)
{
	// select buffer based on port
	volatile ser_buff_s * ser_tx_buff = &ser_tx_buff_0;
	if (p == 1)
	{
		ser_tx_buff = &ser_tx_buff_1;
	}
	
	volatile uint8_t b;
	do // wait for space
	{
		b = (ser_tx_buff->s + ser_tx_buff->t - ser_tx_buff->h) % ser_tx_buff->s;
		LED1_tog();
	}
	while (b > ser_tx_buff->s - 3);
	
	// set character and then expand buffer
	ser_tx_buff->d[ser_tx_buff->t] = c;
	ser_tx_buff->t = (ser_tx_buff->t + 1) % ser_tx_buff->s;

	if(ser_tx_buff->f == 0)
	{
		// if first character then start the transmission
		
		#ifdef __AVR_ATmega644P__
		if (p == 1)
		{
			UDR1 = c;
		}
		else
		#endif
		{
			UDR0 = c;
		}
		
		// move the pointer and indicate busy
		ser_tx_buff->h = (ser_tx_buff->h + 1) % ser_tx_buff->s;
		ser_tx_buff->f = 1;
	}
}

void ser_tx_0(char c, FILE * stream)
{
	ser_tx(0, c);
}

void ser_tx_1(char c, FILE * stream)
{
	ser_tx(1, c);
}

uint8_t ser_rx(uint8_t p, uint8_t * r)
{
	ser_buff_s * ser_rx_buff = &ser_rx_buff_0;
	
	if (p == 1)
	{
		ser_rx_buff = &ser_rx_buff_1;
	}
	
	if(ser_rx_buff->h == ser_rx_buff->t) // if buffer empty, return error
	{
		*r = 0;
		return 0;
	}
	else
	{
		*r = (ser_rx_buff->s + ser_rx_buff->h - ser_rx_buff->t) % ser_rx_buff->s;
		uint8_t data = ser_rx_buff->d[ser_rx_buff->t]; // read from buffer
		ser_rx_buff->t = (ser_rx_buff->t + 1) % ser_rx_buff->s; // advance buffer read pointer
		return data; // return
	}
}

uint8_t ser_tx_is_busy(uint8_t p)
{
	if (p == 1)
	{
		return ser_tx_buff_1.f;
	}
	
	return ser_tx_buff_0.f;
}

ISR(USART0_TX_vect)
{
	if(ser_tx_buff_0.h != ser_tx_buff_0.t)
	{
		// still data in buffer, output next char in queue and advance pointer
		UDR0 = ser_tx_buff_0.d[ser_tx_buff_0.h];
		ser_tx_buff_0.h = (ser_tx_buff_0.h + 1) % ser_tx_buff_0.s;
	}
	else
	{
		// all done
		ser_tx_buff_0.h = 0;
		ser_tx_buff_0.t = 0;
		ser_tx_buff_0.f = 0;
	}
}

ISR(USART0_RX_vect)
{	
	uint8_t data = UDR0; // read
	uint8_t temp = (ser_rx_buff_0.h + 1) % ser_rx_buff_0.s; // check buffer location first
	if(temp != ser_rx_buff_0.t) // if not overflow
	{
		ser_rx_buff_0.d[ser_rx_buff_0.h] = data; // store in buffer
		ser_rx_buff_0.h = temp; // increase array pointer
	}
}

#ifdef __AVR_ATmega644P__

ISR(USART1_TX_vect)
{
	if(ser_tx_buff_1.h != ser_tx_buff_1.t)
	{
		UDR1 = ser_tx_buff_1.d[ser_tx_buff_1.h];
		ser_tx_buff_1.h = (ser_tx_buff_1.h + 1) % ser_tx_buff_1.s;
	}
	else
	{
		ser_tx_buff_1.h = 0;
		ser_tx_buff_1.t = 0;
		ser_tx_buff_1.f = 0;
	}
}

ISR(USART1_RX_vect)
{
	uint8_t data = UDR1; // read
	uint8_t temp = (ser_rx_buff_1.h + 1) % ser_rx_buff_1.s; // check buffer location first
	if(temp != ser_rx_buff_1.t) // if not overflow
	{
		ser_rx_buff_1.d[ser_rx_buff_1.h] = data; // store in buffer
		ser_rx_buff_1.h = temp; // increase array pointer
	}
}

#endif