#ifndef calibration_h
#define calibration_h

#include "calibration_struct.h"

void calibration_default(Calibration *);
void calibration_save(Calibration *);
void calibration_load(Calibration *);
void calibration_write(Calibration *, signed long, signed long);

#endif