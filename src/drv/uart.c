/**
 * MIT License
 * 
 * Copyright (c) 2021 Piyush Itankar <pitankar@gmail.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <gpio.h>
#include <uart.h>

volatile uart_s *__uart0 = (volatile uart_s *)(UART0_BASE);
volatile uart_s *__uart1 = (volatile uart_s *)(UART1_BASE);

void uart_init(uart_e uart) {
    uint32_t tx_pin, rx_pin;
    volatile uart_s *u = uart ? __uart1 : __uart0;

    u->div = BAUD_115200;

    tx_pin = uart ? UART1_TX : UART0_TX;
    rx_pin = uart ? UART1_RX : UART0_RX;

    gpio_pin_config(tx_pin, UART);
    gpio_pin_config(rx_pin, UART);
}

void uart_putc(uart_e uart, char c) {
    volatile uart_s *u = uart ? __uart1 : __uart0;
    u->txdata = c;
}

void printf(const char *str) {
    while (*str)
        uart_putc(UART0, *(str++));
}
