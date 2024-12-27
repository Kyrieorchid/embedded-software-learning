#ifndef _FOC_LIB_H
#define _FOC_LIB_H

#define voltage_limit 10
#define _constrain((x), (low_limit), (high_limit)) ((x) < (low_limit) ? (low_limit) : ((x) > (high_limit) ? (high_limit) : (x)))

float Ualpha, Ubeta;
float Ua, Ub, Uc;
float dc_a, dc_b, dc_c;
float voltage_power_supply = 12;

#endif
