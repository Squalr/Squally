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
	static CipherScene* create(CipherPuzzleData* cipherPuzzleData);

protected:
	CipherScene(CipherPuzzleData* cipherPuzzleData);
	~CipherScene();

private:
	typedef GlobalScene super;
	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializePositions() override;
	void initializeListeners() override;
	void openPauseMenu();

	Cipher* cipher;
	cocos2d::LayerColor* menuBackDrop;
	PauseMenu* pauseMenu;
	OptionsMenu* optionsMenu;

	CipherPuzzleData* cipherPuzzleData;
};
