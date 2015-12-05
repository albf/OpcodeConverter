/***************************************************************************
 *   Copyright (C) 2015 by                                                 *
 *   - Carlos Eduardo Millani (carloseduardomillani@gmail.com)             *
 *   - Edson Borin (edson@ic.unicamp.br)                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#include <avr/interrupt.h>
#include <avr/io.h>
#include "ARCH_encoder.h"
#include <stdint.h>
#include <stdbool.h>
	
	
#include <serial.h>

volatile uint32_t last_left = 0;
volatile uint32_t last_right = 0;

volatile uint32_t pulse_left = 0;
volatile uint32_t pulse_right = 0;

volatile uint32_t left_count = 0;
volatile uint32_t right_count = 0;

volatile uint32_t timer0_ovf_count = 0;
volatile uint32_t timer0_last_ovf_count = 0;

void reset_counter(int side)
{
	switch (side)
	{
		case RIGHT:
		right_count = 0;
		case LEFT:
		left_count = 0;
		default:
		return;
		break;
	}
}

uint32_t read_encoder_counter(int side) //Defined on ARCH
{
	switch (side)
	{
		case RIGHT:
		return right_count;
		case LEFT:
		return left_count;
		default:
		return 0;
		break;
	}
}
uint32_t read_encoder_time(int side)
{
	switch (side)
	{
		case RIGHT:
		return pulse_right;
		case LEFT:
		return pulse_left;
		default:
		return 0;
		break;
	}
}
void start_encoder(void)
{
	DDRD &= ~((1 << PD2) | (1 << PD3));
	PORTD |= ((1 << PD2) | (1 << PD3));
	EICRA |= (1 << ISC01) | (1 << ISC11); //Configures interrupt on the falling edge
	EIMSK |= (1 << INT0) | (1 << INT1); //Enables encoder interrupt
	TIMSK0 |= (1 << TOIE0);//Enables timer overflow interrupt
	sei();
}

// uint32_t millees()
// {
// 	return timer0_ovf_count;
// }

ISR(TIMER0_OVF_vect) //Timer0 overflow interrupt
{
	timer0_ovf_count++;
}

ISR(INT0_vect)
{
	register uint32_t time_now = timer0_ovf_count; 
	
	pulse_left = (time_now - last_left)>10?(time_now - last_left):pulse_left;
	last_left = time_now;
	left_count++;
}
ISR(INT1_vect)
{
	register uint32_t time_now = timer0_ovf_count; 
	pulse_right = (time_now - last_right)>10?(time_now - last_right):pulse_right;
	last_right = time_now;
	right_count++;
}

#ifdef __cplusplus
}
#endif
