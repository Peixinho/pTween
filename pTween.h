//============================================================================
// Name        : pTween.h
// Author      : Duarte Peixinho
// Version     : 0.1
// Copyright   : ;) 
// Description : pTween Engine
//============================================================================

#ifndef PTWEEN_H
#define	PTWEEN_H

#include "core/pTweenEngine.h"
#include "core/pTweenTransitions.h"

namespace pTween {
    
    using namespace Engine;

    static pTweenEngine* pTengine;
    static bool _Initialized=false;

    pTweenEngine pTween(void* OBJ, bool useFrames = false)
    {
        // Singleton
        if (_Initialized==false) {
                pTengine = new pTweenEngine();
        }
        pTweenEngine pT = pTengine->Init(OBJ, useFrames);
        return pT;
    }
    pTweenEngine UpdatepTween(void* OBJ)
    {
        pTweenEngine pT;
        pT = pTengine->UpdateTween(OBJ);
        return pT;
    }
    void pTweenDestroy()
    {
        delete pTengine;
        _Initialized = false;
    }
    void pTweenStep(const float &Time)
    {
        pTweenEngine::Step(Time);
    }
    void PauseAllTweens() 
    {
        pTweenEngine::PauseAllTweens();
    }
    void ResumeAllTweens()
    {
        pTweenEngine::ResumeAllTweens();
    }
    void PauseTween(void* OBJ)
    {
        pTweenEngine::PauseTween(OBJ);
    }
    void ResumeTween(void* OBJ)
    {
        pTweenEngine::ResumeTween(OBJ);
    }
    void Remove(void* OBJ)
    {
        pTweenEngine::Remove(OBJ);
    }
    void RemoveAll()
    {
        pTweenEngine::RemoveAll();
    }

}

#endif	/* PTWEEN_H */
