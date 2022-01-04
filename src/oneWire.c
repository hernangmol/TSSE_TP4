/*============================================================================
 * Módulo de comunicación protocolo 1 Wire.
 * Archivo: oneWire.c
 * Versión: 1.3.beta
 * Fecha 08/10/2021
 * Autor: Hernán Gomez Molino
 *===========================================================================*/

#include "oneWire.h"
#include "OW_port.h"

#define espera 400
#define ReadROM 0x33

/*=============================================================================
* FUNCIÓN: OWresetSearch
* Que hace: Inicializa los parámetros de busqueda (OWsearch).
* PARÁMETROS:
* Que recibe:(puntero a OWbus_t) estructura que indentifica el bus a leer.
* Que devuelve: N/A
* Variables externas que modifca: N/A
*============================================================================*/
void OWresetSearch(OWbus_t* OneWireStruct)
{
	OneWireStruct->lastDiscrepancy = 0;
	OneWireStruct->lastDeviceFlag = 0;
	OneWireStruct->lastFamilyDiscrepancy = 0;
}

/*=============================================================================
* FUNCIÓN: OWreadByte
* Que hace: lee un byte del bus oneWire.
* PARÁMETROS:
* Que recibe:(puntero a OWbus_t) estructura que indentifica el bus a leer.
* Que devuelve: (char) byte leido.
* Variables externas que modifca: N/A
*============================================================================*/
char OWreadByte(OWbus_t* OneWireStruct)
{
	unsigned char i = 8, byte = 0;
	while (i--)
	{
		byte >>= 1;
		byte |= (OWreadBit(OneWireStruct) << 7);
	}
	return byte;
}


/*=============================================================================
* FUNCIÓN: OWreadROM
* Que hace: Lee la dirección del dispositivo oneWire (ROM).
* PARÁMETROS:
* Que recibe: char * buffer8, dirección del buffer para guardar respuesta
* 			  int port, int pin puerto y pin del bus oneWire
* Que devuelve:  -1 si no hay lectura, 0 si hay lectura.
* Variables externas que modifca: N/A
*============================================================================*/
int OWreadROM(unsigned char * buffer, int port, int pin)
{
	int rv = -1;
	unsigned char crc = 0;

	if(OWpresence(port, pin)==0)
	{
		OWdelay_uS(espera);
		disableInterrupts();
		// comando Read ROM
		OWcommand(ReadROM, buffer, 8, port, pin);
		enableInterrupts();
		// chequea CRC
		crc = OWcrc(buffer,7);
		if(crc == buffer[7])
		{
			rv = 0;
		}
	}
	return rv;
}

/*=============================================================================
* FUNCIÓN: OWcrc
* Que hace: Calcula el CRC para comparar con el enviado por el dispositivo.
* PARÁMETROS:
* Que recibe: char* code, puntero a la copia de la ROM o scratchpad
* 			  char n, longitud (7 para ROM, 8 para scratchpad)
* Que devuelve: el CRC calculado (char)
* Variables externas que modifca: N/A
* Nota: Implementado según datasheet - página 9.
* 		(https://datasheets.maximintegrated.com/en/ds/DS18B20.pdf)
*============================================================================*/
unsigned char OWcrc(unsigned char* code, char n)
{
	unsigned char crc=0, inbyte, i, mix;

	// recorre cada byte
	while(n--)
	{
		inbyte = *code++;
		// recorre bit a bit
		for(i=8; i; i--)
		{
			// calcula el carry
			mix= (crc ^ inbyte) & 0x01;
			// corrimiento a derecha de CRC
			crc >>= 1;
			// si carry es uno
			if(mix)
			{
				// hace XOR bitwise bits 7, 3 y 2
				crc ^= 0x8C;
			}
			// corrimiento a derecha del byte de entrada
			inbyte >>= 1;
		}
	}
	return crc;
}
