#pragma once
#include "cocos2d.h"
#include "Game.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

using namespace cocos2d;

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

/**
@brief The cocos2d Application.

Private inheritance here hides part of interface from Director.
*/
class  Window : private Application
{
public:
	Window();
	virtual ~Window();

	virtual void initGLContextAttrs();

	/**
	@brief Implement Director and Scene init code here.
	@return true Initialize success, app continue.
	@return false Initialize failed, app terminate.
	*/
	virtual bool applicationDidFinishLaunching();

	/**
	@brief Called when the application moves to the background.
	@param The pointer of the application.
	*/
	virtual void applicationDidEnterBackground();

	/**
	@brief Called when the application reenters the foreground.
	@param The pointer of the application.
	*/
	virtual void applicationWillEnterForeground();
};
