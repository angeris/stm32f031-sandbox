#define I2C_BASE 0x40013000

typedef struct {
    volatile unsigned CR1;      //0x00
    volatile unsigned CR2;      //0x04
    volatile unsigned OAR1;     //0x08
    volatile unsigned OAR2;     //0x0c
    volatile unsigned TIMINGR;  //0x10
    volatile unsigned TIMEOUTR; //0x14
    volatile unsigned ISR;      //0x18
    volatile unsigned ICR;      //0x1c
    volatile unsigned PECR;     //0x20
    volatile unsigned RXDR;     //0x24
    volatile unsigned TXDR;     //0x28
} I2CStruct;

#define I2C ((I2CStruct *)I2C_BASE)

