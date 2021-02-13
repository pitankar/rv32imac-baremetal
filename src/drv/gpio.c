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

#define SET_BIT(src, bit)   (src |=  (1 << bit))
#define CLEAR_BIT(src, bit) (src &= ~(1 << bit))

/**
 * @brief Holds the GPIO base address, local to this file!
 * 
 */
static volatile gpio *__gpio_base = (volatile gpio*)GPIO_BASE;

static gpio_config_e gpio_hw_function[32] = {
    PWM,        // 0
    PWM,        // 1
    SPI | PWM,  // 2
    SPI | PWM,  // 3
    SPI,        // 4
    SPI,        // 5
    SPI,        // 6
    SPI,        // 7
    SPI,        // 8
    SPI,        // 9
    SPI | PWM,  // 10
    PWM,        // 11
    I2C | PWM,  // 12
    I2C | PWM,  // 13
    0,          // 14
    0,          // 15
    UART,       // 16
    UART,       // 17
    UART,       // 18
    PWM,        // 19
    PWM,        // 20
    PWM,        // 21
    PWM,        // 22
    UART,       // 23
    0,          // 24
    0,          // 25
    SPI,        // 26
    SPI,        // 27
    SPI,        // 28
    SPI,        // 29
    SPI,        // 30
    SPI         // 31
}; 

static void clear_bit_congif(int pin_no) {
    CLEAR_BIT(__gpio_base->input_valPin, pin_no); 
    CLEAR_BIT(__gpio_base->input_enPin, pin_no);
    CLEAR_BIT(__gpio_base->output_enPin, pin_no);
    CLEAR_BIT(__gpio_base->output_valOutput, pin_no); 
    CLEAR_BIT(__gpio_base->pueInternal, pin_no);
    CLEAR_BIT(__gpio_base->dsPin, pin_no);
    CLEAR_BIT(__gpio_base->rise_ieRise, pin_no);
    CLEAR_BIT(__gpio_base->rise_ipRise, pin_no);
    CLEAR_BIT(__gpio_base->fall_ieFall, pin_no);
    CLEAR_BIT(__gpio_base->fall_ipFall, pin_no);
    CLEAR_BIT(__gpio_base->high_ieHigh, pin_no);
    CLEAR_BIT(__gpio_base->high_ipHigh, pin_no);
    CLEAR_BIT(__gpio_base->low_ieLow, pin_no);
    CLEAR_BIT(__gpio_base->low_ipLow, pin_no);
    CLEAR_BIT(__gpio_base->iof_en, pin_no);
    CLEAR_BIT(__gpio_base->iof_sel, pin_no);
    CLEAR_BIT(__gpio_base->out_xorOutput, pin_no);
}

void gpio_init(void) {
    // Set everything to 0
    __gpio_base->input_valPin = 0; 
    __gpio_base->input_enPin = 0;
    __gpio_base->output_enPin = 0;
    __gpio_base->output_valOutput = 0; 
    __gpio_base->pueInternal = 0;
    __gpio_base->dsPin = 0;
    __gpio_base->rise_ieRise = 0;
    __gpio_base->rise_ipRise = 0;
    __gpio_base->fall_ieFall = 0;
    __gpio_base->fall_ipFall = 0;
    __gpio_base->high_ieHigh = 0;
    __gpio_base->high_ipHigh = 0;
    __gpio_base->low_ieLow = 0;
    __gpio_base->low_ipLow = 0;
    __gpio_base->iof_en = 0;
    __gpio_base->iof_sel = 0;
    __gpio_base->out_xorOutput = 0;
}

int gpio_pin_config(uint8_t pin_no, gpio_config_e config) {
    if (pin_no < 0 || pin_no > 31)
        return -1;
    
    if (config < SPI || config > INT_LVL_LOW)
        return -2;

    if (config >= SPI && config <= I2C) {
        if (!(gpio_hw_function[pin_no] & config))
            return -3;
    }

    // Clear any previous configuration for the pin
    clear_bit_congif(pin_no);

    switch (config) {
        case SPI:
        case PWM:
        case UART:
        case I2C:
            __gpio_base->iof_en |= 1 << pin_no;
            if (config == PWM)
                SET_BIT(__gpio_base->iof_sel, pin_no);
            else
                CLEAR_BIT(__gpio_base->iof_sel, pin_no);
            break;
        case INPUT:
            SET_BIT(__gpio_base->input_enPin, pin_no);
            break;
        case OUTPUT:
            SET_BIT(__gpio_base->output_enPin, pin_no);
            SET_BIT(__gpio_base->out_xorOutput, pin_no);
            break;
        case INT_RISE_HIGH:
            SET_BIT(__gpio_base->rise_ieRise, pin_no);
            break;
        case INT_RISE_LOW:
            SET_BIT(__gpio_base->fall_ieFall, pin_no);
            break;
        case INT_LVL_HIGH:
            SET_BIT(__gpio_base->high_ieHigh, pin_no);
            break;
        case INT_LVL_LOW:
            SET_BIT(__gpio_base->low_ieLow, pin_no);
            break;
        default:
            return -4;
    }

    return 0;
}

int gpio_pin_set(int pin_no) {
    if (pin_no < 0 || pin_no > 31)
        return -1;
    
    SET_BIT(__gpio_base->output_valOutput, pin_no);
    return 0;
}

int gpio_pin_clear(int pin_no) {
    if (pin_no < 0 || pin_no > 31)
        return -1;
    
    CLEAR_BIT(__gpio_base->output_valOutput, pin_no);
    return 0;
}
