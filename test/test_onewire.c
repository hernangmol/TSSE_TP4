#include "unity.h"
#include "oneWire.h"
#include "mock_OW_port.h"
#include "mock_sapi.h"
#include <string.h>

OWbus_t aux;
OWbus_t* OWStruct;
unsigned char mi_str[] = "ABCDEFG";
unsigned char mi_crc = 88;    

void setUp(void)
{
   OWStruct = &aux; 
}

/* ______________Tests unitarios__________________*/

/* OWresetSearch deja las tres variables en cero*/
void test_Reset_busqueda (void)
{
    OWStruct->lastDiscrepancy = 1; 
	OWStruct->lastDeviceFlag = 2;
	OWStruct->lastFamilyDiscrepancy = 3;
    OWresetSearch(OWStruct);
    TEST_ASSERT_EQUAL_INT8 (0, OWStruct->lastDiscrepancy);
    TEST_ASSERT_EQUAL_INT8 (0, OWStruct->lastDeviceFlag);
    TEST_ASSERT_EQUAL_INT8 (0, OWStruct->lastFamilyDiscrepancy);
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
    TEST_ASSERT_EQUAL_UINT8(mi_crc,OWcrc(mi_str,7));
}

/* OWreadROM hace una lectura válida de la ROM de sensor*/
void test_Lectura_ROM(void)
{
    unsigned char p[8];
    unsigned char str_aux[7]; 
    strncpy(str_aux, mi_str, 7); 
    strncat(str_aux, &mi_crc, 1); 
    OWpresence_ExpectAndReturn(1,1,0);
    OWdelay_uS_Expect(400);
    disableInterrupts_Expect();
    OWcommand_Expect(0x33, str_aux, 8, 1, 1);
    enableInterrupts_Expect();
    TEST_ASSERT_EQUAL_INT32(0, OWreadROM( str_aux, 1, 1));
    //TEST_FAIL_MESSAGE("message"); 
}