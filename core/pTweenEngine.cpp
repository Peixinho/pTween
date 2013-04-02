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

        // Initialize Static Vars
        float pTweenEngine::_time				= 0;
        float pTweenEngine::_frames				= 0;
        unsigned int pTweenEngine::_counter                     = 0;
        unsigned int pTweenEngine::_pTobjInUse                  = 0;
        std::map<unsigned int ,pTweenOBJ> pTweenEngine::_pTweenOBJS;

        // Initialization of a new pTween
        pTweenEngine &pTweenEngine::Init(void* OBJ, bool useFrames)
        {
            // Generate ID
            pTweenEngine::_counter++;
            pTweenEngine::_pTobjInUse = pTweenEngine::_counter;

            pTweenOBJ pTobj = pTweenOBJ(_counter, OBJ, useFrames);

            // linear by default
            pTobj.SetTransition(pTweenTransitions::Linear);
            // set init time
            pTobj.SetInitTime(pTweenEngine::_time);

            // add to list
            pTweenEngine::_pTweenOBJS[pTweenEngine::_counter]=pTobj;
            return *this;

        }
        // updates an existing pTween
        pTweenEngine &pTweenEngine::UpdateTween(void* OBJ)
        {
            unsigned int ID = pTweenEngine::Search(OBJ);
            if (ID>0)
            {
                pTweenEngine::_pTobjInUse = ID;

            }
            return *this;
        }
        pTweenEngine &pTweenEngine::Duration(const float &t)
        {
            pTweenEngine::_pTweenOBJS[_pTobjInUse].SetDuration(t);
            return *this;
        }
        pTweenEngine &pTweenEngine::Transition(const unsigned int &transition)
        {
            pTweenEngine::_pTweenOBJS[_pTobjInUse].SetTransition(transition);
            return *this;
        }
        pTweenEngine &pTweenEngine::AddParam(float* param, const float &endValue)
        {
            pTweenEngine::_pTweenOBJS[_pTobjInUse].AddParam(param,*param,endValue);
            return *this;
        }
        pTweenEngine &pTweenEngine::AddParam(float* param, const float &initValue, const float &endValue)
        {
            pTweenEngine::_pTweenOBJS[_pTobjInUse].AddParam(param,initValue,endValue);
            return *this;
        }
        pTweenEngine &pTweenEngine::OnStartFunction(void (*func)(void))
        {
            pTweenEngine::_pTweenOBJS[_pTobjInUse].SetOnStartFunction(func);
            return *this;
        }
        pTweenEngine &pTweenEngine::OnUpdateFunction(void (*func)(void))
        {
            pTweenEngine::_pTweenOBJS[_pTobjInUse].SetOnUpdateFunction(func);
            return *this;
        }
        pTweenEngine &pTweenEngine::OnCompleteFunction(void (*func)(void))
        {
            pTweenEngine::_pTweenOBJS[_pTobjInUse].SetOnCompleteFunction(func);
            return *this;
        }
        pTweenEngine &pTweenEngine::Delay(const float& t)
        {
            pTweenEngine::_pTweenOBJS[_pTobjInUse].SetDelay(t);
            return *this;
        }

        pTweenEngine::~pTweenEngine() {}

        // Engine specific Methods

        void pTweenEngine::Step(const float& Time)
        {
            pTweenEngine::_time = Time;
            pTweenEngine::_frames++;

            if (pTweenEngine::_pTweenOBJS.size()>0) {

                pTweenEngine::UpdateTweens();

            }
        }
        void pTweenEngine::UpdateTweens()
        {

            // list of ended tweens to remove
            std::vector<std::map<unsigned int ,pTweenOBJ>::iterator> _pTweensToRemove;

             // Update Tweens
             for (std::map<unsigned int, pTweenOBJ>::iterator i=pTweenEngine::_pTweenOBJS.begin();i!=pTweenEngine::_pTweenOBJS.end();i++)
             {
                 if ((*i).second.GetTarget()!=NULL) {

                     // Update Tween Time
                     if ((*i).second.IsUsingFrames()==true)
                        (*i).second.SetTime(_frames);
                     else
                        (*i).second.SetTime(_time);

                     if (_time>=(*i).second.GetInitTime())
                     {
                         if (_time<(*i).second.GetEndTime())
                         {

                             // execute on Start Function
                             if ((*i).second.HaveStartFunction()==true && (*i).second.StartFunctionExecuted()==false)
                             {
                                    (*i).second.GetOnStartFunction();
                             }

                            // check all params
                            for (std::vector<Params>::iterator k=(*i).second.GetParams().begin();k!=(*i).second.GetParams().end();k++)
                            {
                                *(*k).Param = pTweenEquations::Equation((*i).second.GetTransition(),(*i).second.GetTime(),(*k).InitValue,(*k).EndValue-(*k).InitValue,(*i).second.GetDuration());
                            }

                            // execute on Update Function
                            if ((*i).second.HaveUpdateFunction()==true)
                            {
                               (*i).second.GetOnUpdateFunction();
                            }

                         } else {
                             // Tween ended

                             // Set Final position
                             for (std::vector<Params>::iterator k=(*i).second.GetParams().begin();k!=(*i).second.GetParams().end();k++)
                             {
                                *(*k).Param = (*k).EndValue;
                             }

                             // onComplete function
                             if ((*i).second.HaveCompleteFunction()==true)
                             {
                                (*i).second.GetOnCompleteFunction();
                             }

                            // Remove pTobj
                             _pTweensToRemove.push_back(i);

                         }
                     } else {
                        // not initialized yet
                     }
                 }
             }

             // remove Tweens
             for (int i=0;i<_pTweensToRemove.size();i++)
             {
                pTweenEngine::_pTweenOBJS.erase((*_pTweensToRemove[i]).first);
             }
             // clear remove list
             _pTweensToRemove.clear();

        }
        void pTweenEngine::PauseTween(void* OBJ)
        {
            unsigned  int o = pTweenEngine::Search(OBJ);
            if (o!=0)
            {
                pTweenEngine::_pTweenOBJS[o].Pause();
            }
        }
        void pTweenEngine::ResumeTween(void* OBJ)
        {
            unsigned  int o = pTweenEngine::Search(OBJ);
            if (o!=0)
            {
                pTweenEngine::_pTweenOBJS[o].Resume();
            }
        }
        void pTweenEngine::PauseAllTweens()
        {
            for (std::map<unsigned int, pTweenOBJ>::iterator i=pTweenEngine::_pTweenOBJS.begin();i!=pTweenEngine::_pTweenOBJS.end();i++)
            {
                (*i).second.Pause();
            }
        }
        void pTweenEngine::ResumeAllTweens()
        {
            for (std::map<unsigned int, pTweenOBJ>::iterator i=pTweenEngine::_pTweenOBJS.begin();i!=pTweenEngine::_pTweenOBJS.end();i++)
            {
                (*i).second.Resume();
            }
        }
        void pTweenEngine::Remove(void* OBJ)
        {
            unsigned  int o = pTweenEngine::Search(OBJ);
            if (o!=0)
            {
                pTweenEngine::_pTweenOBJS.erase(pTweenEngine::_pTweenOBJS.find(o));
            }
        }
        void pTweenEngine::RemoveAll()
        {
            pTweenEngine::_pTweenOBJS.clear();
        }
        unsigned int pTweenEngine::Search(void* OBJ)
        {
            for (std::map<unsigned int, pTweenOBJ>::iterator i=pTweenEngine::_pTweenOBJS.begin();i!=pTweenEngine::_pTweenOBJS.end();i++)
            {
                if ((*i).second.GetTarget()==OBJ)
                    return (*i).first;
            }

            return 0;
        }
    }
}
    
