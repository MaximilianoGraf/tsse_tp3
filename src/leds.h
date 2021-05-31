#include <stdint.h>
#include "stdbool.h"

#define ALL_LEDS_OFF 0x0000
#define ALL_LEDS_ON  0xFFFF

#define LED_UPPER  16
#define LED_LOWER  1

void Leds_Create(uint16_t * puerto);
void Leds_TurnOn(uint16_t led);
void Leds_TurnOff(uint16_t led);
void Leds_TurnAllLeds(uint16_t status);
uint16_t Leds_GetStatus(uint16_t led);
bool Leds_CheckLimits(uint16_t led);