//============================================================================
// Name        : pTweenObject.h
// Author      : Duarte Peixinho
// Version     : 0.1
// Copyright   : ;) 
// Description : pTween Object
//============================================================================

#ifndef PTWEENOBJECT_H
#define	PTWEENOBJECT_H

#include "pTweenEngine.h"

namespace pTween {

	namespace Engine {

		class pTweenEngine;

		class PTWEEN_API pTweenObject {

			friend class pTweenEngine;

			public:

				// Constructor
				pTweenObject(float* &target);

				// Initial Value
				pTweenObject* From(const float &initValue);

				// Final Value
				pTweenObject* To(const float &endValue);

				// Duration
				pTweenObject* Duration(const float &duration);

				// Transition
				pTweenObject* Transition(const unsigned int &transition);

				// Play
				pTweenObject* Play();

				// Pause
				pTweenObject* Pause();

				// Resume
				pTweenObject* Resume();

				// Delay
				pTweenObject* Delay(const float &delay);

				// Yoyo
				pTweenObject* Yoyo();

				// Delete
				void Dispose();

				// Chain Animation
				pTweenObject* Chain(float* othertarget);

				virtual ~pTweenObject();

			private:
				// Constructor
				pTweenObject(float* &target, pTweenObject* Parent);

				// Parameters
				float* _Data;
				float _InitValue;
				float _EndValue;
				float _Duration;
				unsigned int _Transition;

				bool _StartPlaying;
				bool _Pause;
				bool _IsPlaying;
				bool _IsPaused;

				// Timers
				float _StartTime;
				float _EndTime;
				float _PauseStartTime;
				float _PauseTime;
				float _Delay;

				// Yoyo
				bool _YoYo;

				// Autodelete on Finish
				bool _AutoDelete;

				// Data for Repetition
				float __Delay;
				bool __YoYo;
				float __InitValue;
				float __EndValue;

				// Chain
				bool _HasChain;
				pTweenObject* _ChainTween;
				// Chain Parent
				bool _HasParent;
				pTweenObject* _ChainParent;

		};

	};
	
};

#endif /* PTWEENOBJECT_H */