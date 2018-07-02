//============================================================================
// Name        : pTweenTransitions.h
// Author      : Duarte Peixinho
// Version     : 0.1
// Copyright   : ;)
// Description : pTween Transitions
//============================================================================


#ifndef PTWEENTRANSITIONS_H
#define	PTWEENTRANSITIONS_H

namespace pTween {

    namespace Engine {

        namespace pTweenTransitions
        {
            enum
            {
                Linear = 0,
                EaseInCubic,
                EaseOutCubic,
                EaseInOutCubic,
                EaseInQuart,
                EaseOutQuart,
                EaseInOutQuart,
                EaseInQuint,
                EaseOutQuint,
                EaseInOutQuint,
                EaseInSine,
                EaseOutSine,
                EaseInOutSine,
                EaseInCirc,
                EaseOutCirc,
                EaseInOutCirc,
                EaseInExpo,
                EaseOutExpo,
                EaseInOutExpo,
                EaseInBounce,
                EaseOutBounce,
                EaseInOutBounce,
                EaseInElastic,
                EaseOutElastic,
                EaseInOutElastic,
                EaseInBack,
                EaseOutBack,
                EaseInOutBack
            };
        }
    }
}

#endif	/* PTWEENTRANSITIONS_H */

