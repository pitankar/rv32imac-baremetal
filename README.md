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
│   ├── layout.ld
│   └── setup.sh
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
You will need the `risc-v-gcc` and `openocd` to be able to compile and upload the output to the board. The `setup.sh` script in the `scripts` directory can be used to automatically setup the tools required. The script will download and extract the right versions of `gcc` and `openocd` which are also available as part of [sifive freedom-tools - August 2020 Tools Release](https://github.com/sifive/freedom-tools/releases/tag/v2020.08.0). To launch the setup execute the following:
```
make
```

Make detects the missing `toolchain/` directory and executes the following on user's behalf. If Make fails for whatever reason, you can manually execute the following to install the required tools.

```shell
chmod +x scripts/setup.sh
./scripts/setup.sh
```

If all goes well you should see the following prints
```shell
❯ ./scripts/setup.sh
--------------START------------------------
Creating riscv_tools directory
Downloading the right RISC-V GCC Version
--2021-02-07 22:11:17--  https://static.dev.sifive.com/dev-tools/freedom-tools/v2020.08/riscv64-unknown-elf-gcc-10.1.0-2020.08.2-x86_64-linux-ubuntu14.tar.gz
Resolving static.dev.sifive.com (static.dev.sifive.com)... 13.249.214.81, 13.249.214.96, 13.249.214.75, ...
Connecting to static.dev.sifive.com (static.dev.sifive.com)|13.249.214.81|:443... connected.
HTTP request sent, awaiting response... 200 OK
Length: 356973576 (340M) [application/x-gzip]
Saving to: ‘riscv64-unknown-elf-gcc-10.1.0-2020.08.2-x86_64-linux-ubuntu14.tar.gz’

riscv64-unknown-elf-gcc-10.1.0-2020.08 100%[===========================================================================>] 340.44M  29.2MB/s    in 11s

2021-02-07 22:11:29 (29.8 MB/s) - ‘riscv64-unknown-elf-gcc-10.1.0-2020.08.2-x86_64-linux-ubuntu14.tar.gz’ saved [356973576/356973576]

Downloading the right openocd Version
--2021-02-07 22:11:29--  https://static.dev.sifive.com/dev-tools/freedom-tools/v2020.08/riscv-openocd-0.10.0-2020.08.1-x86_64-linux-ubuntu14.tar.gz
Resolving static.dev.sifive.com (static.dev.sifive.com)... 13.249.214.53, 13.249.214.75, 13.249.214.96, ...
Connecting to static.dev.sifive.com (static.dev.sifive.com)|13.249.214.53|:443... connected.
HTTP request sent, awaiting response... 200 OK
Length: 3485902 (3.3M) [application/x-gzip]
Saving to: ‘riscv-openocd-0.10.0-2020.08.1-x86_64-linux-ubuntu14.tar.gz’

riscv-openocd-0.10.0-2020.08.1-x86_64- 100%[===========================================================================>]   3.32M  --.-KB/s    in 0.1s

2021-02-07 22:11:29 (22.8 MB/s) - ‘riscv-openocd-0.10.0-2020.08.1-x86_64-linux-ubuntu14.tar.gz’ saved [3485902/3485902]

Extracting riscv64-unknown-elf-gcc-10.1.0-2020.08.2-x86_64-linux-ubuntu14.tar.gz
Done!
Extracting riscv-openocd-0.10.0-2020.08.1-x86_64-linux-ubuntu14.tar.gz
Done!
Doing Cleanup!
Done!
The Downloads are still retained in toolchain/ and will be used the next time this setup is run again!
Please delete them manually if you think you may not need those!
--------------END--------------------------
```
Make may also attempt to build the source and you may see few more prints.

**Note that the downloads are retained and used next time the setup is run again.**

----
## Testing setup
If you want to ensure that everything works as expected then you can build the default source without any changes and upload to the board. You can run the following in sequence:

Build the source and upload to board
```shell
make upload
```

If you see the `blue` LED blinking and `Hello, World! :)` on uart0 port, then everything is working as expected! :)

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
Open On-Chip Debugger 0.10.0+dev (SiFive OpenOCD 0.10.0-2020.11.0)
Licensed under GNU GPL v2
For bug reports:
        https://github.com/sifive/freedom-tools/issues
Info : J-Link OB-K22-SiFive compiled Oct 30 2020 11:20:31
Info : Hardware version: 1.00
Info : VTarget = 3.300 V
Info : clock speed 4000 kHz
Info : JTAG tap: riscv.cpu tap/device found: 0x20000913 (mfg: 0x489 (SiFive Inc), part: 0x0000, ver: 0x2)
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
GNU gdb (SiFive GDB 9.1.0-2020.08.2) 9.1
Copyright (C) 2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "--host=x86_64-pc-linux-gnu --target=riscv64-unknown-elf".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://github.com/sifive/freedom-tools/issues>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from firmware.elf...
_start () at start.S:29
29      1:  j 1b
JTAG tap: riscv.cpu tap/device found: 0x20000913 (mfg: 0x489 (SiFive Inc), part: 0x0000, ver: 0x2)
keep_alive() was not invoked in the 1000 ms timelimit. GDB alive packet not sent! (1919 ms). Workaround: increase "set remotetimeout" in GDB
(gdb)
```

`monitor` and `gdb` can be used to debug further.

---
# Trouble Shooting
## Recovering the board
Follow the instructions here to recover the board in case you brick it: https://github.com/riscv-rust/hifive1-recover