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

#ifndef __GPIO_H__
#define __GPIO_H__

#include <hifive_rev_b.h>
#include <stdint.h>

#define GPIO_0      0
#define GPIO_1      1
#define GPIO_2      2
#define GPIO_3      3
#define GPIO_4      4
#define GPIO_5      5
#define GPIO_6      6
#define GPIO_7      7
#define GPIO_8      8
#define GPIO_9      9
#define GPIO_10     10
#define GPIO_11     11
#define GPIO_12     12
#define GPIO_13     13
#define GPIO_14     14
#define GPIO_15     15
#define GPIO_16     16
#define GPIO_17     17
#define GPIO_18     18
#define GPIO_19     19
#define GPIO_20     20
#define GPIO_21     21
#define GPIO_22     22
#define GPIO_23     23

/**
 * @brief Maps the GPIO block.
 *        Note that the variable name are in 1:1
 *        correspondance with that in the Spec.
 *        For the Soc.
 */
typedef struct _gpio_s {
    uint32_t input_valPin;
    uint32_t input_enPin;
    uint32_t output_enPin;
    uint32_t output_valOutput;
    uint32_t pueInternal;
    uint32_t dsPin;
    uint32_t rise_ieRise;
    uint32_t rise_ipRise;
    uint32_t fall_ieFall;
    uint32_t fall_ipFall;
    uint32_t high_ieHigh;
    uint32_t high_ipHigh;
    uint32_t low_ieLow;
    uint32_t low_ipLow;
    uint32_t iof_en;
    uint32_t iof_sel;
    uint32_t out_xorOutput;
} gpio_s;

typedef enum _gpio_config_e {
    SPI,
    PWM,
    UART,
    I2C,
    INPUT,
    OUTPUT,
    INT_RISE_HIGH,
    INT_RISE_LOW,
    INT_LVL_HIGH,
    INT_LVL_LOW
} gpio_config_e;

void gpio_init(void);
int gpio_pin_config(uint8_t pin_no, gpio_config_e config);
int gpio_pin_set(int pin_no);
int gpio_pin_clear(int pin_no);

#endif
