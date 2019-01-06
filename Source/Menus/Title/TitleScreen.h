#pragma once

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class ParticleSystem;
	class Sprite;
}

class ClickableNode;
class ClickableTextNode;
class TitleScreenBackground;

class TitleScreen : public GlobalScene
{
public:
	static TitleScreen* getInstance();
	static void registerGlobalScene();

protected:
	TitleScreen();
	~TitleScreen();

private:
	typedef GlobalScene super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	void onStoryModeClick(ClickableNode* menuSprite);
	void onMinigamesClick(ClickableNode* menuSprite);
	void onOptionsClick(ClickableNode* menuSprite);
	void onExitClick(ClickableNode* menuSprite);

	TitleScreenBackground* background;

	cocos2d::Sprite* ether;
	cocos2d::ParticleSystem* etherParticles;

	ClickableTextNode* storyModeButton;
	ClickableTextNode* minigamesButton;
	ClickableTextNode* optionsButton;
	ClickableTextNode* exitButton;
	cocos2d::Sprite* titleBar;
	cocos2d::Sprite* title;

	static TitleScreen* instance;
};
