This repository implements the basic bare metal code that if needed to boot up and work with the [SparkFun RED-V RedBoard](https://www.sparkfun.com/products/15594) development board which has a [SiFive RISC-V FE310 SoC](https://www.sifive.com/chip-designer#fe310) on it. The repo is intended to be used by those who are wanting to learn `assembly` language or `embedded C` and are looking for a development environment that allows them to tinker and explore starting at the very bottom of the things.

# How it works
## The Repo
```shell
.
├── License
├── Makefile
├── README.md
├── scripts
│   ├── debug.gdb
│   └── layout.ld
└── src
    ├── drv
    │   ├── gpio.c
    │   ├── include
    │   │   ├── csr.h
    │   │   ├── gpio.h
    │   │   ├── hifive_rev_b.h
    │   │   ├── interrupt.h
    │   │   ├── pwm.h
    │   │   ├── timer.h
    │   │   └── uart.h
    │   ├── interrupt.c
    │   ├── pwm.c
    │   ├── timer.c
    │   └── uart.c
    ├── main.c
    └── start.S

```
## Details
`main.c` and `start.S` are the source files where you can append code. The processor starts off the execution from `_start` (in `start.S`), loads the stack pointer register `sp` with address pointing to the end of the RAM and then jumps to `main()` (from `main.c`). `layout.ld` is a linker script that details out which section of the code goes where in the memory. The `drv` directory holds the driver for various peripherial blocks on the SoC.

To assist with the compiling, uploading the code and debugging using gdb, we have the following:
- Makefile : Automates compiling, uploading and, starting and attaching to debug server.
- scripts/ : This directory houses `gdb` scripts (along with the linker script `layout.ld`) that are used to test the setup and to attach to the `gdb` server.

---
# Setup
Install the required components using the following command
```
sudo apt install -y minicom gdb-multiarch gcc-riscv64-unknown-elf
```

----
## Testing setup

Plugin the board into the USB port. And connect to it using `minicom` as follows:
```shell
sudo minicom -D /dev/ttyACM0
```
All the messages coming from the board should be seen on minicom. You may see output like:
```shell
Welcome to minicom 2.7.90

OPTIONS: I18n 
Compiled on Jul 26 2020, 10:44:57.
Port /dev/ttyACM0, 09:50:11

Press CTRL-A Z for help on special keys
```

Next, build the source and upload to board by executing:
```shell
make upload
```

If you see the `blue` LED blinking and see the following on the `minicom` screen:
```shell
Welcome to minicom 2.7.90

OPTIONS: I18n 
Compiled on Jul 26 2020, 10:44:57.
Port /dev/ttyACM0, 09:50:11

Press CTRL-A Z for help on special keys

Bench Clock Reset Complete

ATE0--> Send Flag error: #255 #255 #255 #255 AT+BLEINIT=0--> Send Flag error: #255 #255 #255 #255 AT+CWMODE=0--> Se 
Hello, World! :)
```
then everything is working as expected! To exit `minicom` use `CTRL-a + x`.

---
# Flashing/Uploading to Board
Use the following command to build and upload the code to the board
```shell
make upload
```

# Debugging
To debug using GDB you can execute the following in one terminal
```shell
make debug
```
you should see the following
```shell
❯ make debug
Open On-Chip Debugger 0.10.0+dev-snapshot (2020-08-19-11:14)
Licensed under GNU GPL v2
For bug reports, read
        http://openocd.org/doc/doxygen/bugs.html
Info : J-Link OB-K22-SiFive compiled Oct 30 2020 11:20:31
Info : Hardware version: 1.00
Info : VTarget = 3.300 V
Info : clock speed 4000 kHz
Info : JTAG tap: riscv.cpu tap/device found: 0x20000913 (mfg: 0x489 (SiFive, Inc.), part: 0x0000, ver: 0x2)
Info : datacount=1 progbufsize=16
Info : Disabling abstract command reads from CSRs.
Info : Examined RISC-V core; found 1 harts
Info :  hart 0: XLEN=32, misa=0x40101105
Info : starting gdb server for riscv.cpu.0 on 3333
Info : Listening on port 3333 for gdb connections
Info : Found flash device 'issi is25lp032' (ID 0x0016609d)
Ready for Remote Connections
Info : Listening on port 6666 for tcl connections
Info : Listening on port 4444 for telnet connections
```

Connect to the debug server by launching GDB from another terminal by executing the following commands
```shell
make gdb
```
This will connect with the debug server and drop the `gdb` prompt. you should see something as below:
```shell
❯ make gdb
GNU gdb (Ubuntu 9.2-0ubuntu2) 9.2
Copyright (C) 2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from build/firmware.elf...
_start () at src/start.S:31
31      1:  j 1b            # Spin forever
JTAG tap: riscv.cpu tap/device found: 0x20000913 (mfg: 0x489 (SiFive, Inc.), part: 0x0000, ver: 0x2)
keep_alive() was not invoked in the 1000 ms timelimit. GDB alive packet not sent! (1847 ms). Workaround: increase "set remotetimeout" in GDB
(gdb)
```

You can then use the usual `monitor` and `gdb` commands to debug further.

---
# Trouble Shooting
## Recovering the board
Follow the instructions here to recover the board in case you brick it: https://github.com/riscv-rust/hifive1-recover
