// See blinky for comments on setup

// Bit-banging i2c master example for the .96" OLED display

#include "gpio.h"
#include "font.h"

// SDA is on P1
// SCL is on P0

void main() {
    PERIPHERAL_CLOCK |= 1<<17;

    GPIOA->MODER    &= ~(3<<8);
    GPIOA->MODER    |= 1<<8;
    GPIOA->OTYPER   &= ~(1<<4);
    GPIOA->OSPEEDR  &= ~(3<<8);
    GPIOA->OSPEEDR  |= 3<<8;
    GPIOA->PUPDR    &= ~(3<<8);

    unsigned i=0;
    
}