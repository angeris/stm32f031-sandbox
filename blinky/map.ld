/* This is as given in pg 45 in the manual. */

MEMORY
{
    flash : ORIGIN = 0x08000000, LENGTH = 0x2000
    sram  : ORIGIN = 0x20000000, LENGTH = 0x1000
}

SECTIONS
{
    .text   : {*(.text*)}   > flash
    .rodata : {*(.rodata*)} > flash
    .bss    : {*(.bss*)}    > flash
}