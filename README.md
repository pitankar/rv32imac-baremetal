This repository implements the basic bare metal code that if needed to boot up and work with the [SparkFun RED-V RedBoard](https://www.sparkfun.com/products/15594) development board which has a [SiFive RISC-V FE310 SoC](https://www.sifive.com/chip-designer#fe310) on it. The repo is intended to be used by those who are wanting to learn `assembly` language or `embedded C` and are looking for a development environment that allows them to tinker and explore starting at the very bottom of the things.
# Setup
You would need to download the Freedom Studio SDK and set `FS_SDK_PATH` variable within the Makefile. You can get it from here: [Freedom Studio — v2020.11.0](https://github.com/sifive/freedom-studio/releases/tag/v2020.11.1)

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
# Testing setup
If you want to ensure that everything work as expected then you can build the default source without any changes and upload to the board. You can run the following in sequence:
- Build the source and upload to board
```shell
make upload
```
- Start a debug session
```shell
make debug
```
- Wait until you see
```shell
...
Info : Listening on port 3333 for gdb connections
Info : Found flash device 'issi is25lp032' (ID 0x0016609d)
Ready for Remote Connections
Info : Listening on port 6666 for tcl connections
Info : Listening on port 4444 for telnet connections
```
- In a separate terminal (in the root location of this repo) start the `gdb` session
```
make test
```
Following output will should get printed 
```
❯ make test
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
0x00001004 in ?? ()
JTAG tap: riscv.cpu tap/device found: 0x20000913 (mfg: 0x489 (SiFive Inc), part: 0x0000, ver: 0x2)
keep_alive() was not invoked in the 1000 ms timelimit. GDB alive packet not sent! (1877 ms). Workaround: increase "set remotetimeout" in GDB
Disabling abstract command writes to CSRs.
$1 = 42
A debugging session is active.

        Inferior 1 [Remote target] will be detached.

Quit anyway? (y or n) [answered Y; input not from terminal]
[Inferior 1 (Remote target) detached]
```
The `$1 = 42` print confirms that everything is working as expected!

---
# Trouble Shooting
## Recovering the board
Follow the instructions here to recover the board in case you brick it: https://github.com/riscv-rust/hifive1-recover