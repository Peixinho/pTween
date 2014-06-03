//============================================================================
// Name        : pTweenEngine.cpp
// Author      : Duarte Peixinho
// Version     : 0.1
// Copyright   : ;) 
// Description : pTween Engine
//============================================================================

#include "pTweenEngine.h"
#include "pTweenEquations.h"

namespace pTween {

	namespace Engine {
				
		// List of Tween Objects		
		std::list<pTweenObject*> pTweenEngine::_pTweenObjects; 
		float pTweenEngine::Timer;

		void pTweenEngine::PauseAll()
		{
			for (std::list<pTweenObject*>::iterator i=_pTweenObjects.begin();i!=_pTweenObjects.end();i++)
			{
				(*i)->Pause();
			}
		}

		void pTweenEngine::ResumeAll()
		{
			for (std::list<pTweenObject*>::iterator i=_pTweenObjects.begin();i!=_pTweenObjects.end();i++)
			{
				(*i)->Resume();
			}
		}

		void pTweenEngine::DeleteAll()
		{
			for (std::list<pTweenObject*>::iterator i=_pTweenObjects.begin();i!=_pTweenObjects.end();i++)
			{
				(*i)->Dispose();
				// Remove from List
				i = _pTweenObjects.erase(i);
				if (i==_pTweenObjects.end()) break;
			}
		}

		void pTweenEngine::Step(const float &Time)
		{
			// Save Time
			Timer = Time;

			for (std::list<pTweenObject*>::iterator i=_pTweenObjects.begin();i!=_pTweenObjects.end();i++)
			{
				pTweenObject* pTobj = (*i);

				// First Run
				if (!pTobj->_IsPlaying && pTobj->_StartPlaying)
				{
					pTobj->_StartTime = Timer + pTobj->_Delay;
					pTobj->_EndTime = pTobj->_StartTime + pTobj->_Duration;
					pTobj->_IsPlaying = true;
				}

				// Update Tween
				if (pTobj->_IsPlaying)
				{
					// Pause
					if (pTobj->_Pause && !pTobj->_IsPaused)
					{
						// Keep Start Pause Time
						pTobj->_PauseStartTime = Timer;
						pTobj->_IsPaused = true;
					}

					// Resume from Pause
					if (!pTobj->_Pause && pTobj->_IsPaused)
					{
						pTobj->_PauseTime += Timer - pTobj->_PauseStartTime;
						pTobj->_PauseStartTime = 0;
						pTobj->_IsPaused = false;
					}

					// Tween if still in time
					if (pTobj->_IsPaused)
					{
					
					} else {
						if (Timer>pTobj->_StartTime && Timer<pTobj->_EndTime+pTobj->_PauseTime)
						{
							// Tween
							*pTobj->_Data = pTweenEquations::Equation(pTobj->_Transition,Timer-(pTobj->_StartTime+pTobj->_PauseTime),pTobj->_InitValue,pTobj->_EndValue-pTobj->_InitValue,pTobj->_Duration);
						} else if (Timer>pTobj->_EndTime+pTobj->_PauseTime)
						{
							if (pTobj->_YoYo)
							{
								// Set new Tween
								pTobj->_InitValue=pTobj->__EndValue;
								pTobj->_EndValue=pTobj->__InitValue;
								pTobj->_Delay = 0;
								pTobj->_PauseTime = 0;
								pTobj->_IsPlaying = false;
								pTobj->_StartPlaying = true;
								pTobj->_YoYo = false;
							}
							else {

								// Play Chain Tween
								if (pTobj->_HasChain) pTobj->_ChainTween->Play();
								// Delete Tween
								else pTobj->Dispose();
								// Remove from List
								i = _pTweenObjects.erase(i);
								if (i==_pTweenObjects.end()) break;
							}
						}
					}
				}
			}
		}
	};
};