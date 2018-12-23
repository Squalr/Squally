#pragma once

#include "Engine/GlobalScene.h"

class MenuSprite;
class TextMenuSprite;
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
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	void onStoryModeClick(MenuSprite* menuSprite);
	void onMinigamesClick(MenuSprite* menuSprite);
	void onOptionsClick(MenuSprite* menuSprite);
	void onExitClick(MenuSprite* menuSprite);

	TitleScreenBackground* background;

	cocos2d::Sprite* ether;
	cocos2d::ParticleSystem* etherParticles;

	TextMenuSprite* storyModeButton;
	TextMenuSprite* minigamesButton;
	TextMenuSprite* optionsButton;
	TextMenuSprite* exitButton;
	cocos2d::Sprite* titleBar;
	cocos2d::Sprite* title;

	static TitleScreen* instance;
};
