/*
 * \file port.c
 *
 * \brief PORT used to set up the correct pin configurations.
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

#include "port.h"

void port_init(void){
	/*Set up pins controlling the OPAMP configuration to have Pull-up enabled and 
	inverted states*/
	PORTC.PINCONFIG = PORT_PULLUPEN_bm | PORT_INVEN_bm;
	PORTC.PINCTRLUPD = OPAMP_CONFIG_gc;

	/*Disable the input buffer on the OPAMP pins*/
	PORTD.PINCONFIG = PORT_ISC_INPUT_DISABLE_gc;
	PORTD.PINCTRLUPD = (OPAMP_OP1_PIN_gc | OPAMP_OP0_PIN_gc);
	PORTE.PINCTRLUPD = OPAMP_OP2_PIN_gc;

	/*Setup LED0 pin and turn it off*/
	PORTB.DIRSET = PIN3_bm;
	PORTB.OUTSET = PIN3_bm;
	
	/*Setup SW0*/
	PORTB.DIRCLR = PIN2_bm;
	PORTB.PIN2CTRL = PORT_ISC_FALLING_gc | PORT_PULLUPEN_bm;
}


