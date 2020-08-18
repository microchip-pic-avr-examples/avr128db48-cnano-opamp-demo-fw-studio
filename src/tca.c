/*
 * \file tca.c
 *
 * \brief TCA used to blink LED0 with PWM signal.
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

#include "tca.h"

#include <avr/io.h>

/*Initialize the TCA0 to count LED0 blinks*/
void tca0_init(void)
{
	/*Connect Event User TCA0 CNTA to Channel 0 in the Event system*/
	EVSYS.USERTCA0CNTA = EVSYS_USER_CHANNEL0_gc;
	
	/*Connect Event Generator LED0 on pin PB3 to Channel 0*/
	EVSYS.CHANNEL0 = EVSYS_CHANNEL0_PORTB_PIN3_gc;
	
	
	/*Make TCA0 count on positive edge of event*/
	TCA0.SINGLE.EVCTRL = TCA_SINGLE_EVACTA_CNT_POSEDGE_gc | TCA_SINGLE_CNTAEI_bm;
	
	TCA0.SINGLE.CMP0 = 0x1;
	
	TCA0.SINGLE.INTCTRL = TCA_SINGLE_CMP0EN_bm;
	
	TCA0.SINGLE.CTRLA = TCA_SINGLE_RUNSTDBY_bm | TCA_SINGLE_ENABLE_bm;
}

void tca0_set_cmp_value(uint8_t cmp_val)
{
	TCA0.SINGLE.CMP0 = cmp_val;
}


/*Initialize the TCA1 to create a PWM signal to blink the LED0*/
/*TCA1 is used to toggle LED0 every 0.5s when active*/
void tca1_init(void)
{
	TCA1.SPLIT.CTRLD = TCA_SINGLE_SPLITM_bm;
	
	TCA1.SPLIT.CTRLB = TCA_SPLIT_HCMP0EN_bm;
	TCA1.SPLIT.HPER = TCA_FREQ*TCA_PWM_PERIOD;
	TCA1.SPLIT.HCMP0 = TCA_FREQ*TCA_DUTY_CYCLE_S;
	
	TCA1.SPLIT.CTRLA = TCA_SINGLE_RUNSTDBY_bm | TCA_SINGLE_CLKSEL_DIV256_gc;
}

/*Initialize all used TCA timers*/
void tca_init(void){
	tca0_init();
	tca1_init();
}

void tca1_enable(void)
{
	TCA1.SPLIT.CTRLA |= TCA_SINGLE_ENABLE_bm;
}

void tca1_disable(void)
{
	TCA1.SPLIT.CTRLA &= ~TCA_SINGLE_ENABLE_bm;
}



