#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Config/SoundManager.h"
#include "Events/NavigationEvents.h"
#include "Utils/GameUtils.h"
#include "GUI/Menus/Title/HackerMode.h"
#include "GUI/Menus/Title/TitleScreenBackground.h"
#include "GUI/Menus/Tutorial/TutorialScreen.h"
#include "GUI/Menus/Story/StoryMap.h"
#include "GUI/Menus/Options/OptionsMenu.h"
#include "GUI/Components/FadeScene.h"
#include "GUI/Components/FloatingSprite.h"
#include "GUI/Components/InfiniteParallaxNode.h"
#include "GUI/Components/MenuSprite.h"
#include "GUI/Components/Mouse.h"
#include <algorithm>
#include <string>

using namespace cocos2d;
using namespace cocos_experimental;

class TitleScreen : public FadeScene
{
public:
	static TitleScreen * create();

protected:
	TitleScreen();
	~TitleScreen();

private:
	void onEnter() override;
	void initializePositions();

	void onMatrixClick(MenuSprite* menuSprite);
	void onStoryModeClick(MenuSprite* menuSprite);
	void onOptionsClick(MenuSprite* menuSprite);
	void onExitClick(MenuSprite* menuSprite);

	TitleScreenBackground* background;

	MenuSprite* ether;
	ParticleSystem* etherParticles;

	MenuSprite* storyModeButton;
	MenuSprite* optionsButton;
	MenuSprite* exitButton;
	Sprite* titleBar;
	Sprite* title;

	const float titleFontSize = 64.0f;
	const float menuFontSize = 48.0f;
	const float menuOffset = 128.0f;
	const float spacing = -96.0f;
};

