#pragma once

#include "cocos/platform/CCApplication.h"

namespace cocos2d
{ 
	class GLViewImpl;
}

class GlobalNode;
class LocalizedString;

/**
@brief The cocos2d Application.

Private inheritance here hides part of interface from Director.
*/
class  GameWindow : private cocos2d::Application
{
public:
	GameWindow();
	virtual ~GameWindow();

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

private:
	typedef cocos2d::Application super;
	GlobalNode* gameWindowTitleContainer;
	LocalizedString* gameWindowTitle;
	cocos2d::GLViewImpl* glView;
};
