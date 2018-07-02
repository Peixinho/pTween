//============================================================================
// Name        : pTweenEquations.h
// Author      : Duarte Peixinho
// Version     : 0.1
// Copyright   : ;)
// Description : pTween Equations
//============================================================================

#ifndef PTWEENEQUATIONS_H
#define	PTWEENEQUATIONS_H

#define PI 3.14159265f

#include <math.h>
#include <iostream>

#include "pTweenTransitions.h"
#include "pTweenEngine.h"

namespace pTween {

    namespace Engine {

        class PTWEEN_API pTweenEquations {
        public:
            static float Equation(unsigned int Transition, double Time, float Init, float Change, float Duration)
            {
                float p = 0, a = 0, s;
                if (Change!=0)
                    switch (Transition)
                    {
                        case pTweenTransitions::Linear:
                                return Change * Time / Duration + Init;
                        break;
                        case pTweenTransitions::EaseInCubic:
                                return Change * powf(Time/Duration, 3.f) + Init;
                        break;
                        case pTweenTransitions::EaseOutCubic:
                                return Change * (powf(Time/Duration-1.f, 3.f) + 1.f) + Init;
                        break;
                        case pTweenTransitions::EaseInOutCubic:
                                if ((Time/=Duration/2.f) < 1.f)
                                        return Change/2.f * powf(Time, 3.f) + Init;
                                return Change/2 * (powf(Time-2.f, 3.f) + 2.f) + Init;
                        break;
                        case pTweenTransitions::EaseInQuart:
                                return Change * powf(Time/Duration, 4) + Init;
                        break;
                        case pTweenTransitions::EaseOutQuart:
                                return -Change * (powf(Time/Duration-1, 4) - 1) + Init;
                        break;
                        case pTweenTransitions::EaseInOutQuart:
                                if ((Time/=Duration/2) < 1)
                                        return Change/2 * powf(Time, 4) + Init;
                                return -Change/2 * (powf(Time-2, 4) - 2) + Init;
                        break;
                        case pTweenTransitions::EaseInQuint:
                                return Change * powf(Time/Duration, 5) + Init;
                        break;
                        case pTweenTransitions::EaseOutQuint:
                                return Change * (powf(Time/Duration-1, 5) + 1) + Init;
                        break;
                        case pTweenTransitions::EaseInOutQuint:
                                if ((Time/=Duration/2) < 1)
                                        return Change/2 * powf(Time, 5) + Init;
                                return Change / 2 * (powf(Time - 2, 5) + 2) + Init;
                        break;
                        case pTweenTransitions::EaseInSine:
                                return (float)(Change * (1 - cosf(Time/Duration * (PI/2))) + Init);
                        break;
                        case pTweenTransitions::EaseOutSine:
                                return (float)(Change * sinf(Time/Duration * (PI/2)) + Init);
                        break;
                        case pTweenTransitions::EaseInOutSine:
                                return (float)(Change/2 * (1 - cosf(PI*Time/Duration)) + Init);
                        break;
                        case pTweenTransitions::EaseInExpo:
                                return (float)(Change * powf(2, 10 * (Time/Duration - 1)) + Init);
                        break;
                        case pTweenTransitions::EaseOutExpo:
                                return (float)(Change * (-powf(2, -10 * Time/Duration) + 1) + Init);
                        break;
                        case pTweenTransitions::EaseInOutExpo:
                                if ((Time/=Duration/2) < 1)
                                        return (float)(Change/2 * powf(2, 10 * (Time - 1)) + Init);
                                return (float)(Change/2 * (-powf(2, -10 * --Time) + 2) + Init);
                        break;
                        case pTweenTransitions::EaseInCirc:
                                return (float)(Change * (1 - sqrt(1 - (Time/=Duration)*Time)) + Init);
                        break;
                        case pTweenTransitions::EaseOutCirc:
                                return (float)(Change * sqrt(1 - (Time=Time/Duration-1)*Time) + Init);
                        break;
                        case pTweenTransitions::EaseInOutCirc:
                                if ((Time/=Duration/2) < 1)
                                        return (float)(Change/2 * (1 - sqrt(1 - Time*Time)) + Init);
                                return(float)( Change/2 * (sqrt(1 - (Time-=2)*Time) + 1) + Init);
                        break;
                        case pTweenTransitions::EaseInBounce:
                                return (float)(Change - pTweenEquations::Equation(pTweenTransitions::EaseOutBounce, Duration-Time, 0, Change, Duration) + Init);
                        break;
                        case pTweenTransitions::EaseOutBounce:
                                if ((Time/=Duration) < (1/2.75)) {
                                        return (float)(Change*(7.5625*Time*Time) + Init);
                                } else if (Time < (2/2.75)) {
                                        return (float)(Change*(7.5625*(Time-=(1.5f/2.75f))*Time + .75f) + Init);
                                } else if (Time < (2.5/2.75)) {
                                        return (float)(Change*(7.5625*(Time-=(2.25f/2.75f))*Time + .9375f) + Init);
                                } else {
                                        return (float)(Change*(7.5625*(Time-=(2.625f/2.75f))*Time + .984375f) + Init);
                                }
                        break;
                        case pTweenTransitions::EaseInOutBounce:
                                if (Time < Duration/2) return (float)(pTweenEquations::Equation(pTweenTransitions::EaseInBounce,Time*2, 0, Change, Duration) * .5 + Init);
                                else return (float)(pTweenEquations::Equation(pTweenTransitions::EaseOutBounce,Time*2-Duration, 0, Change, Duration) * .5 + Change*.5 + Init);
                        break;
                        case pTweenTransitions::EaseInElastic:
                                if (Time==0) return (float)Init;  if ((Time/=Duration)==1) return (float)(Init+Change);  if (!p) p=Duration*.3f;
                                if (!a || a < fabs(Change)) { a=Change; s=p/4; }
                                else s = p/(2*PI) * asinf(Change/a);
                                return -(a*powf(2.f,10.f*(Time-=1)) * sinf( (Time*Duration-s)*(2*PI)/p )) + Init;
                        break;
                        case pTweenTransitions::EaseOutElastic:
                                if (Time==0) return Init;  if ((Time/=Duration)==1) return Init+Change;  if (!p) p=Duration*.3f;
                                if (a < fabs(Change)) { a=Change; s=p/4; }
                                else s = p/(2*PI) * asinf(Change/a);
                                return a*powf(2.f,-10.f*Time) * sinf( (Time*Duration-s)*(2*PI)/p ) + Change + Init;
                        break;
                        case pTweenTransitions::EaseInOutElastic:
                                if (Time==0) return Init;  if ((Time/=Duration/2)==2) return Init+Change;  if (!p) p=Duration*(.3f*1.5f);
                                if (a < fabs(Change)) { a=Change; s=p/4; }
                                else s = p/(2*PI) * asinf(Change/a);
                                if (Time < 1) return -.5f*(a*powf(2.f,10.f*(Time-=1)) * sin( (Time*Duration-s)*(2*PI)/p )) + Init;
                                return a*powf(2.f,-10.f*(Time-=1)) * sinf( (Time*Duration-s)*(2*PI)/p )*.5f + Change + Init;
                        break;
                        case pTweenTransitions::EaseInBack:
                                s = 1.70158f;
                                return Change*(Time/=Duration)*Time*((s+1)*Time - s) + Init;
                        break;
                        case pTweenTransitions::EaseOutBack:
                                s = 1.70158f;
                                return Change*((Time=Time/Duration-1)*Time*((s+1)*Time + s) + 1) + Init;
                        break;
                        case pTweenTransitions::EaseInOutBack:
                                s = 1.70158f;
                                if ((Time/=Duration/2) < 1) return Change/2*(Time*Time*(((s*=(1.525f))+1)*Time - s)) + Init;
                                return Change/2*((Time-=2)*Time*(((s*=(1.525f))+1)*Time + s) + 2) + Init;
                        break;
                }
                return Init;

            }

        };
    }

}

#endif	/* PTWEENEQUATIONS_H */
