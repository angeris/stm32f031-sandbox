// For general RCC control see page 108
#define RCC_BASE 0x40021000

typedef struct {
    volatile unsigned CR;        //0x00
    volatile unsigned CFGR;      //0x04
    volatile unsigned CIR;       //0x08
    volatile unsigned APB2RSTR;  //0x0c
    volatile unsigned APB1RSTR;  //0x10
    volatile unsigned AHBENR;    //0x14
    volatile unsigned APB2ENR;   //0x18
    volatile unsigned APB1ENR;   //0x1c
    volatile unsigned BDCR;      //0x20
    volatile unsigned CSR;       //0x24
    volatile unsigned AHBRSTR;   //0x28
    volatile unsigned CFGR2;     //0x2c
    volatile unsigned CFGR3;     //0x30
    volatile unsigned CR2;       //0x34
} RCCStruct;

#define RCC ((RCCStruct *)RCC_BASE)