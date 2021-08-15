#pragma once

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class MusicOverlay;
class TitleScreenBackground;
class Track;
class SmartParticles;

class TitleScreen : public GlobalScene
{
public:
	static TitleScreen* getInstance();

protected:
	TitleScreen();
	virtual ~TitleScreen();
	
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef GlobalScene super;

	TitleScreenBackground* background = nullptr;

	cocos2d::Sprite* ether = nullptr;
	SmartParticles* etherParticles = nullptr;

	ClickableTextNode* storyModeButton = nullptr;
	ClickableTextNode* tutorialsButton = nullptr;
	ClickableTextNode* optionsButton = nullptr;
	ClickableTextNode* exitButton = nullptr;
	ClickableTextNode* debugButton = nullptr;
	cocos2d::Sprite* titleBar = nullptr;
	cocos2d::Sprite* title = nullptr;
	MusicOverlay* musicOverlay = nullptr;
	Track* music = nullptr;

	static TitleScreen* Instance;
};
