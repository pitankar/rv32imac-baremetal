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

#include <csr.h>
#include <interrupt.h>
#include <stdint.h>
#include <timer.h>

#define MIE_OFFSET      (0x3)
#define MIP_OFFSET      (0x7)
#define MIE             (0x1 << MIE_OFFSET)
#define MIP             (0x1 << MIP_OFFSET)

#define LOCAL_INT_MASK  (0xF)
#define CAUSE_TIMER     (0x7)

#define m_interrupt __attribute__ ((aligned (8))) __attribute__ ((interrupt ("machine"))) void

static m_interrupt trap_handler(void) {
    uint32_t cause;

    csr_r(cause, mcause);

    cause &= LOCAL_INT_MASK;

    switch (cause) {
        case CAUSE_TIMER:
            timer_hanlder();
            break;
        default:
            return;
    }
}

void trap_setup(void) {
    uint32_t val;

    csr_w(trap_handler, mtvec);

    csr_r(val, mstatus);
    val = val | MIE;
    csr_w(val, mstatus);

    csr_r(val, mie);
    val = val | MIP;
    csr_w(val, mie);
}
