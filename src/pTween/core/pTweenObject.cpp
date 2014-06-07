//============================================================================
// Name        : pTweenObject.cpp
// Author      : Duarte Peixinho
// Version     : 0.1
// Copyright   : ;) 
// Description : pTween Object
//============================================================================

#include "pTweenObject.h"

namespace pTween {

	namespace Engine {

		// Constructor
		pTweenObject::pTweenObject(float* &target)
		{
			// Target
			_Data					= target;

			// Default Values
			_StartPlaying 			= false;
			_Pause 					= false;
			_IsPlaying				= false;
			_IsPaused				= false;
			_PauseTime				= 0;
			_PauseStartTime			= 0;
			_Transition				= 0; // Default Transition is Linear
			_InitValue				= 0;
			_InitValueSet			= false;
			_Delay					= 0;
			_YoYo					= false;
			_HasChain				= false;
			_ChainTween				= NULL;
			_HasParent				= false;
			_ChainParent			= NULL;
			_HasStartCallBack		= false;
			_HasUpdateCallBack		= false;
			_HasEndCallBack			= false;
			_HasStartCallBackOBJ	= false;
			_HasUpdateCallBackOBJ	= false;
			_HasEndCallBackOBJ		= false;
			__Delay					= 0;
			__YoYo					= 0;
			__InitValue				= *(float*)_Data;
		}

		// Initial Value
		pTweenObject* pTweenObject::From(const float &initValue)
		{
			_InitValue = __InitValue = initValue;
			_InitValueSet = true;
			return this;
		}
		
		// Final Value
		pTweenObject* pTweenObject::To(const float &endValue)
		{
			_EndValue = __EndValue = endValue;
			return this;
		}

		// Duration
		pTweenObject* pTweenObject::Duration(const float &duration)
		{
			_Duration = duration;
			return this;
		}

		// Transition
		pTweenObject* pTweenObject::Transition(const unsigned int &transition)
		{
			_Transition = transition;
			return this;
		}

		// Play
		pTweenObject* pTweenObject::Play()
		{
			_StartPlaying = true;
			_IsPlaying = false;
			pTweenEngine::_pTweenObjects.push_back(this);
			return this;
		}

		// Pause
		pTweenObject* pTweenObject::Pause()
		{
			if (_IsPlaying)
				_Pause = true;
			else if (_HasChain) _ChainTween->Pause();
			return this;
		}

		// Resume
		pTweenObject* pTweenObject::Resume()
		{
			if (_IsPlaying)
				_Pause = false;
			else if (_HasChain) _ChainTween->Resume();
			return this;
		}

		// Delay
		pTweenObject* pTweenObject::Delay(const float &delay)
		{
			_Delay = __Delay = delay;
			return this;
		}

		// Yoyo
		pTweenObject* pTweenObject::Yoyo()
		{
			_YoYo = __YoYo = true;
			return this;
		}

		// Stop
		void pTweenObject::Dispose()
		{
			if (_HasChain)
			{	_ChainTween->_HasParent = false;
				_ChainTween->Dispose();
			}
			if (_HasParent)
			{
				_ChainParent->_HasChain = false;
				_ChainParent->Dispose();
			}
			delete this;
		}

		// Chain
		pTweenObject* pTweenObject::Chain(float* othertarget)
		{
			_ChainTween = new pTweenObject(othertarget, this);
			_HasChain = true;
			return _ChainTween;
		}

		// Chain
		pTweenObject::pTweenObject(float* &otherTarget, pTweenObject* Parent)
		{
			// Parent Data
			_HasParent				= true;
			_ChainParent			= Parent;

			// Target
			_Data					= otherTarget;

			// Default Values
			_StartPlaying 			= false;
			_Pause 					= false;
			_IsPlaying				= false;
			_IsPaused				= false;
			_PauseTime				= 0;
			_PauseStartTime			= 0;
			_Transition				= 0; // Default Transition is Linear
			_InitValue				= *(float*)_Data;
			_Delay					= 0;
			_YoYo					= false;
			_HasChain				= false;
			_ChainTween				= NULL;
			_HasStartCallBack		= false;
			_HasUpdateCallBack		= false;
			_HasEndCallBack			= false;
			_HasStartCallBackOBJ	= false;
			_HasUpdateCallBackOBJ	= false;
			_HasEndCallBackOBJ		= false;
			__Delay					= 0;
			__YoYo					= 0;
			__InitValue				= *(float*)_Data;
		}

		// Destructor
		pTweenObject::~pTweenObject() {}

	};
	
};