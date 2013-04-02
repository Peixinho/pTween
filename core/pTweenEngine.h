//============================================================================
// Name        : pTweenEngine.h
// Author      : Duarte Peixinho
// Version     : 0.1
// Copyright   : ;) 
// Description : pTween Engine
//============================================================================

#ifndef PTWEENENGINE_H
#define	PTWEENENGINE_H

#include "pTweenOBJ.h"

#include <map>
#include <vector>

namespace pTween {

    namespace Engine {

        class pTweenEngine {

            public:

                pTweenEngine() {}

                pTweenEngine &Init(void* OBJ, bool useFrames = false);

                // Params
                pTweenEngine &Duration(const float &t);
                pTweenEngine &Transition(const unsigned int &transition);
                pTweenEngine &AddParam(float* param, const float &endValue);
                pTweenEngine &AddParam(float* param, const float &initValue, const float &endValue);
                pTweenEngine &UpdateTween(void* OBJ);
                pTweenEngine &Delay(const float &t);

                            // Events
                pTweenEngine &OnStartFunction(void (*func)(void));
                pTweenEngine &OnUpdateFunction(void (*func)(void));
                pTweenEngine &OnCompleteFunction(void (*func)(void));

                // Engine Methods
                static void Step(const float &Time);
                static void UpdateTweens();

                // Pause, Resume and Remove
                static void PauseTween(void* OBJ);
                static void ResumeTween(void* OBJ);
                static void PauseAllTweens();
                static void ResumeAllTweens();
                static void Remove(void* OBJ);
                static void RemoveAll();
                static unsigned int Search(void* OBJ);

                virtual ~pTweenEngine();

            private:

                // internal time
                static float _time;
                static float _frames;

                // internal counter
                static unsigned int _counter;
                // saves the pTweenObject in use
                static unsigned int _pTobjInUse;

                // pTweenObjects List
                static std::map<unsigned int ,pTweenOBJ> _pTweenOBJS;
        };
    }
}

#endif	/* PTWEENENGINE_H */
