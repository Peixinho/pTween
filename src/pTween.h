//============================================================================
// Name        : pTween.h
// Author      : Duarte Peixinho
// Version     : 0.1
// Copyright   : ;) 
// Description : pTween
//============================================================================

#ifndef PTWEEN_H
#define	PTWEEN_H

#include "core\pTweenObject.h"
#include "core\pTweenEngine.h"
#include "core\pTweenTransitions.h"

typedef pTween::Engine::pTweenObject* pTweenObject;

namespace pTween {

	using namespace Engine;

	// Add new Tween
	pTweenObject* pTween(float* target)
	{
		return new pTweenObject(target);
	}

	// pTween Step
	void pTweenStep(const float &time)
	{
		pTweenEngine::Step(time);
	}

	// Pause All
	void pTweenPauseAllTweens()
	{
		pTweenEngine::PauseAll();
	}

	// Resume
	void pTweenResumeAllTweens()
	{
		pTweenEngine::ResumeAll();
	}

	// Remove All Tweens
	void pTweenDeleteAllTweens()
	{
		pTweenEngine::DeleteAll();
	}
};

#endif /* PTWEEN_H */