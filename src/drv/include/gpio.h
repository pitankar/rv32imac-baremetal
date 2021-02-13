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

#include <stdint.h>

#define GPIO_BASE (0x10012000U)

/**
 * @brief Maps the GPIO block.
 *        Note that the variable name are in 1:1
 *        correspondance with that in the Spec.
 *        For the Soc.
 */
typedef struct _gpio {
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
    uint32_t out_xorOutput;
} gpio;


/**
 * @brief Get the gpio base object
 * 
 * @return gpio* 
 */
volatile gpio* get_gpio_base(void);

#endif