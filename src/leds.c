#include "leds.h"
#include "stdio.h"

#define ALL_LEDS_OFF  0x0000
#define ALL_LEDS_ON   0xFFFF
#define LED_ON        1
#define LED_OFF       0

static uint16_t * puntero;
static void (* pFn)(void);

uint16_t led_to_bit(uint8_t led)
{
    return (LED_ON << (led - FIRST_LED));
}

void Leds_Create(uint16_t * puerto, void(*pfn))
{
    puntero = puerto;
    *puntero = ALL_LEDS_OFF;
    pFn = pfn; 
}

bool Leds_CheckLimits(uint16_t led)
{
    return (led >= FIRST_LED && led <= LAST_LED);
}

void Leds_TurnOn(uint16_t led)
{
    if(Leds_CheckLimits(led))
    {
        *puntero = led_to_bit(led);
    }
    else
    {
        pFn();
    }
}

void Leds_TurnOff(uint16_t led)
{
    if (Leds_CheckLimits(led))
    {
        *puntero &= ~led_to_bit(led);
    }
    else
    {
        pFn();
    }
}

void Leds_TurnAllLeds(uint16_t status)
{
    *puntero = status;
}

bool Leds_GetStatus(uint16_t led)
{
    if (Leds_CheckLimits(led))
    {
        bool ledStatus = ((*puntero & led_to_bit(led)) >> led - FIRST_LED);
        return ledStatus;
    }
    else
    {
        pFn();
    }
}
