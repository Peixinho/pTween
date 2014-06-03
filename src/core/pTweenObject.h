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
#include "../signals/Signal.h"

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

				// Set CallBacks
				template< class X, class Y >
				pTweenObject* OnStartCallBack( Y * obj, void (X::*func)() )
				{
					_HasStartCallBackOBJ = true;
					_OnStart.Connect(obj,func);
					return this;
				}
				template< class X, class Y >
				pTweenObject* OnUpdateCallBack( Y * obj, void (X::*func)() )
				{
					_HasUpdateCallBackOBJ = true;
					_OnUpdate.Connect(obj,func);
					return this;
				}
				template< class X, class Y >
				pTweenObject* OnEndCallBack( Y * obj, void (X::*func)() )
				{
					_HasEndCallBackOBJ = true;
					_OnEnd.Connect(obj,func);
					return this;
				}
				pTweenObject* OnStartCallBack(void(func)())
				{
					_HasStartCallBack = true;
					_OnStart.Bind(func);
					return this;
				}
				pTweenObject* OnUpdateCallBack(void(func)())
				{
					_HasUpdateCallBack = true;
					_OnUpdate.Bind(func);
					return this;
				}
				pTweenObject* OnEndCallBack(void(func)())
				{
					_HasEndCallBack = true;
					_OnEnd.Bind(func);
					return this;
				}

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

				// CallBacks
				Gallant::Signal0<void> _OnStartOBJ;
				Gallant::Signal0<void> _OnUpdateOBJ;
				Gallant::Signal0<void> _OnEndOBJ;
				Gallant::Delegate0<void> _OnStart;
				Gallant::Delegate0<void> _OnUpdate;
				Gallant::Delegate0<void> _OnEnd;

				bool _HasStartCallBack;
				bool _HasUpdateCallBack;
				bool _HasEndCallBack;
				bool _HasStartCallBackOBJ;
				bool _HasUpdateCallBackOBJ;
				bool _HasEndCallBackOBJ;

		};

	};
	
};

#endif /* PTWEENOBJECT_H */