/*
 * Arduino_zTTLV_Beehive_Simulator.cpp
 *
 *  Created on: Jan 22, 2015
 *      Author: sherpa
 */

#include "Arduino_zTTLV_Beehive_Simulator.h"
#include "Arduino_Simu_Sine.h"

#define BLINK_LED_PERIOD 1000
#define SINE_PERIOD 1000

void setup()
{
	// Set PB5 as OUTPUT
	DDRB |= (1 << PB5 ) ;
#ifdef DEBUG
	Serial.begin(115200);

	// fill in the UART file descriptor with pointer to writer.
   fdev_setup_stream (&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);

   // The uart is the standard output device STDOUT.
   stdout = &uartout ;
#endif

   PDEBUG("--- Arduino zTTLV Beehive Simulator ---\r\n");
}

void loop()
{
	static unsigned long ulCurrentTime = 0 ;
	static unsigned long ulNextTimeLED = BLINK_LED_PERIOD ;
	static unsigned long ulNextTimeSine = SINE_PERIOD ;


	ulCurrentTime = millis() ;

	if( ulCurrentTime > ulNextTimeSine )
	{
		unsigned int uiSineVal = getSineValue() ;
		PDEBUG( "%lu : uiSineVal : %u\r\n", ulCurrentTime, uiSineVal ) ;

		ulNextTimeSine = ulNextTimeSine + SINE_PERIOD ;
	}

	if( ulCurrentTime > ulNextTimeLED )
	{
		PORTB ^= (1 << PB5 ) ;

		ulNextTimeLED = ulCurrentTime + BLINK_LED_PERIOD ;
	}
}
