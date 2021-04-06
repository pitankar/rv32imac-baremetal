This repository implements the basic bare metal code that if needed to boot up and work with the [SparkFun RED-V RedBoard](https://www.sparkfun.com/products/15594) development board which has a [SiFive RISC-V FE310 SoC](https://www.sifive.com/chip-designer#fe310) on it. The repo is intended to be used by those who are wanting to learn `assembly` language or `embedded C` and are looking for a development environment that allows them to tinker and explore starting at the very bottom of the things.

# How it works
## The Repo
```shell
.
├── layout.ld
├── License
├── Makefile
├── README.md
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
`main.c` and `start.S` are the source files where you can append code. The processor starts off the execution from `_start` (in `start.S`), loads the stack pointer register `sp` with address pointing to the end of the RAM and then jumps to `main()` (from `main.c`). `layout.ld` is a linker script that details out which section of the code goes where in the memory. The `drv` directory holds the driver for various peripherial blocks on the SoC. `Makefile` automates compiling, uploading and, starting and attaching to debug server.

---
# Setup
Install the required components using the following command
```
❯ sudo apt install -y minicom gdb-multiarch gcc-riscv64-unknown-elf
```

----
## Testing setup

Plugin the board into the USB port. And connect to it using `minicom` as follows:
```shell
❯ sudo minicom -D /dev/ttyACM0
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
❯ make upload
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
❯ make upload
```
You should see the following output on the scree:
```shell
❯ make upload
Uploading...
Done :)
```
# Debugging
To debug using GDB you can execute the following in one terminal
```shell
❯ make debug
```
you should see the following:
```shell
❯ make debug
GDB server active... 
Use Ctrl+c to close the server!
```

Connect to the debug server by launching GDB from another terminal by executing the following commands
```shell
❯ make gdb
```
This will connect with the debug server and drop the `gdb` prompt. you should see something as below:
```shell
❯ make gdb
Reading symbols from build/firmware.elf...
_start () at src/start.S:32
32      1:  j 1b            # Spin forever
JTAG tap: riscv.cpu tap/device found: 0x20000913 (mfg: 0x489 (SiFive, Inc.), part: 0x0000, ver: 0x2)
keep_alive() was not invoked in the 1000 ms timelimit. GDB alive packet not sent! (1862 ms). Workaround: increase "set remotetimeout" in GDB
(gdb)
```

You can then use the usual `monitor` and `gdb` commands to debug further. Use `q` to quit `gdb` and `Ctrl+c` to exit the debug server.

---
# Trouble Shooting
## Recovering the board
Follow the instructions here to recover the board in case you brick it: https://github.com/riscv-rust/hifive1-recover
