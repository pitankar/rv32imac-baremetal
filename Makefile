# 
# MIT License
# 
# Copyright (c) 2021 Piyush Itankar <pitankar@gmail.com>
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

# openocd
OPENOCD = openocd

# openocd board config
OPENOC_CONFIG_FILE = board/sifive-hifive1-revb.cfg

# gcc
RISCV_TOOL = riscv64-unknown-elf
RISCV_GCC = $(RISCV_TOOL)-gcc
RISCV_NM = $(RISCV_TOOL)-nm
RISCV_OBJDUMP = $(RISCV_TOOL)-objdump

# gdb
RISCV_GDB = gdb-multiarch

# compiler options
CFLAGS = -march=rv32imac -mabi=ilp32 -Wall -O0 -nostdlib -nostartfiles -ffreestanding -ggdb

# Firmware
FIRMWARE = firmware

# build/
BUILD = build

# source Files
INC = src/drv/include

SRC = src/start.S \
	  src/drv/interrupt.c \
	  src/drv/timer.c \
	  src/drv/gpio.c \
	  src/drv/pwm.c \
	  src/drv/uart.c \
      src/main.c

all: $(BUILD)/$(FIRMWARE).elf

$(BUILD)/$(FIRMWARE).elf: $(SRC)
	@mkdir -p $(BUILD) 
	@$(RISCV_GCC) $(CFLAGS) -I$(INC) $^ -T scripts/layout.ld -o $@
	@$(RISCV_NM) $@ > $(BUILD)/$(FIRMWARE).sections
	@$(RISCV_OBJDUMP) -d $@ > $(BUILD)/$(FIRMWARE).disassembly

upload: $(BUILD)/$(FIRMWARE).elf
	@sudo $(OPENOCD) -f $(OPENOC_CONFIG_FILE) -c "program $^ verify reset exit"

debug: $(BUILD)/$(FIRMWARE).elf
	@sudo $(OPENOCD) -f $(OPENOC_CONFIG_FILE)

gdb: $(BUILD)/$(FIRMWARE).elf
	@$(RISCV_GDB) $^ --command=scripts/debug.gdb

clean:
	@rm -rf build/

.PHONY: clean
