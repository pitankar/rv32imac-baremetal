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

# Config to be set by the user
FS_SDK_PATH ?= ~/Downloads/.fs/SiFive

# Infer the path of tools from the FS_SDK_PATH
RISC_V_GCC_PATH_BIN ?= $(FS_SDK_PATH)/riscv64-unknown-elf-gcc-10.1.0-2020.08.2/bin/riscv64-unknown-elf
OPENOCD_PATH ?= $(FS_SDK_PATH)/riscv-openocd-0.10.0-2020.11.0/bin

# Config
OPENOC_CONFIG_FILE = $(FS_SDK_PATH)/riscv-openocd-0.10.0-2020.11.0/share/openocd/scripts/board/sifive-hifive1-revb.cfg

# Tools
RISCV_GCC = $(RISC_V_GCC_PATH_BIN)-gcc
RISCV_GDB = $(RISC_V_GCC_PATH_BIN)-gdb

OPENOCD = $(OPENOCD_PATH)/openocd 

# compiler options
CFLAGS = -march=rv32imac -mabi=ilp32 -Wall -O0 -nostdlib -nostartfiles -ffreestanding -ggdb

# Firmware
FIRMWARE = firmware

all: $(FIRMWARE).hex

$(FIRMWARE).elf : start.S main.c
	@$(RISCV_GCC) $(CFLAGS) start.S main.c -T layout.ld -o $@

upload: $(FIRMWARE).elf
	@sudo $(OPENOCD) -f $(OPENOC_CONFIG_FILE) -c "program $^ verify reset exit"

debug: $(FIRMWARE).elf
	@sudo $(OPENOCD) -f $(OPENOC_CONFIG_FILE)


gdb:
	@$(RISCV_GDB) firmware.elf --command=scripts/debug.gdb

test:
	@$(RISCV_GDB) firmware.elf --command=scripts/bm_test.gdb

clean:
	@rm -f *.elf *.hex

.PHONY: clean
