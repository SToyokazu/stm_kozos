# Windows11の環境パスでツールチェインや書き込みツールにはパスが通っている前提

ARCH	 = arm-none-eabi
ADDNAME	:= $(ARCH)-

AR		:= $(ADDNAME)ar
AS 		:= $(ADDNAME)as
CC 		:= $(ADDNAME)gcc
LD		:= $(ADDNAME)ld
NM		:= $(ADDNAME)nm
OBJCOPY	:= $(ADDNAME)objcopy
OBJDUMP	:= $(ADDNAME)objdump
RANLIB	:= $(ADDNAME)ranlib
STRIP	:= $(ADDNAME)strip

STM32WRITE	= STM32_Programmer_CLI 
WRITE_ADDR  = 0x08000000

CSRC		:= $(wildcard *.c)
ASRC		:= $(wildcard *.s)
OBJS		:= $(CSRC:.c=.o) $(ASRC:.s=.o)
LDSCRIPT	:= ld.scr								# リンカスクリプトは固有の名前に

TARGET	 	= kzload

MPUFLAGS	 = -mcpu=cortex-m4						# CPU固有のフラグ
MPUFLAGS	+= -mfpu=fpv4-sp-d16 -mfloat-abi=hard	# FPU固有のフラグ
MPUFLAGS	+= -mthumb								# Thumb命令を使うフラグ

CFLAGS		 = $(MPUFLAGS)							# MPU固有のフラグ
CFLAGS		+= -Wall -Wextra 						# 警告を出すフラグ
CFLAGS		+= -O0									# 最適化レベルを指定するフラグ(0:最適化なし) 
CFLAGS		+= -g3									# デバッグ情報を追加するフラグ
CFLAGS		+= -std=gnu11							# C言語の規格を指定するフラグ
CFLAGS		+= -nostdinc							# 標準ライブラリを使わないフラグ
CFLAGS		+= -ffreestanding						# ベアメタル環境であることを示すフラグ
CFLAGS		+= -I.									# インクルードパスを指定するフラグ

ASFLAGS		+= $(MPUFLAGS)							# MPU固有のフラグ

LFLAGS		 = $(MPUFLAGS)							# MPU固有のフラグ
LFLAGS		+= -nostdlib							# 標準ライブラリを使わないフラグ
LFLAGS		+= -static								# 静的リンクするフラグ
LFLAGS		+= -T $(LDSCRIPT)						# リンカスクリプトを指定するフラグ
LFLAGS		+= -L.									# ライブラリパスを指定するフラグ
LFLAGS		+= -Wl,-Map=$(TARGET).map,--cref		# リンカにマップファイルを出力させるフラグ

all:	$(TARGET)

image:	$(TARGET).srec

write:	$(TARGET).srec
	$(STM32WRITE) -c port=SWD -w $(TARGET).srec $(WRITE_ADDR) -v -rst

clean:
	del /Q $(OBJS) $(TARGET) $(TARGET)_dbg.elf $(TARGET).srec $(TARGET).map

$(TARGET):	$(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LFLAGS)
	copy $(TARGET) $(TARGET)_dbg.elf
	$(STRIP) $(TARGET)

%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

%.o:	%.s
	$(CC) $(ASFLAGS) -c $< -o $@

$(TARGET).srec:	$(TARGET)
	$(OBJCOPY) -O srec $(TARGET) $(TARGET).srec