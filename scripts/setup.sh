#!/bin/bash

R=`tput setaf 1`
G=`tput setaf 2`
B=`tput bold`
U=`tput sgr0`

function echo_green() {
    echo ${G}$1${U}
}

function echo_red() {
    echo ${R}$1${U}
}

function echo_red_bld() {
    echo ${B}${R}$1${U}
}

echo_green "--------------START------------------------"

echo_green "Creating riscv_tools directory"
mkdir -p toolchain
cd toolchain

if [[ -f "riscv64-unknown-elf-gcc-10.1.0-2020.08.2-x86_64-linux-ubuntu14.tar.gz" ]]
then
    echo_green "riscv64-unknown-elf-gcc-10.1.0-2020.08.2-x86_64-linux-ubuntu14.tar.gz already exists! Using that and skipping the download."
else
    echo_green "Downloading the right RISC-V GCC Version"
    wget https://static.dev.sifive.com/dev-tools/freedom-tools/v2020.08/riscv64-unknown-elf-gcc-10.1.0-2020.08.2-x86_64-linux-ubuntu14.tar.gz
fi

if [[ -f "riscv-openocd-0.10.0-2020.08.1-x86_64-linux-ubuntu14.tar.gz" ]]
then
    echo_green "riscv-openocd-0.10.0-2020.08.1-x86_64-linux-ubuntu14.tar.gz already exists! Using that and skipping the download."
else
    echo_green "Downloading the right openocd Version"
    wget https://static.dev.sifive.com/dev-tools/freedom-tools/v2020.08/riscv-openocd-0.10.0-2020.08.1-x86_64-linux-ubuntu14.tar.gz
fi

echo_green "Extracting riscv64-unknown-elf-gcc-10.1.0-2020.08.2-x86_64-linux-ubuntu14.tar.gz"
tar -xf riscv64-unknown-elf-gcc-10.1.0-2020.08.2-x86_64-linux-ubuntu14.tar.gz
echo_green "Done!"

echo "Extracting riscv-openocd-0.10.0-2020.08.1-x86_64-linux-ubuntu14.tar.gz"
tar -xf riscv-openocd-0.10.0-2020.08.1-x86_64-linux-ubuntu14.tar.gz
echo_green "Done!"

echo_green "Doing Cleanup!"

if [[ -d "gcc" ]]
then
    rm -rf gcc
fi
mv riscv64-unknown-elf-gcc-10.1.0-2020.08.2-x86_64-linux-ubuntu14 gcc

if [[ -d "openocd" ]]
then
    rm -rf openocd
fi
mv riscv-openocd-0.10.0-2020.08.1-x86_64-linux-ubuntu14 openocd
echo_green "Done!"

echo_red_bld "The Downloads are still retained in toolchain/ and will be used the next time this setup is run again!"
echo_red_bld "Please delete them manually if you think you may not need those!"
echo_green "--------------END--------------------------"