#include <stdint.h>
#include "stdbool.h"

#define FIRST_LED     1
#define LAST_LED      16

#define LEDS_OK 0
#define LEDS_ERROR -1

void Leds_Create(uint16_t * puerto, void(*pfn));
void Leds_TurnOn(uint16_t led);
void Leds_TurnOff(uint16_t led);
void Leds_TurnAllLeds(uint16_t status);
bool Leds_GetStatus(uint16_t led);
