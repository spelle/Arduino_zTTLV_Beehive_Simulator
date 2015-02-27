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
	Serial.begin(115200) ;

	// fill in the UART file descriptor with pointer to writer.
   fdev_setup_stream (&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE) ;

   // The uart is the standard output device STDOUT.
   stdout = &uartout ;
#endif

   PDEBUG("--- Arduino zTTLV Beehive Simulator ---\r\n");
}

void loop()
{
	static uint32_t ulCurrentTime = 0 ;
	static uint32_t ulNextTimeLED = BLINK_LED_PERIOD ;
	static uint32_t ulNextTimeSine = SINE_PERIOD ;

	static uint8_t ui8Array[50] ;
	static zTTLV_Buffer_t zTTLV_Buffer = { 0, sizeof(ui8Array), ui8Array } ;

	if( 0 == ulCurrentTime )
		zTTLV_Initialize( & zTTLV_Buffer, sizeof(ui8Array) ) ;

	ulCurrentTime = millis() ;

	if( ulCurrentTime > ulNextTimeSine )
	{

		unsigned int uiSineVal = getSineValue() ;
		PDEBUG( "%lu : uiSineVal : %u\r\n", ulCurrentTime, uiSineVal ) ;
		zTTLV_Item_t zTTLV_Item = { 11, UINT8, sizeof(uint8_t), {&uiSineVal} } ;

		zTTLV_Put( & zTTLV_Buffer, zTTLV_Item ) ;

		ulNextTimeSine = ulNextTimeSine + SINE_PERIOD ;
	}

	if( ulCurrentTime > ulNextTimeLED )
	{
		PORTB ^= (1 << PB5 ) ;

		ulNextTimeLED = ulCurrentTime + BLINK_LED_PERIOD ;
	}
}
