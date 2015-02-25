/*
 * Arduino_zTTLV_Beehive_Simulator.h
 *
 *  Created on: Jan 22, 2015
 *      Author: sherpa
 */

#ifndef ARDUINO_ZTTLV_BEEHIVE_SIMULATOR_H_
#define ARDUINO_ZTTLV_BEEHIVE_SIMULATOR_H_

#include <Arduino.h>
#include <zTTLV_Buffer.h>

#define DEBUG

#ifdef DEBUG

#include <stdio.h>

static FILE uartout = {0} ;

static int uart_putchar (char c, FILE *stream)
{
    Serial.write(c) ;
    return 0 ;
}

#undef PDEBUG // Just in case unimplemented
#ifndef PDEBUG
	#define PDEBUG( ... ) \
		printf( __VA_ARGS__ )
#else
	#define PDEBUG( ... ) /* nothing */
#endif

#endif // DEBUG

#endif /* ARDUINO_ZTTLV_BEEHIVE_SIMULATOR_H_ */
