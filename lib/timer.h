#ifndef __TIMER_H__
#define __TIMER_H__

extern volatile unsigned long Timer; 
void timer_init(unsigned hz);
void timer_release();

#endif