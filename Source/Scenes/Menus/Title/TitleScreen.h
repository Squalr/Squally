#pragma once
#include <algorithm>
#include <string>
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/Rendering/Components/FadeScene.h"
#include "Engine/Rendering/Components/FloatingSprite.h"
#include "Engine/Rendering/Components/InfiniteParallaxNode.h"
#include "Engine/Rendering/Components/MenuSprite.h"
#include "Engine/Rendering/Components/Mouse.h"
#include "Engine/Rendering/Components/TextMenuSprite.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Menus/Title/HackerMode.h"
#include "Scenes/Menus/Title/TitleScreenBackground.h"
#include "Scenes/Menus/Tutorial/TutorialScreen.h"
#include "Scenes/Menus/Options/OptionsMenu.h"
#include "Resources.h"

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
	void onArcadeModeClick(MenuSprite* menuSprite);
	void onOptionsClick(MenuSprite* menuSprite);
	void onExitClick(MenuSprite* menuSprite);

	TitleScreenBackground* background;

	MenuSprite* ether;
	ParticleSystem* etherParticles;

	TextMenuSprite* storyModeButton;
	TextMenuSprite* arcadeModeButton;
	TextMenuSprite* optionsButton;
	TextMenuSprite* exitButton;
	Sprite* titleBar;
	Sprite* title;

	static const std::string StringKeyStoryMode;
	static const std::string StringKeyMinigames;
	static const std::string StringKeyOptions;
	static const std::string StringKeyExit;

	static const float titleFontSize;
	static const float menuFontSize;
	static const float menuOffset;
	static const float spacing;
};

