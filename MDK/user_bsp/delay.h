#ifndef __DELAY_H
#define __DELAY_H
#include "main.h"

void user_systickinit(void);

extern volatile uint32_t led_slowtime[2];

#endif