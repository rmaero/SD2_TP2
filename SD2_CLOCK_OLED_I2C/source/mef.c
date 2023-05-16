#include "stdlib.h"
#include "SD2_board.h"
#include "key.h"
#include "mma8451.h"
#include "display.h"

//Constantes de tiempo para los timers
#define TIMER_500MS 500
#define TIMER_1SEG 1000
#define TIMER_10SEG 10000

//esta en centesimas de g^2 por lo tanto 1g = 10000
#define ACCELEROMETRO_1G 10000
#define ERROR_G 100

//Estados posibles de la MEF
typedef enum
{
	INICIALIZACION=0,
	WAITING_FREEFALL,
	FREEFALL,
	WAITING_RESTART
}MEF_ENUM;

static MEF_ENUM estado=INICIALIZACION;
static uint32_t mefTimer,timerToggle;

//valor de G^2 maximo
static uint32_t maxG;


void mef()
{
	uint32_t newG;
	int16_t newX,newY,newZ;
	switch(estado)
	{
	case INICIALIZACION:
		display_header();
		maxG=0;

		//setear acelerometro para que interrumpa por caida libre
		mma8451_setFF_int();
		display_state("WAITING FREEFALL");
		estado=WAITING_FREEFALL;
		//pasar a LOW POWER y esperar la interrupcion
		APP_SetClockVlpr();
		break;

	case WAITING_FREEFALL:
		//limpio el evento por si a algun gracioso se le ocurre apretar el switch antes
		//de que ocurra el freefall
		key_getPressEv(BOARD_SW_ID_1);
		if(mma8451_getFFEv())
		{
			// transicionar a FREEFALL
			estado=FREEFALL;
			//cuando llegue la interrupcion pasar a RUN,
			APP_SetClockRunFromVlpr();
			//setear interrupcion del acelerometro a DATA READY y empezar a leer valores
			mma8451_setDR_int();
			timerToggle=TIMER_500MS;
			display_state("FREEFALL");
		}
		break;
	case FREEFALL:
		//leer acelerometro y guardo valor maximo de la aceleracion
		newX =mma8451_getAcX();

		newY =mma8451_getAcY();

		newZ =mma8451_getAcZ();

		newG = newX*newX + newY*newY + newZ*newZ;
		if (newG>maxG)
			maxG=newG;
		//hasta que se quede quieto sobre la mesa, el valor de G no es exactamente 1, calculo el error
		if( abs( newG -ACCELEROMETRO_1G) <= ERROR_G )
		{
			//deshabilito interrupciones por DATA READY
			mma8451_disableInt();
			mefTimer=TIMER_10SEG;
			estado=WAITING_RESTART;
			display_state("WAITING RESTART ");
			displayMaxG(maxG);
		}
		//parpadear el led rojo
		if(timerToggle==0)
		{
			timerToggle=TIMER_500MS;
			board_setLed(BOARD_LED_ID_ROJO, BOARD_LED_MSG_TOGGLE);
		}
		break;
	case WAITING_RESTART:
		//mostrar valor maximo en el display
		//displayMaxG(maxG);
		if(timerToggle==0)
		{
			displayMaxG(maxG);
			timerToggle=TIMER_500MS;
			board_setLed(BOARD_LED_ID_ROJO, BOARD_LED_MSG_TOGGLE);
		}
		//si pasan 10 segundos o se presiona el SW1
		if(mefTimer==0||key_getPressEv(BOARD_SW_ID_1))
		{
			board_setLed(BOARD_LED_ID_ROJO, BOARD_LED_MSG_OFF);
			estado=INICIALIZACION;

		}
		break;
	}
}


void mef_tick1ms()
{
	if(mefTimer)
		mefTimer--;

	if(timerToggle)
		timerToggle--;
}
