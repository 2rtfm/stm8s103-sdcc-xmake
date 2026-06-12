#include "inline/stm8s_gpio_inline.h"
#include "stm8s.h"
#include <stdint.h>

void delay(uint16_t t) {
  while (t--)
    ;
}

void main() {
  GPIO_Init_inline(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_SLOW);
  while (1) {
    GPIO_WriteReverse_inline(GPIOB, GPIO_PIN_5);
    delay(20000);
  }
}
