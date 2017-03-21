// See blinky for set up of pins, see i2c-bit-banging-oled for more info on
// i2c, etc.

#include "gpio.h"
#include "rcc.h"

void main() {
    // Set GPIO clock for GPIOA
    RCC->AHBENR |= 1<<17;

    // Set RCC for I2C1
    RCC->APB1ENR |= 1<<21;
    
    // Set up pin A4 (pg 157)
    GPIOA->MODER    &= ~(3<<8); // Reset pin mode
    GPIOA->MODER    |= 1<<8;    // Set pin mode to output
    GPIOA->OTYPER   &= ~(1<<4); // Set type of output to NMOS/PMOS
    GPIOA->OSPEEDR  &= ~(3<<8); // Reset speed of pin
    GPIOA->OSPEEDR  |= 1<<8;    // Set speed of reads/writes to 2 MHz
    GPIOA->PUPDR    &= ~(3<<8); // Reset pull-up/pull-down resistors

}