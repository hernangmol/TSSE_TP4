#include "unity.h"
#include "oneWire.h"
#include "mock_OW_port.h"
#include "mock_sapi.h"

OWbus_t aux;
OWbus_t* OWStruct;

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
    //TEST_FAIL_MESSAGE("message");
}
