//============================================================================
// Name        : pTweenEngine.h
// Author      : Duarte Peixinho
// Version     : 0.1
// Copyright   : ;) 
// Description : pTween Engine
//============================================================================

// Definitions for Exporting
#if defined(_WIN32)

    #if defined(_IMPORT)

        #define PTWEEN_API __declspec(dllimport)

    #elif defined(_EXPORT)
    
        #define PTWEEN_API __declspec(dllexport)

    #else

        #define PTWEEN_API

    #endif

#else

    #define PTWEEN_API

#endif

#ifndef PTWEENENGINE_H
#define	PTWEENENGINE_H

#include <iostream>
#include <list>
#include "pTweenObject.h"

namespace pTween {

	namespace Engine {

		class pTweenObject;

		class PTWEEN_API pTweenEngine {

			friend class pTweenObject;

			public:
				static void Step(const float &Time);
				static void PauseAll();
				static void ResumeAll();
				static void DeleteAll();
			private:
				static std::list<pTweenObject*> _pTweenObjects;
				static float Timer;
		};

	};

};

#endif /* PTWEENENGINE_H */