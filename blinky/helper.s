
.cpu cortex-m0
.thumb

.thumb_func
.global start
start:
stack_init: .word 0x20001000
.word reset
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang

.thumb_func
reset:
    bl main
    b hang

.thumb_func
hang:
    b hang
.end
