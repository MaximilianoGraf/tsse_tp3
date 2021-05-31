/*
 * Se pueden prender todos los LEDs de una vez.
 * Se pueden apagar todos los LEDs de una vez.
 * Se puede consultar el estado de un LED apagado.
 * Se puede consultar el estado de un LED 
 * Revisar limites de los parametros.
 */
#include "unity.h"
#include "leds.h"

#define LED 5
#define INVALID_UPPER_LED 17
#define INVALID_LOWER_LED 0
 
uint16_t ledsVirtuales;

void setUp(void)
{
	Leds_Create(&ledsVirtuales);
}

void tearDown(void)
{

}

void test_LedsOffAfterCraete(void)
{
	uint16_t ledsVirtuales = 0xFFFF;
	Leds_Create(&ledsVirtuales);
	TEST_ASSERT_EQUAL_HEX16(0x0000, ledsVirtuales);	
}

void test_LedsTurnOnLed(void)
{
	Leds_TurnOn(LED);
	TEST_ASSERT_EQUAL_HEX16(1 << (LED - 1), ledsVirtuales);	
}

void test_LedsTurnOffLed(void)
{
	Leds_TurnOn(LED);
	Leds_TurnOff(LED);
	TEST_ASSERT_EQUAL_HEX16(0x0000, ledsVirtuales);	
}

void test_TurnOnAndOffManyLeds(void)
{
	uint8_t anotherLed = 3;
	Leds_TurnOn(anotherLed);
	Leds_TurnOn(LED);
	Leds_TurnOff(anotherLed);
	
	TEST_ASSERT_EQUAL_HEX16(1 << (LED - 1), ledsVirtuales);
}

void test_TurnAllLedsOn(void)
{
	Leds_TurnAllLeds(ALL_LEDS_ON);
	TEST_ASSERT_EQUAL_HEX16(0xFFFF, ledsVirtuales);
}

void test_TurnAllLedsOff(void)
{
	Leds_TurnAllLeds(ALL_LEDS_ON);
	Leds_TurnAllLeds(ALL_LEDS_OFF);
	TEST_ASSERT_EQUAL_HEX16(0x0000, ledsVirtuales);
}

void test_GetLedStatusOff(void)
{
	uint16_t led_status = Leds_GetStatus(LED);	
	TEST_ASSERT_EQUAL_HEX16(0x0000, led_status);
}

void test_GetLedStatusOn(void)
{
	Leds_TurnOn(LED);
	uint16_t led_status = Leds_GetStatus(LED);	
	TEST_ASSERT_EQUAL_HEX16(0x0001, led_status);
}

void test_CheckUpperLimit(void)
{	
	TEST_ASSERT_FALSE(Leds_CheckLimits(INVALID_UPPER_LED));		
}

void test_CheckValueBetweenLimits(void)
{	
	TEST_ASSERT_TRUE(Leds_CheckLimits(LED));	
}

void test_CheckLowerLimit(void)
{	
	TEST_ASSERT_FALSE(Leds_CheckLimits(INVALID_LOWER_LED));	
}