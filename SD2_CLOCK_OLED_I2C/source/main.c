/* Copyright 2023, DSI FCEIA UNR - Sistemas Digitales 2
 *    DSI: http://www.dsi.fceia.unr.edu.ar/
 * Copyright 2023, Guido Cicconi
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stdio.h>
#include "board.h"
#include "MKL46Z4.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
#include "fsl_smc.h"
#include "SD2_board.h"
#include "mma8451.h"
#include "oled.h"
#include "display.h"
#include "key.h"

#include "mef.h"

#define TIMER_1S 1000
#define TIMER_100MS 100
static uint32_t timer;

//=====================CLOCK TEST=======================//
//int main(void) {
//
//	int16_t accX,accY,accZ;
//	/* Inits */
//	BOARD_InitBootClocks();
//	/* Se habilita la posibilidad de operar con todos los modos de bajo consumo */
//	SMC_SetPowerModeProtection(SMC, kSMC_AllowPowerModeAll);
//
//    BOARD_InitBootPins();
//    BOARD_InitDebugConsole();
//
//    board_init();
//
//    key_init();
//
//	SysTick_Config(SystemCoreClock / 1000U);
//
//    board_configSPI0();
//
//   // mma8451_setDataRate(DR_12p5hz);
//
//	display_init();
//	display_header();
//
//
//	//timer =TIMER_100MS;
//	//mma8451_setFF_int();
//	//mma8451_setDR_int();
//    while(1)
//    {
//
//		//mef();
//    	//TEST
////    	APP_SetClockVlpr();
//    	if(timer==0)
//    	{
//    		timer=1000;
//    		board_setLed(BOARD_LED_ID_VERDE, BOARD_LED_MSG_TOGGLE);
//    	}
//
///*
//    	if(timer==0)
//    	{
//    		timer=TIMER_100MS;
//    		accX = mma8451_getAcX();
//    		accY = mma8451_getAcY();
//    		accZ = mma8451_getAcZ();
//    		display_reading(accX,accY,accZ);
//
//    	}
//
//
//    	if(mma8451_getFFEv())
//    		display_FF();
//*/
//
//    }
//    return 0 ;
//}


int main(void) {
	/* Init board hardware. */
    BOARD_InitBootClocks();

    /* Se habilita la posibilidad de operar con todos los modos de bajo consumo */
    SMC_SetPowerModeProtection(SMC, kSMC_AllowPowerModeAll);

    /* Init FSL debug console. */
    BOARD_InitDebugConsole();

    board_init();
    board_configSPI0();

    key_init();

    display_init();

    /* inicializa interrupción de systick cada 1 ms */
    SysTick_Config(SystemCoreClock / 1000U);

    while(1)
    {
    	mef();
    }

    return 0;
}


void SysTick_Handler(void)
{
	key_periodicTask1ms();
	mef_tick1ms();
	if(timer)
		timer--;
}

