#include "unity.h"
#include "oneWire.h"
#include "mock_OW_port.h"
#include "mock_sapi.h"
#include <string.h>

#define largoString 7
#define largoROM 8
#define largoCRC 1
#define valorReset 0
#define port 1
#define pin 1
#define presente 0
#define ausente 1
#define espera 400
#define ReadROM 0x33

OWbus_t aux;
OWbus_t* OWStruct;
unsigned char mi_str[] = "ABCDEFG";// mensaje cualquiera
unsigned char mi_crc = 88;// su CRC asociada   
unsigned char str_aux[largoString];  

void setUp(void)
{
    OWStruct = &aux;
    strncpy(str_aux, mi_str, largoString); 
    strncat(str_aux, &mi_crc, largoCRC);  
}

/* ______________Tests unitarios__________________*/

/* OWresetSearch deja las tres variables en cero*/
void test_Reset_busqueda (void)
{
    OWStruct->lastDiscrepancy = 1;// imita un valor residual 
	OWStruct->lastDeviceFlag = 2;// imita un valor residual
	OWStruct->lastFamilyDiscrepancy = 3;// imita un valor residual
    OWresetSearch(OWStruct);
    TEST_ASSERT_EQUAL_INT8 (valorReset, OWStruct->lastDiscrepancy);
    TEST_ASSERT_EQUAL_INT8 (valorReset, OWStruct->lastDeviceFlag);
    TEST_ASSERT_EQUAL_INT8 (valorReset, OWStruct->lastFamilyDiscrepancy);
}

 /* OWreadByte lee un byte del bus OneWire */
void test_Lectura_byte(void)
{
    OWreadBit_ExpectAndReturn(OWStruct,1);
    OWreadBit_ExpectAndReturn(OWStruct,1);
    OWreadBit_ExpectAndReturn(OWStruct,1);
    OWreadBit_ExpectAndReturn(OWStruct,1);
    OWreadBit_ExpectAndReturn(OWStruct,1);
    OWreadBit_ExpectAndReturn(OWStruct,1);
    OWreadBit_ExpectAndReturn(OWStruct,1);
    OWreadBit_ExpectAndReturn(OWStruct,1);
    TEST_ASSERT_EQUAL_UINT8(0xFF,OWreadByte(OWStruct));
}

/* OWcrc genera un código de redundancia cíclica correcto */
void test_Generacion_crc(void)
{
    TEST_ASSERT_EQUAL_UINT8(mi_crc,OWcrc(mi_str,largoString));
}

/* OWreadROM hace una lectura inválida (sin sensor) de la ROM de sensor*/
void test_Lectura_invalida_ROM(void)
{
    OWpresence_ExpectAndReturn(port, pin, ausente);
    TEST_ASSERT_EQUAL_INT32(-1, OWreadROM( str_aux, port, pin));
}

/* OWreadROM hace una lectura válida de la ROM de sensor*/
void test_Lectura_ROM(void)
{
    OWpresence_ExpectAndReturn(port, pin, presente);
    OWdelay_uS_Expect(espera);
    disableInterrupts_Expect();
    OWcommand_Expect(ReadROM, str_aux, largoROM, port, pin);
    enableInterrupts_Expect();
    TEST_ASSERT_EQUAL_INT32(0, OWreadROM( str_aux, port, pin));
}

