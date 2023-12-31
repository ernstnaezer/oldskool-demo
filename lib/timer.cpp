#include <stdint.h>
#include <dos.h>
#include <conio.h>

/**
 * For some reason the timer included in the USM player crashes the application 
 * with a Stack Overflow. I can't be bothered to debug that at this point in time.
 * 
 * Make sure to initialize the timer _before_ the music player, as the player samples 
 * the clock speed to determine the correct playback speed. 
 *
 * If you start timer afterwards, you'll have some really slow and low pitched playback.
 */

#define PIT_CTRL 0x43
#define PIT_COUNTER0 0x40
#define PIT_FREQUENCY 1193182L

void interrupt (*oldTimerISR)(void); // Pointer to store the old ISR

volatile unsigned long Timer = 0;

void interrupt timerISR(void) {
    Timer++; 

    // Acknowledge the interrupt to the PIC so that it can raise more interrupts
    outp(0x20, 0x20);
}

void timer_init(unsigned hz){
    unsigned divisor = (unsigned)(PIT_FREQUENCY / hz);

    _disable();

    // Save the old timer ISR
    oldTimerISR = _dos_getvect(0x08);

    _dos_setvect(0x08, timerISR);

    // Program the PIT to the desired frequency
    outp(PIT_CTRL, 0x36);                 // Set control word for Counter 0
    outp(PIT_COUNTER0, divisor & 0xFF);   // Set low byte of divisor
    outp(PIT_COUNTER0, divisor >> 8);     // Set high byte of divisor

    _enable();
}

void timer_release(){
    _disable();

    // Restore the old timer ISR
    _dos_setvect(0x08, oldTimerISR);

    // Restore the original PIT frequency (about 18.2 Hz)
    outp(PIT_CTRL, 0x36);
    outp(PIT_COUNTER0, 0);
    outp(PIT_COUNTER0, 0);

    _enable();
}
