ARMGNU = arm-none-eabi
CC_ARGS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding -mthumb
AS_ARGS = --warn -mcpu=cortex-m0

all: output.bin

%.o: %.s
	$(ARMGNU)-as $(AS_ARGS) $< -o $@

%.o: %.c
	$(ARMGNU)-gcc $(CC_ARGS) -c $< -o $@

output.bin: map.ld helper.o main.o
	$(ARMGNU)-ld $(LD_ARGS) -o $@.elf -T $+
	$(ARMGNU)-objcopy $@.elf $@ -O binary

upload: output.bin
	stmup -w output.bin -v

clean:
	rm -rf *.o *.bin*

.PHONY: upload all
