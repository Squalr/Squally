#pragma once
#include <algorithm>
#include <string>
#include "cocos2d.h"

#include "Engine/GlobalScene.h"
#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/FloatingSprite.h"
#include "Engine/UI/InfiniteParallaxNode.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/NavigationEvents.h"
#include "Menus/Title/HackerMode.h"
#include "Menus/Title/TitleScreenBackground.h"
#include "Menus/Options/OptionsMenu.h"
#include "Resources/MusicResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;
using namespace cocos_experimental;

class TitleScreen : public GlobalScene
{
public:
	static void registerGlobalScene();

protected:
	TitleScreen();
	~TitleScreen();

private:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	void onStoryModeClick(MenuSprite* menuSprite);
	void onArcadeModeClick(MenuSprite* menuSprite);
	void onOptionsClick(MenuSprite* menuSprite);
	void onExitClick(MenuSprite* menuSprite);

	TitleScreenBackground* background;

	Sprite* ether;
	ParticleSystem* etherParticles;

	TextMenuSprite* storyModeButton;
	TextMenuSprite* arcadeModeButton;
	TextMenuSprite* optionsButton;
	TextMenuSprite* exitButton;
	Sprite* titleBar;
	Sprite* title;

	static TitleScreen* instance;

	static const std::string StringKeyStoryMode;
	static const std::string StringKeyMinigames;
	static const std::string StringKeyOptions;
	static const std::string StringKeyExit;

	static const float titleFontSize;
	static const float menuFontSize;
	static const float menuOffset;
	static const float spacing;
};
