CROSS_COMPILE = arm-none-eabi-
CC  = $(CROSS_COMPILE)gcc
LD  = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy
APP = fs4412.elf
BIN = fs4412.bin
CINCLUDES = -I ./include

LDFLAGS += -static -L ./lib -lc -lm -lnosys
LDFLAGS += -static -L ./lib -lgcc

include config.mk

$(APP):start/start.o main.o  $(COBJS)
	$(LD) -Ttext=0x40000000 $^ -o $@ $(LDFLAGS)
	$(OBJCOPY) -O binary $(APP) $(BIN)
	
	
%.o:%.S
	$(CC) -c $< -o $@

%.o:%.c
	$(CC) -c $< -o $@  $(CINCLUDES)