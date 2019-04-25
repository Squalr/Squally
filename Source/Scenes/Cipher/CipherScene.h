#pragma once

#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class LayerColor;
}

class Cipher;
class CipherPuzzleData;
class ConfirmationMenu;
class OptionsMenu;
class PauseMenu;

class CipherScene : public GlobalScene
{
public:
	static void registerGlobalScene();

protected:
	CipherScene();
	~CipherScene();

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

	Cipher* cipher;
	cocos2d::LayerColor* menuBackDrop;
	PauseMenu* pauseMenu;
	OptionsMenu* optionsMenu;

	CipherPuzzleData* cipherPuzzleDataRef;

	static CipherScene* instance;
};
