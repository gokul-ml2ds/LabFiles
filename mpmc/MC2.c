/*
 * File:   newmain.c
 * Author: Kaustubh Venkatesh
 * Created on 2 June, 2021, 5:31 PM
 */

// PIC18F4550 Configuration Bit Settings
// 'C' source line config statements

#pragma config PLLDIV = 4       // PLL Prescaler Selection bits (Divide by 4 (16 MHz oscillator input))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
// #pragma config FOSC = HSPLL_HS   Oscillator Selection bits (HS oscillator, PLL enabled (HSPLL))
#pragma config FOSC = INTOSC_EC    //Select the Internal oscilator
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = ON     // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for low-power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

#include <xc.h>

void delay1s(); // Function to cause a delay of 1s using the internal clock
void __interrupt() ISR(void); //ISR Function to handle interrupts

void main(void) {
    
    TRISA = 0;      // all output (except RA7 not implemented)
    TRISB = 0;      // all output
    TRISC = 0;      // all output (except RC3 not implmented, RC4,5 only input or USB
    TRISD = 0xFF;      // Input port
    TRISE = 0;      // all output (only RE0, RE1, RE2 exist)
    OSCCON = 0xF2;  // internal oscillator, 8MHz
    
 
    
    while (1){
        delay1s();
        PORTA = 0xFF;    // test pattern
        PORTB = 0xFF;    // test pattern
        PORTC = 0x00;    // test pattern
        //PORTD = 0x55;     test pattern
        PORTE = 0x55;    // test pattern
        delay1s();
        PORTA = 0xaa;    // test pattern
        PORTB = 0x00;    // test pattern
        PORTC = 0x00;    // test pattern
        //PORTD = 0xaa;     test pattern
        PORTE = 0xaa;    // test pattern
        
        if(RD0 == 0){
            INTCONbits.GIE = 1; // Enable The Global Interrupt
            INTCONbits.INT0E = 1; // Enable INT
            break;
        }
    }
        return;
}

void delay1s(){
    int m,n;
    for (m = 0;m<200; m++){
        while(n>0){
            n--;
        }
    }
}

void __interrupt() ISR(void){
    PORTC = ~PORTC; //invert the value at port C
    INTCONbits.INT0F =0; // Clear the interrupt 0 flag
    delay1s();
  return;
}
    

