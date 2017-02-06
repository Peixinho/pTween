//============================================================================
// Name        : pTween.h
// Author      : Duarte Peixinho
// Version     : 0.1
// Copyright   : ;) 
// Description : pTween
//============================================================================

#ifndef PTWEEN_H
#define	PTWEEN_H

#include <pTween/core/pTweenObject.h>
#include <pTween/core/pTweenEngine.h>
#include <pTween/core/pTweenTransitions.h>

typedef pTween::Engine::pTweenObject* pTweenObject;

namespace pTween {

	using namespace Engine;

	// Add new Tween
	inline pTweenObject* pTween(float* target)
	{
		return new pTweenObject(target);
	}

	// pTween Step
	inline void pTweenStep(const double &time)
	{
		pTweenEngine::Step(time);
	}

	// Pause All
	inline void pTweenPauseAllTweens()
	{
		pTweenEngine::PauseAll();
	}

	// Resume
	inline void pTweenResumeAllTweens()
	{
		pTweenEngine::ResumeAll();
	}

	// Remove All Tweens
	inline void pTweenDeleteAllTweens()
	{
		pTweenEngine::DeleteAll();
	}

	// Destroy Tween
	inline void Destroy(pTweenObject* pTobj)
	{
		pTweenEngine::Destroy(pTobj);
	}	
};

#endif /* PTWEEN_H */
