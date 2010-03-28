#ifndef calc_h
#define calc_h

#include <stdint.h>

#define rad_to_deg_const 57.2957795130823

#define calc_abs(in) 				(in < 0 ? -1 * in : in)
#define calc_sign(in) 				(in < 0 ? -1 : 1)
#define calc_map_long(in,old_min,old_max,new_min,new_max) (new_min + calc_multi(in - old_min, new_max - new_min, old_max - old_min))
#define calc_max(a,b) 				(a > b ? a : b)
#define calc_min(a,b) 				(a < b ? a : b)
#define calc_ang_range(ang) 		(ang > (180 * MATH_MULTIPLIER) ? ((-180 * MATH_MULTIPLIER) + ang - (180 * MATH_MULTIPLIER)) : (ang < (-180 * MATH_MULTIPLIER) ? ((180 * MATH_MULTIPLIER) + ang - (-180 * MATH_MULTIPLIER)) : ang))
#define calc_constrain(in,min,max) 	(in < min ? min : (in > max ? max : in))

#ifndef use_multiplication_funct
#define calc_multi(input,numer,denom) 	((input*numer)+(denom/2))/denom
#endif

typedef struct PID_data_
{
	int32_t err_sum;
	int32_t err_last;
} PID_data;

typedef struct kalman_data_
{
	int32_t x[2];
	int32_t P[4];
	int32_t Q[2];
	int32_t R;
} kalman_data;

#ifdef use_multiplication_funct
volatile int32_t calc_multi(volatile int32_t, volatile int32_t, volatile int32_t);
#endif
volatile int32_t PID_mv(PID_data *, int32_t, int32_t, int32_t, int32_t, int32_t);
PID_data PID_init();
volatile int32_t complementary_filter(int32_t *, int32_t, int32_t, int32_t, int32_t);
volatile double kalman_filter(kalman_data *, double, double, double);
volatile int32_t calc_atan2(int32_t, int32_t);
volatile int32_t calc_asin(int32_t, int32_t);
void kalman_init(kalman_data *, double, double, double);

#endif