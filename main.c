/*
 * File:   main.c
 * Author: ricardo
 *
 * Created on February 16, 2024, 11:05 PM
 */

#define _XTAL_FREQ 8000000

#include <xc.h>
#include <stdint.h>
#include "main.h"

void main(void) {
    CLRWDT();
    // OSC = 8MHz
    OSCCONbits.IRCF = 7;
    // GPIO2
    ANSELbits.ANS2 = 0;
    GPIObits.GP2 = 0;
    TRISIObits.TRISIO2 = 0;
    // GPIO5
    GPIObits.GP5 = 0;
    TRISIObits.TRISIO5 = 0;
    // PWM
    PR2 = 0x65;
    CCP1CONbits.DC1B = 0;
    CCP1CONbits.CCP1M = 0b1100;
    CCPR1L = 0;
    // Timer2
    T2CONbits.TOUTPS = 0;
    T2CONbits.T2CKPS = 0;
    PIE1bits.TMR2IE = 0;
    PIR1bits.TMR2IF = 0;
    T2CONbits.TMR2ON = 1;
    
    uint16_t count5 = 0;
    uint16_t count2 = 0;
    uint8_t dir = 0;
    CLRWDT();
    while (1) {
//        if (PIR1bits.TMR2IF) {
//            PIR1bits.TMR2IF = 0;
            count5++;
            count2++;
//        }
        if (count5 >= 1000){
            GPIObits.GP5 = !GPIObits.GP5;
            count5 = 0;
        }
        if (count2 >= 100){
            //GPIObits.GP2 = !GPIObits.GP2;
            count2 = 0;
            if (dir){
                CCPR1L--;
                if (!CCPR1L){
                    dir = 0;
                }
            } else {
                CCPR1L++;
                if (CCPR1L >= 100){
                    dir = 1;
                }
            }
            
        }
        CLRWDT();
        __delay_ms(1);
    }
    return;
}
