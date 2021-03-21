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

#ifndef __PWM_H__
#define __PWM_H__

#include <stdint.h>

#define PWM0_BASE (0x10015000)
#define PWM1_BASE (0x10025000)
#define PWM2_BASE (0x10035000)

#define PWM_NUM 4

typedef struct _pwmcfg_s {
    uint32_t pwmscale : 4;
    uint32_t reserved0: 4;
    uint32_t pwmsticky: 1;
    uint32_t pwmzerocmp: 1;
    uint32_t pwmdeglitch: 1;
    uint32_t reserved1: 1;
    uint32_t pwmenalways: 1;
    uint32_t pwmenoneshot: 1;
    uint32_t reserved2: 2;
    uint32_t pwmcmp0center: 1;
    uint32_t pwmcmp1center: 1;
    uint32_t pwmcmp2center: 1;
    uint32_t pwmcmp3center: 1;
    uint32_t reserved3: 4;
    uint32_t pwmcmp0gang: 1;
    uint32_t pwmcmp1gang: 1;
    uint32_t pwmcmp2gang: 1;
    uint32_t pwmcmp3gang: 1;
    uint32_t pwmcmp0ip: 1;
    uint32_t pwmcmp1ip: 1;
    uint32_t pwmcmp2ip: 1;
    uint32_t pwmcmp3ip: 1;
} pwmcfg_s;


typedef struct _pwmcount_s {
    uint32_t pwmcount: 31;
    uint32_t reserved: 1;
} pwmcount_s;

typedef struct _pwms_s {
    uint32_t pwms: 16;
    uint32_t reserved: 16;
} pwms_s;

typedef struct _pwmcpm_s {
    uint32_t pwmcmp: 16;
    uint32_t reserved: 16;
} pwmcpm_s;

/**
 * @brief Maps the PWM blovk
 *        Note that the variable name are in 1:1
 *        correspondance with that in the Spec.
 *        For the Soc.
 */
typedef struct _pwm_s {
    pwmcfg_s pwmcfg;
    uint32_t reserved0;
    pwmcount_s pwmcount;
    uint32_t reserved1;
    pwms_s pwms;
    uint32_t reserved2[3];
    pwmcpm_s pwmcpm[PWM_NUM];
} pwm_s;

#endif