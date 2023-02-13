#ifndef CPU_CONFIG_H_
#define CPU_CONFIG_H_


#undef F_CPU // disable internal CPU freq
#define F_CPU 16000000 // enable external CPU freq
#define BITS 256

#include <avr/io.h>
#include <util/delay.h>
#include "BitMath.h"
#include "PWM_Private.h"


#endif /* CPU_CONFIG_H_ */
