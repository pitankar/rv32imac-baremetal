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

#include <timer.h>

#define MTIMECMP_OFFSET (0x4000)
#define MTIME_OFFSET    (0xbff8)

static volatile uint64_t *_mtimecmp = (volatile uint64_t*)(CLINT_BASE + MTIMECMP_OFFSET);
static volatile uint64_t *_mtime    = (volatile uint64_t*)(CLINT_BASE + MTIME_OFFSET);

static timer_s __timer;

static void update_timer(void) {
    *_mtimecmp = *_mtime + __timer.period;
}

void timer_setup(uint32_t period, timer_handler_t handler) {
    __timer.period = period;
    __timer.handler = handler;

    update_timer();
}

void timer_hanlder (void) {
    if (__timer.handler)
        __timer.handler();

    if (__timer.period)
        update_timer();
}
