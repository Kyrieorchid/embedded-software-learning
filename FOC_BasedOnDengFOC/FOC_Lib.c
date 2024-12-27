#include <math.h>
#include "FOC_Lib.h"

void setPwm(float Ua, float Ub, float Uc)
{
    Ua = _constrain(Ua, 0.0f, voltage_limit);
    Ub = _constrain(Ub, 0.0f, voltage_limit);
    Uc = _constrain(Uc, 0.0f, voltage_limit);

    dc_a = _constrain(dc_a, 0.0f, 1.0f);
    dc_b = _constrain(dc_b, 0.0f, 1.0f);
    dc_c = _constrain(dc_c, 0.0f, 1.0f);

    /*set PWM channel duty cycle

            CODE HERE
    
    set PWM channel duty cycle*/
}

void setPhaseVoltage(float Uq, float Ud, float angle_el)
{
    angle_el = _normalizeAngle(angle_el + zero_electric_angle);

    // Inv_Park_trans 
    Ualpha = -Uq * sin(angle_el);
    Ubeta = Uq * cos(angle_el);

    // Inv_Clark_trans
    Ua = Ualpha + voltage_power_supply / 2;
    Ub = (sqrt(3) * Ubeta - Ualpha + voltage_power_supply) / 2;
    Uc = (-Ualpha - sqrt(3) * Ubeta + voltage_power_supply) / 2;
    setPwm(Ua, Ub, Uc);
}

float velocityOpenLoop(float target_velocity)
{
    
}



