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

#include <pwm.h>

/**
 * @brief Holds the PWM instance base address, local to this file!
 *
 */
static volatile pwm_s *__pwm0_base = (volatile pwm_s*)PWM0_BASE;
static volatile pwm_s *__pwm1_base = (volatile pwm_s*)PWM1_BASE;
static volatile pwm_s *__pwm2_base = (volatile pwm_s*)PWM2_BASE;

static volatile pwm_s* get_pwm_addr(pwm_e pwm_no) {
    switch (pwm_no) {
        case PWM0: return __pwm0_base;
        case PWM1: return __pwm1_base;
        case PWM2: return __pwm2_base;
    }

    return (volatile pwm_s*)0;
}

void pwm_config(pwm_e pwm_no, pwmcfg_s *config) {
    volatile pwm_s *pwm = get_pwm_addr(pwm_no);

    pwm->pwmcfg.pwmscale = config->pwmscale;
    pwm->pwmcfg.pwmsticky = config->pwmsticky;
    pwm->pwmcfg.pwmzerocmp = config->pwmzerocmp;
    pwm->pwmcfg.pwmdeglitch = config->pwmdeglitch;
    pwm->pwmcfg.pwmenalways = config->pwmenalways;
    pwm->pwmcfg.pwmenoneshot = config->pwmenoneshot;
    pwm->pwmcfg.pwmcmp0center = config->pwmcmp0center;
    pwm->pwmcfg.pwmcmp1center = config->pwmcmp1center;
    pwm->pwmcfg.pwmcmp2center = config->pwmcmp2center;
    pwm->pwmcfg.pwmcmp3center = config->pwmcmp3center;
    pwm->pwmcfg.pwmcmp0gang = config->pwmcmp0gang;
    pwm->pwmcfg.pwmcmp1gang = config->pwmcmp1gang;
    pwm->pwmcfg.pwmcmp2gang = config->pwmcmp2gang;
    pwm->pwmcfg.pwmcmp3gang = config->pwmcmp3gang;
    pwm->pwmcfg.pwmcmp0ip = config->pwmcmp0ip;
    pwm->pwmcfg.pwmcmp1ip = config->pwmcmp1ip;
    pwm->pwmcfg.pwmcmp2ip = config->pwmcmp2ip;
    pwm->pwmcfg.pwmcmp3ip = config->pwmcmp3ip;
}

void pwm_set_counter(pwm_e pwm_no, uint32_t count) {
    volatile pwm_s *pwm = get_pwm_addr(pwm_no);
    pwm->pwmcount.pwmcount = count;
}

void pwm_set_cmp(pwm_e pwm_no, pwm_cpm_e pwm_cmp_no, uint16_t count) {
    volatile pwm_s *pwm = get_pwm_addr(pwm_no);
    pwm->pwmcpm[pwm_cmp_no].pwmcmp = count;
}

void pwm_set_scaled_count(pwm_e pwm_no, uint16_t pwms) {
    volatile pwm_s *pwm = get_pwm_addr(pwm_no);
    pwm->pwms.pwms = pwms;
}