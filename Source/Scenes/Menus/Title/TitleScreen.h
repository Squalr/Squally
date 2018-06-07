#pragma once
#include <algorithm>
#include <string>
#include "cocos2d.h"

#include "Engine/Sound/SoundManager.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Menus/Title/HackerMode.h"
#include "Scenes/Menus/Title/TitleScreenBackground.h"
#include "Scenes/Menus/Tutorial/TutorialScreen.h"
#include "Scenes/Menus/Story/StoryMap.h"
#include "Scenes/Menus/Options/OptionsMenu.h"
#include "Engine/Rendering/Components/FadeScene.h"
#include "Engine/Rendering/Components/FloatingSprite.h"
#include "Engine/Rendering/Components/InfiniteParallaxNode.h"
#include "Engine/Rendering/Components/MenuSprite.h"
#include "Engine/Rendering/Components/Mouse.h"
#include "Resources.h"
#include "Utils/GameUtils.h"


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

