pTween

A Really Small and Lightweight Tween Engine

		Examples:
			Simple Tween - x var from 0 to 10 in 5 seconds using Linear Transition
			float x = 0;
			pTween(&x)->To(10)->Duration(5)->Play();

			Elastic Tween - x var from specific (5) position to 200 in 8 seconds using EleasticInOut Transition
			pTween(&x)->From(5)->To(200)->Duration(8)->Transition(pTween::pTweenTransitions::EaseInOutElastic)->Play();

			Tween using YoYo - Plays Inverse Tween after the First
			pTween(&x)->From(5)->To(40)->Duration(3)->Transition(pTween::pTweenTransitions::EaseInOutCirc)->Yoyo()->Play();
			
			Keeping Pointer
			pTweenObject tween = pTween(&x)->To(100)->Duration(10);
			Playing when needed			
			tween->Play();
			... and using it to remove it
			tween->Dispose();

			Chain - Plays an animation after another
			pTween(&x)->From(5)->To(200)->Duration(8)->Play()->Chain(&y)->To(10)->Duration(5);

			Keep in ming that using chain, when keeping a pointer, will store the last tween object created.			
			For safer usage:
			pTweenObject tween = pTween(&x)->From(5)->To(200)->Duration(8)->Play();
			tween->Chain(&y)->To(10)->Duration(5);

			All tweens are automatically deleted after being run, so you'll have to create them again in order to play them again.
