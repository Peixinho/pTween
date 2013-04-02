//============================================================================
// Name        : pTweenObject.h
// Author      : Duarte Peixinho
// Version     : 0.1
// Copyright   : ;)
// Description : pTween Object
//============================================================================

#ifndef PTWEENOBJ_H
#define	PTWEENOBJ_H

#include <vector>

namespace pTween {

    namespace Engine {

        struct Params
        {
            float* Param;
            float InitValue;
            float EndValue;
            Params();
            Params(float* &param, const float &initValue, const float &endValue) : Param(param), InitValue(initValue), EndValue(endValue) {}
        };

        class pTweenOBJ
        {

            public:

                pTweenOBJ() {}

                pTweenOBJ(const unsigned int &ID, void* OBJ, bool useFrames = false)
                {
                    _ID                             = ID;
                    _target                         = OBJ;
                    _useFrames                      = useFrames;
                    _pauseFrames                    = 0;
                    _pauseTime                      = 0;
                    _delayTime                      = 0;
                    _delayFrames                    = 0;
                    _isPaused                       = false;

                    // true if is doesn't exist
                    _onStartFunctionExecuted	= true;
                    _onUpdateFunction		= false;
                    _onCompleteFunction		= false;
                }
                void* GetTarget()
                {
                    return _target;
                }
                void SetDuration(const float &t)
                {
                    _duration = t;
                    if (_useFrames == false)
                        _endTime = _initTime + _duration;
                    if (_useFrames == true)
                        _endFrame = _initFrame + _duration;
                }
                float GetDuration()
                {
                    return _duration;
                }
                void SetInitTime(const float &t)
                {
                    if (_useFrames==false)
                        _initTime = t;
                    if (_useFrames==true)
                        _initFrame = t;
                }
                float GetInitTime()
                {
                    if (_useFrames==false)
                        return _initTime;
                    if (_useFrames==true)
                        return _initFrame;
                }
                float GetEndTime()
                {
                    if (_useFrames==false)
                        return _endTime + _pauseTime + _delayTime;
                    if (_useFrames==true)
                        return _endFrame + _pauseFrames + _delayFrames;
                }
                void SetTime(const int &t)
                {
                    _frames = t;
                    _globalFrames = t;
                }
                void SetTime(const float &t)
                {
                    _time = t;
                    _globalTime = t;
                }
                float GetTime()
                {
                    if (_useFrames==true)
                    {
                        if (_isPaused==true)
                            return _initPauseFrames;
                        else return (float)(_frames-_pauseFrames-_delayFrames);
                    } else {
                        if (_isPaused==true)
                            return _initPauseTime;
                        else return _time-_pauseTime-_delayTime;
                    }
                }
                void AddParam(float* Param, const float &initValue, const float &endValue)
                {
                    _params.push_back(Params(Param, initValue, endValue));
                }
                void SetTransition(const unsigned int &Transition)
                {
                    _transition = Transition;
                }
                bool IsUsingFrames()
                {
                    return _useFrames;
                }
                void Pause()
                {
                    if (_isPaused==false)
                    {
                        _isPaused = true;
                        if (_useFrames==false)
                        {
                            _initPauseTime = _globalTime;
                        } else {
                            _initPauseFrames = _globalFrames;
                        }
                    }
                }
                void Resume()
                {
                    if (_isPaused==true)
                    {
                        _isPaused = false;
                        if (_useFrames==false)
                        {
                            _pauseTime = _globalTime - _initPauseTime;
                        } else {
                            _pauseFrames = _globalFrames - _initPauseFrames;
                        }
                    }
                }
                unsigned int GetTransition()
                {
                    return _transition;
                }
                std::vector<Params> &GetParams()
                {
                    return _params;
                }

                void SetOnStartFunction(void (*func)(void))
                {
                    _onStartFunctionExecuted = false;
                    _onStartFunction = true;
                    _OnStartFunction = func;
                }
                void SetOnUpdateFunction(void (*func)(void))
                {
                    _onUpdateFunction = true;
                    _OnUpdateFunction = func;
                }
                void SetOnCompleteFunction(void (*func)(void))
                {
                    _onCompleteFunction = true;
                    _OnCompleteFunction = func;
                }
                bool HaveStartFunction()
                {
                    return _onStartFunction;
                }
                bool HaveUpdateFunction()
                {
                    return _onUpdateFunction;
                }
                bool HaveCompleteFunction()
                {
                    return _onCompleteFunction;
                }
                bool StartFunctionExecuted()
                {
                    return _onStartFunctionExecuted;
                }
                void GetOnStartFunction()
                {
                    _OnStartFunction();
                    _onStartFunctionExecuted = true;
                }
                void GetOnUpdateFunction()
                {
                    _OnUpdateFunction();
                }
                void GetOnCompleteFunction()
                {
                    _OnCompleteFunction();
                }
                void SetDelay(const float &t)
                {
                    if (_useFrames==true)
                    {
                        _initFrame += t;
                        _delayFrames = t;
                    } else {
                        _initTime += t;
                        _delayTime = t;
                    }
                }

            private:

                // unique identifier
                unsigned int _ID;

                // external timer
                float               _globalTime;
                unsigned int        _globalFrames;

                // internal timer
                float               _time;
                unsigned int        _frames;

                // Paused
                bool _isPaused;

                // use frames
                bool                _useFrames;
                unsigned int
                                    _initFrame,
                                    _endFrame,
                                    _pauseFrames,
                                    _initPauseFrames,
                                    _delayFrames;

                // pTween Object
                void*               _target;

                // pTween args
                    float           _duration,
                                    _initTime,
                                    _endTime,
                                    _pauseTime,
                                    _initPauseTime,
                                    _delayTime;

                // transition name
                unsigned int _transition;

                // pTween Object Params
                std::vector<Params> _params;

                bool                _onStartFunctionExecuted,
                                    _onStartFunction,
                                    _onUpdateFunction,
                                    _onCompleteFunction;
                void                (*_OnStartFunction)(void);
                void                (*_OnUpdateFunction)(void);
                void                (*_OnCompleteFunction)(void);
        };
    }
}

#endif	/* PTWEENOBJ_H */
