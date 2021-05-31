#include "leds.h"


static uint16_t * puntero;

uint16_t led_to_bit(uint8_t led)
{
    return (1 << (led - 1));
}

void Leds_Create(uint16_t * puerto)
{
     puntero = puerto;
    *puntero = ALL_LEDS_OFF;
}

void Leds_TurnOn(uint16_t led)
{
    if (Leds_CheckLimits(led))
    {
        *puntero = led_to_bit(led);
    }
}

void Leds_TurnOff(uint16_t led)
{
    if (Leds_CheckLimits(led))
    {
        *puntero &= ~led_to_bit(led);
    }
}

void Leds_TurnAllLeds(uint16_t status)
{
    *puntero = status;
}

uint16_t Leds_GetStatus(uint16_t led)
{
    uint16_t ledStatus = ((*puntero & led_to_bit(led)) >> led -1);
    return ledStatus;
}

bool Leds_CheckLimits(uint16_t led)
{
    return (led >= LED_LOWER && led <= LED_UPPER);
}