#ifndef macros_h
#define macros_h

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit)) // clear bit
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit)) // set bit
#define tog(sfr, bit) (_SFR_BYTE(sfr) ^= _BV(bit)) // toggle bit
#define nop() __asm__ __volatile__ ("nop") // no operation

#define LED1_on() cbi(LED_port, LED1_pin)
#define LED1_off() sbi(LED_port, LED1_pin)
#define LED1_tog() tog(LED_port, LED1_pin)
#define LED2_on() cbi(LED_port, LED2_pin)
#define LED2_off() sbi(LED_port, LED2_pin)
#define LED2_tog() tog(LED_port, LED2_pin)

#define button_is_pressed() bit_is_clear(button_in, button_pin)

#define switch_1_is_down() bit_is_clear(switch_in, switch_1_pin)
#define switch_2_is_down() bit_is_clear(switch_in, switch_2_pin)
#define switch_3_is_down() bit_is_clear(switch_in, switch_3_pin)
#define switch_4_is_down() bit_is_clear(switch_in, switch_4_pin)

#endif