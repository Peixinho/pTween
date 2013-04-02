//============================================================================
// Name        : pTweenEquations.h
// Author      : Duarte Peixinho
// Version     : 0.1
// Copyright   : ;) 
// Description : pTween Equations
//============================================================================

#ifndef PTWEENEQUATIONS_H
#define	PTWEENEQUATIONS_H

#define PI 3.14159265

#include <math.h>
#include <iostream>

#include "pTweenTransitions.h"

namespace pTween {

    namespace Engine {
    
        class pTweenEquations {
        public:
            static float Equation(unsigned int Transition, float Time, int Init, float Change, float Duration)
            {

                float p = 0, a = 0, s;
                if (Change!=0)
                    switch (Transition)
                    {
                        case pTweenTransitions::Linear:
                                return Change * Time / Duration + Init;
                        break;
                        case pTweenTransitions::EaseInCubic:
                                return Change * pow (Time/Duration, 3) + Init;
                        break;
                        case pTweenTransitions::EaseOutCubic:
                                return Change * (pow (Time/Duration-1, 3) + 1) + Init;
                        break;
                        case pTweenTransitions::EaseInOutCubic:
                                if ((Time/=Duration/2) < 1)
                                        return Change/2 * pow (Time, 3) + Init;
                                return Change/2 * (pow (Time-2, 3) + 2) + Init;
                        break;
                        case pTweenTransitions::EaseInQuart:
                                return Change * pow (Time/Duration, 4) + Init;
                        break;
                        case pTweenTransitions::EaseOutQuart:
                                return -Change * (pow (Time/Duration-1, 4) - 1) + Init;
                        break;
                        case pTweenTransitions::EaseInOutQuart:
                                if ((Time/=Duration/2) < 1)
                                        return Change/2 * pow (Time, 4) + Init;
                                return -Change/2 * (pow (Time-2, 4) - 2) + Init;
                        break;
                        case pTweenTransitions::EaseInQuint:
                                return Change * pow (Time/Duration, 5) + Init;
                        break;
                        case pTweenTransitions::EaseOutQuint:
                                return Change * (pow (Time/Duration-1, 5) + 1) + Init;
                        break;
                        case pTweenTransitions::EaseInOutQuint:
                                if ((Time/=Duration/2) < 1)
                                        return Change/2 * pow (Time, 5) + Init;
                                return Change / 2 * (pow (Time - 2, 5) + 2) + Init;
                        break;
                        case pTweenTransitions::EaseInSine:
                                return Change * (1 - cos(Time/Duration * (PI/2))) + Init;
                        break;
                        case pTweenTransitions::EaseOutSine:
                                return Change * sin(Time/Duration * (PI/2)) + Init;
                        break;
                        case pTweenTransitions::EaseInOutSine:
                                return Change/2 * (1 - cos(PI*Time/Duration)) + Init;
                        break;
                        case pTweenTransitions::EaseInExpo:
                                return Change * pow(2, 10 * (Time/Duration - 1)) + Init;
                        break;
                        case pTweenTransitions::EaseOutExpo:
                                return Change * (-pow(2, -10 * Time/Duration) + 1) + Init;
                        break;
                        case pTweenTransitions::EaseInOutExpo:
                                if ((Time/=Duration/2) < 1)
                                        return Change/2 * pow(2, 10 * (Time - 1)) + Init;
                                return Change/2 * (-pow(2, -10 * --Time) + 2) + Init;
                        break;
                        case pTweenTransitions::EaseInCirc:
                                return Change * (1 - sqrt(1 - (Time/=Duration)*Time)) + Init;
                        break;
                        case pTweenTransitions::EaseOutCirc:
                                return Change * sqrt(1 - (Time=Time/Duration-1)*Time) + Init;
                        break;
                        case pTweenTransitions::EaseInOutCirc:
                                if ((Time/=Duration/2) < 1)
                                        return Change/2 * (1 - sqrt(1 - Time*Time)) + Init;
                                return Change/2 * (sqrt(1 - (Time-=2)*Time) + 1) + Init;
                        break;
                        case pTweenTransitions::EaseInBounce:
                                return Change - pTweenEquations::Equation(pTweenTransitions::EaseOutBounce, Duration-Time, 0, Change, Duration) + Init;
                        break;
                        case pTweenTransitions::EaseOutBounce:
                                if ((Time/=Duration) < (1/2.75)) {
                                        return Change*(7.5625*Time*Time) + Init;
                                } else if (Time < (2/2.75)) {
                                        return Change*(7.5625*(Time-=(1.5/2.75))*Time + .75) + Init;
                                } else if (Time < (2.5/2.75)) {
                                        return Change*(7.5625*(Time-=(2.25/2.75))*Time + .9375) + Init;
                                } else {
                                        return Change*(7.5625*(Time-=(2.625/2.75))*Time + .984375) + Init;
                                }
                        break;
                        case pTweenTransitions::EaseInOutBounce:
                                if (Time < Duration/2) return pTweenEquations::Equation(pTweenTransitions::EaseInBounce,Time*2, 0, Change, Duration) * .5 + Init;
                                else return pTweenEquations::Equation(pTweenTransitions::EaseOutBounce,Time*2-Duration, 0, Change, Duration) * .5 + Change*.5 + Init;
                        break;
                        case pTweenTransitions::EaseInElastic:
                                if (Time==0) return Init;  if ((Time/=Duration)==1) return Init+Change;  if (!p) p=Duration*.3;
                                if (!a || a < fabs(Change)) { a=Change; s=p/4; }
                                else s = p/(2*PI) * asin (Change/a);
                                return -(a*pow(2,10*(Time-=1)) * sin( (Time*Duration-s)*(2*PI)/p )) + Init;
                        break;
                        case pTweenTransitions::EaseOutElastic:
                                if (Time==0) return Init;  if ((Time/=Duration)==1) return Init+Change;  if (!p) p=Duration*.3;
                                if (a < fabs(Change)) { a=Change; s=p/4; }
                                else s = p/(2*PI) * asin (Change/a);
                                return a*pow(2,-10*Time) * sin( (Time*Duration-s)*(2*PI)/p ) + Change + Init;
                        break;
                        case pTweenTransitions::EaseInOutElastic:
                                if (Time==0) return Init;  if ((Time/=Duration/2)==2) return Init+Change;  if (!p) p=Duration*(.3*1.5);
                                if (a < fabs(Change)) { a=Change; s=p/4; }
                                else s = p/(2*PI) * asin (Change/a);
                                if (Time < 1) return -.5*(a*pow(2,10*(Time-=1)) * sin( (Time*Duration-s)*(2*PI)/p )) + Init;
                                return a*pow(2,-10*(Time-=1)) * sin( (Time*Duration-s)*(2*PI)/p )*.5 + Change + Init;
                        break;
                        case pTweenTransitions::EaseInBack:
                                s = 1.70158;
                                return Change*(Time/=Duration)*Time*((s+1)*Time - s) + Init;
                        break;
                        case pTweenTransitions::EaseOutBack:
                                s = 1.70158;
                                return Change*((Time=Time/Duration-1)*Time*((s+1)*Time + s) + 1) + Init;
                        break;
                        case pTweenTransitions::EaseInOutBack:
                                s = 1.70158;
                                if ((Time/=Duration/2) < 1) return Change/2*(Time*Time*(((s*=(1.525))+1)*Time - s)) + Init;
                                return Change/2*((Time-=2)*Time*(((s*=(1.525))+1)*Time + s) + 2) + Init;
                        break;
                }
                return Init;

            }

        };
    }

}

#endif	/* PTWEENEQUATIONS_H */
