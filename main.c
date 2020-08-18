/*
 * \file main.c
 *
 * \brief Main source file.
 *
 *  (c) 2020 Microchip Technology Inc. and its subsidiaries.
 *
 *  Subject to your compliance with these terms,you may use this software and
 *  any derivatives exclusively with Microchip products.It is your responsibility
 *  to comply with third party license terms applicable to your use of third party
 *  software (including open source software) that may accompany Microchip software.
 *
 *  THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
 *  EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
 *  WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
 *  PARTICULAR PURPOSE.
 *
 *  IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 *  INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 *  WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
 *  BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
 *  FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
 *  ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 *  THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 */

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>


#include "opamp.h"
#include "port.h"
#include "tca.h"

typedef enum {
	SINGLE=1,
	VOLTAGE_FOLLOWER,
	NON_INVERTING_PGA,
	INVERTING_PGA,
	DIFFERENTIAL_AMPLIFIER,
	INSTRUMENTATION_AMPLIFIER
}opamp_config_t;

volatile opamp_config_t opamp_confg;
volatile uint8_t opamp_config_flag=1;
void LED0_blink(uint8_t config)
{
	tca0_set_cmp_value(config);
	tca1_enable();
}

int main(void)
{

	port_init();
	opamp_init();
	/*Configure main clock to run at 32.768 kHz*/
	_PROTECTED_WRITE(CLKCTRL.MCLKCTRLA, CLKCTRL.MCLKCTRLA | CLKCTRL_CLKSEL_OSC32K_gc); 
	tca_init();
	set_sleep_mode(SLEEP_MODE_STANDBY);
	sei();

	while (1) 
	{
		/*Read the configuration set by the user externally with pull downs on the 
		OPAMP_CONFIG_PORT and configure the op amps with the appropriate settings*/
		if (opamp_config_flag)
		{
			opamp_confg = GET_OPAMP_CONFIG();
			switch(opamp_confg)
			{
				case SINGLE:
				default:
					LED0_blink(SINGLE);
					opamp_single_config();
					break;
				case VOLTAGE_FOLLOWER:
					LED0_blink(opamp_confg);
					opamp_voltage_follower_config();
					break;
				case NON_INVERTING_PGA:
					LED0_blink(opamp_confg);
					opamp_non_inverting_pga_config();
					break;
				case INVERTING_PGA:
					LED0_blink(opamp_confg);
					opamp_inverting_pga_config();
					break;
				case DIFFERENTIAL_AMPLIFIER:
					LED0_blink(opamp_confg);
					opamp_differential_amplifier_config();
					break;
				case INSTRUMENTATION_AMPLIFIER:
					LED0_blink(opamp_confg);
					opamp_instrumentation_amplifier_config();
					break;
			}
			opamp_config_flag=0;
		}
		/*Set device in sleep*/
		sleep_mode();
	}
}


ISR(TCA0_CMP0_vect)
{
	/*Disable blinking*/
	tca1_disable();
	/*Reset counter*/
	TCA0.SINGLE.CNT = 1;
	/*Clear interrupt flag*/
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_CMP0_bm;
	opamp_config_flag=0;
	
	/*Enable PORTB interrupt again to accept reconfiguration*/
	PORTB.PIN2CTRL |= PORT_ISC_FALLING_gc;
}

ISR(PORTB_PORT_vect){
	/*Clear interrupt flag*/
	PORTB.INTFLAGS = PIN2_bm; 
	opamp_config_flag=1;
	
	/*Turn off PORTB PIN2(SW0) interrupts until 
	blinking is done (TCA0 compare match ISR triggers)*/
	PORTB.PIN2CTRL &= ~PORT_ISC_FALLING_gc;
}
