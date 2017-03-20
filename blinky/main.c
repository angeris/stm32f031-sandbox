// For memory mappings see pg 45 on reference manual and for
// vector mappings see pg 24 on programming manual (map.ld and helper.s, correspondingly)

// For defines for GPIO ports see 157 and table 1 (pg 46) on reference manual
#define GPIOA_MODER 0x48000000
#define RCC_CNTRL 0x40021000
#define GPIO_CLK_ENABLE (RCC_CNTRL+0x14)

// Reset value, see 157
#define GPIOA_MODER_RESET 0x28000000

// GPIO Register structure, see 157
typedef struct {
    volatile unsigned MODER;     //0x00
    volatile unsigned OTYPER;    //0x04
    volatile unsigned OSPEEDR;   //0x08
    volatile unsigned PUPDR;     //0x0c
    volatile unsigned IDR;       //0x10
    volatile unsigned ODR;       //0x14
    volatile unsigned BSRR;      //0x18
    volatile unsigned LCKR;      //0x1c
    volatile unsigned AFRL;      //0x20
    volatile unsigned AFHR;      //0x24
    volatile unsigned BRR;       //0x28
} GPIOStruct;

void main() {
    GPIOStruct *gpioa = ((GPIOStruct *)GPIOA_MODER);

    // Set GPIO clock for GPIOA
    *((unsigned *)GPIO_CLK_ENABLE) |= 1<<17;    
    
    // Set up pin A4 (pg 157)
    gpioa->MODER    &= ~(3<<8); // Reset pin mode
    gpioa->MODER    |= 1<<8;    // Set pin mode to output
    gpioa->OTYPER   &= ~(1<<4); // Set type of output to NMOS/PMOS
    gpioa->OSPEEDR  &= ~(3<<8); // Reset speed of pin
    gpioa->OSPEEDR  |= 1<<8;    // Set speed of reads/writes to 2 MHz
    gpioa->PUPDR    &= ~(3<<8); // Reset pull-up/pull-down resistors

    unsigned i=0;
    // The nop is necessary so the loops don't get optimized out (using -O2)
    for(;;) {
        gpioa->BSRR = 1<<4;     // Set A4
        for(i=0; i<100000; i++) asm("nop");
        gpioa->BRR = 1<<4;      // Reset A4
        for(i=0; i<100000; i++) asm("nop");
    }
}