// Bit-banging i2c master example for the .96" OLED display
// See blinky for comments on setup for pins

#include "gpio.h"
// #include "font.h"

#define BUF_SIZE 128*64/8
#define I2C_ADDR 0x3c

unsigned char display_buf[BUF_SIZE];


// Status LED is on P4
// SDA is on P1
// SCL is on P0
// Overall, note that the SSD1306 is fast enough such that we
// don't have to worry about delays and such on the pins.
void i2c_init() {
    PERIPHERAL_CLOCK |= 1<<17; // Enable GPIOA

    // Enable P0, P1, P4 output
    GPIOA->MODER    &= ~(3<<0 | 3<<2);
    GPIOA->MODER    |=  (1<<0 | 1<<2);
    GPIOA->OTYPER   &= ~(1<<0 | 1<<1);
    GPIOA->OSPEEDR  |=  (3<<0 | 3<<2);
    GPIOA->PUPDR    &= ~(3<<0 | 3<<2);
}
inline void scl_set() {
    GPIOA->BSRR = 1;
}
inline void scl_clear() {
    GPIOA->BRR  = 1;
}
inline void sda_set() {
    GPIOA->BSRR = 2;
}
inline void sda_clear() {
    GPIOA->BRR  = 2;
}
inline void sda_input() {
    GPIOA->MODER &= ~(3<<2);
}
// Assumes bits were in input mode
inline void sda_output() {
    GPIOA->MODER &= ~(3<<2);
    GPIOA->MODER |= 1<<2;
}
inline unsigned sda_read() {
    return GPIOA->IDR & 2;
}
inline void i2c_start() {
    sda_clear();
    scl_clear();
}
inline void i2c_end() {
    scl_set();
    sda_set();
}
unsigned i2c_write(unsigned byte) {
    // Begin send
    unsigned i=0;

    // Send byte
    for(i=1<<7; i>0; i>>=1) {
        if(byte & i) sda_set();
        else sda_clear();
        scl_set();
        scl_clear();
        sda_clear();
    }

    // Receive ACK
    sda_input();
    scl_set();
    unsigned ack = sda_read();
    scl_clear();
    sda_output();
    
    return ack;
}
void i2c_command(unsigned command) {
    i2c_start();
    if(i2c_write(I2C_ADDR<<1)) {
        i2c_end();
        return;
    }
    i2c_write(0x00);
    i2c_write(command);
    i2c_end();
}
void i2c_data(unsigned data) {
    i2c_start();
    if(i2c_write(I2C_ADDR<<1)) {
        i2c_end();
        return;
    }
    i2c_write(0x40);
    i2c_write(data);
    i2c_end();
}
void i2c_start_addr() {
    i2c_start();
    if(i2c_write(I2C_ADDR<<1)) {
        i2c_end();
        return;
    }
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
        i2c_start_addr();
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
    i2c_init();
    // Clears the display and fills it every few seconds
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

    for(i=0; i<196; i++) {
        _set_px((i*42800)>>16, (i*21400)>>16);
    }

    flush_display(); 
}