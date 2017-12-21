#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Tutorial/TutorialScreen.h"
#include "Story/StoryMap.h"
#include "Utils/Utils.h"
#include "GUI/Menus/Options/OptionsMenu.h"
#include "GUI/Components/FloatingSprite.h"
#include "GUI/Components/InfiniteParallaxNode.h"
#include "GUI/Components/MenuLabel.h"
#include "GUI/Components/MenuSprite.h"
#include "GUI/Components/Mouse.h"
#include "audio/include/SimpleAudioEngine.h"
#include <algorithm>
#include <string>

using namespace cocos2d;
using namespace CocosDenshion;

class TitleScreen : public Scene
{
public:
	static TitleScreen * create();

protected:
	TitleScreen();
	~TitleScreen();

private:
	void onEnter() override;
	void update(float) override;
	void InitializeListeners();
	void OnMenuClick(MenuSprite* menuSprite);
	void OnMouseMove(EventMouse* event);

	Mouse* mouse;
	FloatingSprite* squally;
	Sprite* background;
	FloatingSprite* backgroundVines;
	FloatingSprite* backgroundTrees;
	FloatingSprite* midgroundTrees;
	Sprite* tree;
	Animation* eyes1Anim;
	Animation* eyes2Anim;
	Sprite* eyes1;
	Sprite* eyes2;
	FloatingSprite* foregroundVines;
	InfiniteParallaxNode* fog;
	InfiniteParallaxNode* foregroundFog;
	FloatingSprite* foregroundGrassBottom;
	FloatingSprite* foregroundGrassTop;
	Sprite* foregroundLight;
	ParticleSystem* matrixParticles;
	ParticleSystem* windParticles;
	ParticleSystem* fireflyParticles;

	Label* hackerModeLabel;

	MenuSprite* matrix;
	MenuSprite* storyModeButton;
	MenuSprite* optionsButton;
	MenuSprite* exitButton;
	Sprite* titleBar;

	std::vector<MenuSprite*>* clickableMenus;

	static int hackerMode;

	const float titleFontSize = 64.0f;
	const float menuFontSize = 48.0f;
	const float menuOffset = 128.0f;
	const float spacing = -96.0f;
};

