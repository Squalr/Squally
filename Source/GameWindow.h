#pragma once

#include <string>
#include <vector>

#include "platform/CCApplication.h"

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
	struct OffsetLabAutomationOptions
	{
		bool enabled = false;
		std::string itemKey;
		bool quitOnComplete = false;
	};

	GameWindow();
	virtual ~GameWindow();

	static void configureOffsetLabAutomationOptionsFromArgs(const std::vector<std::string>& args);
	static bool isOffsetLabAutomationEnabled();
	static const OffsetLabAutomationOptions& getOffsetLabAutomationOptions();

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

	static OffsetLabAutomationOptions offsetLabAutomationOptions;

	GlobalNode* gameWindowTitleContainer = nullptr;
	LocalizedString* gameWindowTitle = nullptr;
	cocos2d::GLViewImpl* glView = nullptr;
};
