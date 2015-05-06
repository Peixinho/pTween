//============================================================================
// Name        : pTweenEngine.cpp
// Author      : Duarte Peixinho
// Version     : 0.1
// Copyright   : ;) 
// Description : pTween Engine
//============================================================================

#include <pTween/core/pTweenEngine.h>
#include <pTween/core/pTweenEquations.h>

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

		void pTweenEngine::Destroy(pTweenObject* pTobj)
		{
			for (std::list<pTweenObject*>::iterator i=_pTweenObjects.begin();i!=_pTweenObjects.end();i++)
			{
				if ((*i)==pTobj)
				{
					(*i)->Dispose();
					// Remove from List
					i = _pTweenObjects.erase(i);
				}
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

					// CallBack
					if (pTobj->_HasStartCallBackOBJ) pTobj->_OnStartOBJ();
					if (pTobj->_HasStartCallBack) pTobj->_OnStart();

					if (!pTobj->_InitValueSet) 
					{
						pTobj->_InitValue = *pTobj->_Data;
						pTobj->_InitValueSet = true;
					}

					// Fixing Small Numbers Issue
						
					// Get Smaller Input Value
					float small = pTobj->_InitValue;
					if (fabs(pTobj->_InitValue) > fabs(pTobj->_EndValue))
					{
						if (pTobj->_EndValue!=0.0)
							small = pTobj->_EndValue;
					}
					if (small!=0.f) // Getting Decimal Factor
						while(fabs(small*pTobj->_decim)<1.f)
						{
							pTobj->_decim*=10;
						}

					while(pTobj->_Duration*pTobj->_decimTime<1.f)
					{
						pTobj->_decimTime*=10;
					}
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
					if (!pTobj->_IsPaused)
					{
						if (Timer>pTobj->_StartTime && Timer<pTobj->_EndTime+pTobj->_PauseTime)
						{
							// Tween
							*pTobj->_Data = 
							(pTweenEquations::Equation(
								pTobj->_Transition,
								Timer*pTobj->_decimTime - (pTobj->_StartTime-pTobj->_PauseTime)*pTobj->_decimTime,
								pTobj->_InitValue*pTobj->_decim,
								(pTobj->_EndValue*pTobj->_decim)-(pTobj->_InitValue*pTobj->_decim),
								pTobj->_Duration*pTobj->_decimTime)/pTobj->_decim);
							
							// CallBack
							if (pTobj->_HasUpdateCallBackOBJ) pTobj->_OnUpdateOBJ();
							if (pTobj->_HasUpdateCallBack) pTobj->_OnUpdate();

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
								pTobj->_HasStartCallBackOBJ = false;
								pTobj->_HasStartCallBack = false;
							}
							else {

								// Set End Value
								*pTobj->_Data = pTobj->_EndValue;
								
								// End CallBack
								if (pTobj->_HasEndCallBackOBJ) pTobj->_OnEndOBJ();
								if (pTobj->_HasEndCallBack) pTobj->_OnEnd();

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