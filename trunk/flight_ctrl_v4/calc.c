#include <stdint.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <math.h>

#include "config.h"
#include "pindef.h"
#include "macros.h"

#include "calc.h"

#ifdef use_multiplication_funct

volatile inline int32_t calc_multi(volatile int32_t input, volatile int32_t numer, volatile int32_t denom)
{
	return calc_multi_funct(input, numer, denom);
}

#endif

// function which performs fixed point multiplication, has been replaced with a macro
volatile inline int32_t calc_multi_funct(volatile int32_t input, volatile int32_t numer, volatile int32_t denom)
{	
	volatile int32_t r = (input * numer);
	r += (denom / 2);
	return r / denom;
}

volatile inline int32_t PID_mv(PID_data * pid, int32_t kp, int32_t ki, int32_t kd, int32_t current, int32_t target)
{
        // proportional, integral, derivative
        // refer to external resources to learn more about this functioln
        
		volatile int32_t mm = MATH_MULTIPLIER;
		
        int32_t err = target - current;

		int32_t mv = err * kp;
		
		if (ki != 0)
		{
			pid->err_sum = calc_constrain(pid->err_sum + err, INT64_MIN / 2, INT64_MAX / 2);
			mv += pid->err_sum * ki;
		}

		if (kd != 0)
		{
			int32_t delta_err = err - pid->err_last;
			mv += delta_err * kd;
			pid->err_last = err;
		}
		
		mv += mm / 2;
		mv /= mm;
		return mv;
}

inline PID_data PID_init()
{
        // create a PID persistent data structure and reset its values
        PID_data r;
        r.err_sum = 0;
        r.err_last = 0;
        return r;
}

volatile inline int32_t calc_filter(int32_t oldval, int32_t newval, int32_t weight)
{
	volatile int32_t mm = MATH_MULTIPLIER;
	volatile int32_t result = oldval * (mm - weight);
	result += (newval * weight) + (weight / 2);
	result /= mm;
	return result;
}