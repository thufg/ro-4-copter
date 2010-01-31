/*
 * Please refer to the pin chart document
 *
*/

#ifndef pindef_h
#define pindef_h

#include <avr/io.h>

#define roll_accel_chan 0
#define pitch_accel_chan 1
#define vert_accel_chan 2
#define roll_gyro_chan 3
#define pitch_gyro_chan 4
#define yaw_gyro_chan 5

#define esc_port PORTD
#define esc_ddr DDRD
#define esc_rst_pin 4
#define esc_clk_pin 5
#define esc_dat_pin 7

#define f_mot_chan 0
#define b_mot_chan 1
#define l_mot_chan 2
#define r_mot_chan 3

#define ppm_port PORTD
#define ppm_ddr DDRD
#define ppm_pin 6

#define LED_port PORTC
#define LED_ddr DDRC
#define LED1_pin 6 // red
#define LED2_pin 7 // yellow

#define button_port PORTB
#define button_in PINB
#define button_ddr DDRB
#define button_pin 4

#define switch_port PORTB
#define switch_in PINB
#define switch_ddr DDRB
#define switch_1_pin 3
#define switch_2_pin 2
#define switch_3_pin 1
#define switch_4_pin 0

#endif