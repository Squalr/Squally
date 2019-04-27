#pragma once

#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class LayerColor;
}

class ConfirmationMenu;
class OptionsMenu;
class PauseMenu;
class PointerTrace;

class PointerTraceScene : public GlobalScene
{
public:
	static void registerGlobalScene();

protected:
	PointerTraceScene();
	~PointerTraceScene();

private:
	typedef GlobalScene super;
	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onOptionsExit();
	void openPauseMenu();
	void onResumeClick();
	void onOptionsClick();
	void onExitClick();

	PointerTrace* pointerTrace;
	cocos2d::LayerColor* menuBackDrop;
	PauseMenu* pauseMenu;
	OptionsMenu* optionsMenu;

	static PointerTraceScene* instance;
};
