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

	Serial.begin(115200) ;

#ifdef DEBUG
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

	// zTTLV Buffer
	static uint8_t ui8Array[50] ;
	static zTTLV_Buffer_t zTTLV_Buffer = { UNINITIALIZED, 0, sizeof(ui8Array), ui8Array } ;

	// Initialize the Buffer
	zTTLV_Initialize( & zTTLV_Buffer, sizeof(ui8Array) ) ;

	// Get the current time
	ulCurrentTime = millis() ;

	// Simulation Sine
	if( ulCurrentTime > ulNextTimeSine )
	{
		unsigned int uiSineVal = getSineValue() ;
		PDEBUG( "%lu : uiSineVal : %u (0x%.4X)\r\n", ulCurrentTime, uiSineVal, uiSineVal ) ;
		zTTLV_Item_t zTTLV_Item = { 11, UINT16, sizeof(uint16_t), {&uiSineVal} } ;

		zTTLV_Put( & zTTLV_Buffer, zTTLV_Item ) ;

		for ( uint8_t ui8 = 0 ; zTTLV_Buffer.last_Position > ui8 && sizeof(ui8Array) > ui8 ; ui8 ++ )
		{
#if !defined(DEBUG)
			Serial.write( ui8Array[ui8] ) ;
#endif // defined(DEBUG)
			PDEBUG( "0x%.2X ", ui8Array[ui8] ) ;
		}
		PDEBUG( "\r\n" ) ;

		zTTLV_Reset( & zTTLV_Buffer ) ;

		ulNextTimeSine = ulNextTimeSine + SINE_PERIOD ;
	}

	// Kind of watchdog. Lighting the D13 LED.
	if( ulCurrentTime > ulNextTimeLED )
	{
		PORTB ^= (1 << PB5 ) ;

		ulNextTimeLED = ulCurrentTime + BLINK_LED_PERIOD ;
	}
}
