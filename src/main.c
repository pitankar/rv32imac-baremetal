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

#define BLUE_LED GPIO_5

void blink_led(void) {
    gpio_pin_config(BLUE_LED, OUTPUT);


    while (1) {
        for (volatile int i = 0; i < 500000; i++);
        gpio_pin_set(BLUE_LED);
        for (volatile int i = 0; i < 500000; i++);
        gpio_pin_clear(BLUE_LED);
    }
}

int main()
{
    gpio_init();
    uart_init(UART0);

    printf("Hello, World! :)\n\r");
    
    blink_led();

    return 0;
}