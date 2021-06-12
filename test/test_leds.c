/*
 * Se pueden prender todos los LEDs de una vez.
 * Se pueden apagar todos los LEDs de una vez.
 * Se puede consultar el estado de un LED apagado.
 * Se puede consultar el estado de un LED 
 * Revisar limites de los parametros.
 */
#include "unity.h"
#include "leds.h"
#include "stdio.h"
#define LED 5
#define INVALID_UPPER_LED 17
#define INVALID_LOWER_LED 0

#define ALL_LEDS_OFF 0x0000 
#define ALL_LEDS_ON  0xFFFF

#define OPERATION_OK true
#define OPERATION_FAIL false

uint16_t ledsVirtuales;
bool driverOperationControl;

void errorDetection(void)
{
	driverOperationControl = OPERATION_FAIL;
}

void setUp(void)
{
	Leds_Create(&ledsVirtuales, &errorDetection);
	driverOperationControl = OPERATION_OK;
}

void tearDown(void)
{

}

void test_LedsOffAfterCreate(void)
{
	uint16_t ledsVirtuales = 0xFFFF;
	Leds_Create(&ledsVirtuales, &errorDetection);	
	TEST_ASSERT_TRUE(driverOperationControl);	
	TEST_ASSERT_EQUAL_HEX16(0x0000, ledsVirtuales);	
}

void test_LedsTurnOnLed(void)
{
	Leds_TurnOn(LED);
	TEST_ASSERT_TRUE(driverOperationControl);	
	TEST_ASSERT_EQUAL_HEX16(1 << (LED - FIRST_LED), ledsVirtuales);	
}

void test_LedsTurnOffLed(void)
{
	Leds_TurnOn(LED);
	TEST_ASSERT_TRUE(driverOperationControl);
	Leds_TurnOff(LED);
	TEST_ASSERT_TRUE(driverOperationControl);
	TEST_ASSERT_EQUAL_HEX16(0x0000, ledsVirtuales);	
}

void test_TurnOnAndOffManyLeds(void)
{
	uint8_t anotherLed = 3;
	Leds_TurnOn(anotherLed);
	TEST_ASSERT_TRUE(driverOperationControl);
	Leds_TurnOn(LED);
	TEST_ASSERT_TRUE(driverOperationControl);
	Leds_TurnOff(anotherLed);
	TEST_ASSERT_TRUE(driverOperationControl);	
	TEST_ASSERT_EQUAL_HEX16(1 << (LED - FIRST_LED), ledsVirtuales);
}

void test_TurnAllLedsOn(void)
{
	Leds_TurnAllLeds(ALL_LEDS_ON);
	TEST_ASSERT_TRUE(driverOperationControl);
	TEST_ASSERT_EQUAL_HEX16(0xFFFF, ledsVirtuales);
}

void test_TurnAllLedsOff(void)
{
	Leds_TurnAllLeds(ALL_LEDS_ON);
	TEST_ASSERT_TRUE(driverOperationControl);
	Leds_TurnAllLeds(ALL_LEDS_OFF);
	TEST_ASSERT_TRUE(driverOperationControl);
	TEST_ASSERT_EQUAL_HEX16(0x0000, ledsVirtuales);
}

void test_GetLedStatusOff(void)
{
	uint16_t led_status = Leds_GetStatus(LED);
	TEST_ASSERT_TRUE(driverOperationControl);
	TEST_ASSERT_EQUAL_HEX16(0x0000, led_status);
}

void test_GetLedStatusOn(void)
{
	Leds_TurnOn(LED);
	TEST_ASSERT_TRUE(driverOperationControl);
	uint16_t led_status = Leds_GetStatus(LED);	
	TEST_ASSERT_TRUE(driverOperationControl);
	TEST_ASSERT_EQUAL_HEX16(0x0001, led_status);
}

void test_CheckUpperLimit(void)
{	
	TEST_ASSERT_FALSE(Leds_GetStatus(INVALID_UPPER_LED));		
	TEST_ASSERT_FALSE(driverOperationControl);
}

void test_CheckLowerLimit(void)
{	
	TEST_ASSERT_FALSE(Leds_GetStatus(INVALID_LOWER_LED));
	TEST_ASSERT_FALSE(driverOperationControl);
}