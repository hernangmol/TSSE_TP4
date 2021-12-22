/*============================================================================
 * Módulo de comunicación protocolo 1 Wire.
 * Archivo: oneWire.c
 * Versión: 1.2
 * Fecha 08/10/2021
 * Autor: Hernán Gomez Molino
 *===========================================================================*/


#include "oneWire.h"
#include "OW_port.h"

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