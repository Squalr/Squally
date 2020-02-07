#pragma once

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class ParticleSystem;
	class Sprite;
}

class ClickableNode;
class ClickableTextNode;
class MusicOverlay;
class TitleScreenBackground;
class Track;

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

	TitleScreenBackground* background;

	cocos2d::Sprite* ether;
	cocos2d::ParticleSystem* etherParticles;

	ClickableTextNode* storyModeButton;
	ClickableTextNode* tutorialsButton;
	ClickableTextNode* optionsButton;
	ClickableTextNode* exitButton;
	ClickableTextNode* debugButton;
	cocos2d::Sprite* titleBar;
	cocos2d::Sprite* title;
	MusicOverlay* musicOverlay;
	Track* music;

	static TitleScreen* instance;
};
