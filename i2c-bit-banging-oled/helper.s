
.cpu cortex-m0
.thumb

.thumb_func
.global start
start:
// Vector table, see pg 24 in programming manual
stack_init: .word 0x20001000 // Initial stack pointer (note that the stack grows *down*!)
.word reset // reset
.word hang  // NMI
.word hang  // HardFault
.word hang  // Reserved
.word hang  // Reserved
.word hang  // Reserved
.word hang  // Reserved
.word hang  // Reserved
.word hang  // Reserved
.word hang  // Reserved
.word hang  // SVCall
.word hang  // Reserved
.word hang  // Reserved
.word hang  // PendSV
.word hang  // SysTick

.thumb_func
reset:
    bl main
    b hang

.thumb_func
hang:
    b hang

.end
