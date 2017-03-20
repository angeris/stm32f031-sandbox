// For defines for GPIO ports see 157 and table 1 (pg 46) on reference manual
#define GPIOA_BASE 0x48000000

// For general RCC control see page 108
#define RCC_CNTRL 0x40021000
// For GPIO clock see page 120
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

#define GPIOA ((GPIOStruct *)GPIOA_BASE)
#define PERIPHERAL_CLOCK *((unsigned *)GPIO_CLK_ENABLE)