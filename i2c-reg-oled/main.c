// See blinky for set up of pins, see i2c-bit-banging-oled for more info on
// i2c, etc.

#include "gpio.h"
#include "rcc.h"
#include "i2c.h"

#define BUF_SIZE 128*64/8
#define I2C_ADDR 0x3c

unsigned char display_buf[BUF_SIZE];

void i2c_init() {
    // Set RCC for I2C1
    RCC->APB1ENR |= 1<<21;

    // Set GPIO clock for GPIOA
    RCC->AHBENR |= 1<<17;

    // Set Alternate function for GPIO 9/10
    GPIOA->AFRH |= 0x440;

    // Timing constant calculated by STM32CubeMX
    I2C->TIMINGR = 0x0000020B;

    // Enable analog filter
    I2C->CR1 |= 1<<12;
    
    // Set up pins A9/A10 as I2C
    // Set up alternate functions
    GPIOA->MODER    &= ~(3<<20 | 3<<18);
    GPIOA->MODER    |= 2<<20 | 2<<18;

    // Set the register to open drain
    GPIOA->OTYPER   |= 1<<10 | 1<<9;

    // Set the register speeds to high
    GPIOA->OSPEEDR  |= 3<<20 | 3<<18;

    // Set internal pull-up resistors
    GPIOA->PUPDR    &= ~(3<<20 | 3<<18);
    GPIOA->PUPDR    |= 1<<20 | 1<<18;

    // Enable I2C
    I2C->CR1 |= 1;
}
void i2c_start(unsigned n_bytes) {
    I2C->CR2 = 0; // Reset CR2 register

    // Wait up while the I2C is busy
    while(I2C->ISR & (1<<15));

    // Set the number of bytes to transfer (2), the address, and start
    I2C->CR2 |= (n_bytes<<16 | I2C_ADDR << 1);
    I2C->CR2 |= 1<<13;
}
void i2c_write(unsigned char byte) {
    // Wait if TX register isn't empty
    // while(!(I2C->ISR & 1));

     GPIOA->BSRR = 1<<4;

    // Fill TX and send it over
    I2C->TXDR = (unsigned)byte;
}
void i2c_end() {
    // Make sure everything's been sent (if it hasn't, this will be stuck in an endless loop!)
    while(I2C->ISR & (1<<6));
    GPIOA->BRR = 1<<4;

    // End I2C transmission
    I2C->CR2 |= 1<<14;

    I2C->ICR |= 1<<5;
}
void i2c_command(unsigned command) {
    i2c_start(2);
    i2c_write(0x40);
    i2c_write(command);
    i2c_end();
}
void flush_display() {
    i2c_command(0x21);
    i2c_command(0);
    i2c_command(127);

    i2c_command(0x22);
    i2c_command(0);
    i2c_command(7);

    unsigned i=0;
    unsigned j=0;
    while(i<BUF_SIZE) {
        i2c_start(17);
        i2c_write(0x40);
        for(j=0; j<16; j++) i2c_write(display_buf[i++]);
        i2c_end();
    }
}
void _set_px(unsigned x, unsigned y) { // Unsafe af
    display_buf[((y >> 3) << 7) + x] |= 1<<(y&7);
}
void _clr_px(unsigned x, unsigned y) { // Also unsafe af
    display_buf[((y >> 3) << 7) + x] &= ~(1<<(y&7));
}
void clear_all() {
    unsigned i;
    for(i=0; i<BUF_SIZE; i++) display_buf[i] = 0;
}
void main() {
    RCC->AHBENR |= 1<<17;

    GPIOA->MODER &= ~(3<<8);
    GPIOA->MODER |= 1<<8;
    GPIOA->OTYPER &= ~(1<<4);
    GPIOA->OSPEEDR &= ~(3<<8);
    GPIOA->OSPEEDR |= 1<<8;
    GPIOA->PUPDR &= ~(3<<8);

    i2c_init();

    unsigned i=0;

    // TODO: Comment all commands
    i2c_command(0xae);
    
    i2c_command(0xd5);
    i2c_command(0x80);

    i2c_command(0xa8);
    i2c_command(0x3f);


    i2c_command(0xd3);
    i2c_command(0x00);

    i2c_command(0x40);

    i2c_command(0x8d);
    i2c_command(0x14);

    i2c_command(0x20);
    i2c_command(0x00);

    i2c_command(0xa1);

    i2c_command(0xc8);

    i2c_command(0xda);
    i2c_command(0x12);

    i2c_command(0x81);
    i2c_command(0xcf);

    i2c_command(0xd9);
    i2c_command(0xf1);

    i2c_command(0xdb);
    i2c_command(0x40);

    i2c_command(0xa4);
    i2c_command(0xa6);
    i2c_command(0x2e);
    
    i2c_command(0xaf);

    clear_all();
    flush_display();


    // for(i=0; i<196; i++) {
    //     _set_px((i*42800)>>16, (i*21400)>>16);
    // }

    flush_display(); 
}