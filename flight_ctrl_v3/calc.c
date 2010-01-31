#include <avr/io.h>
#include <avr/pgmspace.h>
#include <math.h>

#include "calc.h"

#include "config.h"
#include "pindef.h"
#include "macros.h"

/*
// function which performs fixed point multiplication, has been replaced with a macro
inline signed long calc_multi(signed long in, signed long numer, signed long denom)
{
	if(denom == 0)
	{
		if(in * numer > 0)
		{
			return INT32_MAX;
		}
		else if(in * numer < 0)
		{
			return INT32_MIN;
		}
		else
		{
			return 0;
		}
	}
	
	signed long r = (in * numer) + (denom / 2);
	return r / denom;
}
*/

#include "trig_tbl.h"

#ifdef use_asin

inline signed long calc_asin(signed long opp, signed long hyp)
{
	// calculate arcsine angle using opposite length and hypotenus length
	// using look up table with the division of opp/hyp as the address
	signed long addr = calc_multi(opp, asin_multiplier, hyp);
	signed long r = pgm_read_dword(&(asin_tbl[calc_abs(addr)]));
	if(addr < 0)
	{
		return -r;
	}
	else
	{
		return r;
	}
	// note that angle is returned in the form stored in the lookup table
}

#endif


#ifdef use_atan

inline signed long calc_atan2(signed long y, signed long x)
{
	// calculate arctan angle using opposite length and adjacent length
	// using look up table with the division of opp/adj as the address
	
	signed long z = 0;
	if(calc_abs(x) > calc_abs(y))
	{
		z = calc_multi(y, atan_multiplier, x);
	}
	else if(calc_abs(x) < calc_abs(y))
	{
		z = calc_multi(x, atan_multiplier, y);
	}
	else if(x == 0 && y == 0)
	{
		return 0;
	}
	else if(x == y)
	{
		z = atan_multiplier;
	}

	signed long r_ = pgm_read_dword(&(atan_tbl[calc_abs(z)]));
	signed long _r = r_;
	signed long r;

	if(calc_abs(x) < calc_abs(y))
	{
		_r = (90 * MATH_MULTIPLIER) - r_;
	}

	if(x >= 0)
	{
		if(y < 0)
		{
			_r *= -1;
		}
		r = _r;
	}
	else
	{
		if(y >= 0)
		{
			r = (180 * MATH_MULTIPLIER) - _r;
		}
		else
		{
			r = (-180 * MATH_MULTIPLIER) + _r;
		}
	}

	return r;
	// note that angle is returned in degrees
}

#endif

inline signed long PID_mv(PID_data * pid, PID_const k, signed long current, signed long target)
{
	// proportional, integral, derivative
	// refer to external resources to learn more about this functioln
	
	signed long err = target - current;

	pid->err_sum = calc_constrain(pid->err_sum + err, -1000000, 1000000);

	signed long delta_err = err - pid->err_last;

	signed long mv = err * k.p + pid->err_sum * k.i + delta_err * k.d;

	pid->err_last = err;

	return calc_multi(mv, 1, MATH_MULTIPLIER);
}

inline PID_data PID_init()
{
	// create a PID persistent data structure and reset its values
	PID_data r;
	r.err_sum = 0;
	r.err_last = 0;
	return r;
}

#ifdef use_comp_filter

inline signed long complementary_filter(signed long * ang, signed long accel_ang, signed long gyro_r, signed long w, signed long dt)
{
	signed long g = calc_multi(gyro_r, dt, MATH_MULTIPLIER);
	*ang = calc_multi
			(
				(MATH_MULTIPLIER - w),
				(*ang + g),
				MATH_MULTIPLIER
			) + calc_multi(w, accel_ang, MATH_MULTIPLIER);
	return *ang;
}

#endif

#ifdef use_kalman_filter

inline double kalman_filter(kalman_data * kd, double gyro_r, double ang, double dt)
{
	// using kalman filtering to calculate angle
	// all double precision calculation, very very slow
	
	kd->x[0] += dt * (gyro_r - kd->x[1]);
	kd->P[0] += (-dt * (kd->P[2] + kd->P[1])) + (dt * kd->Q[0]);
	kd->P[1] -= dt * kd->P[3];
	kd->P[2] -= dt * kd->P[3];
	kd->P[3] += dt * kd->Q[1];

	double y = ang - kd->x[0];
	double S = kd->P[0] + kd->R;
	double K[2] = {kd->P[0] / S, kd->P[2] / S};

	kd->x[0] += K[0] * y;
	kd->x[1] += K[1] * y;

	kd->P[0] -= K[0] * kd->P[0];
	kd->P[1] -= K[0] * kd->P[1];
	kd->P[2] -= K[1] * kd->P[0];
	kd->P[3] -= K[1] * kd->P[1];

	return kd->x[0];
}

void kalman_init(kalman_data * kd, double Q_accel, double Q_gyro, double R_accel)
{
	// initialize a kalman matrix
	
	kd->x[0] = 0;
	kd->x[1] = 0;

	kd->P[0] = 0;
	kd->P[1] = 0;
	kd->P[2] = 0;
	kd->P[3] = 0;

	kd->Q[0] = Q_accel;
	kd->Q[1] = Q_gyro;
	kd->R = R_accel;
}

#endif