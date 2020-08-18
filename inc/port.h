/*
 * \file port.h
 *
 * \brief PORT header file.
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


#ifndef PORT_H_
#define PORT_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define OPAMP_CONFIG_gc (PIN6_bm|PIN5_bm|PIN4_bm)
#define OPAMP_CONFIG_gp PIN4_bp
#define OPAMP_CONFIG_PORT PORTC
#define GET_OPAMP_CONFIG() ((OPAMP_CONFIG_PORT.IN & OPAMP_CONFIG_gc) >> OPAMP_CONFIG_gp)
#define OPAMP_OP0_PIN_gc (PIN3_bm | PIN2_bm | PIN1_bm)
#define OPAMP_OP1_PIN_gc (PIN7_bm | PIN5_bm | PIN4_bm)
#define OPAMP_OP2_PIN_gc (PIN3_bm | PIN2_bm | PIN1_bm) 

void port_init(void);

#endif /* PORT_H_ */
