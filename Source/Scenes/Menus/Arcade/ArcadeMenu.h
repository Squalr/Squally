#pragma once
#include <algorithm>
#include <string>

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "Engine/Localization/Localization.h"
#include "Engine/Rendering/Components/FadeScene.h"
#include "Engine/Rendering/Components/MenuSprite.h"
#include "Engine/Rendering/Components/Mouse.h"
#include "Engine/Rendering/Components/TextMenuSprite.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Menus/Arcade/ArcadeMenu.h"
#include "Scenes/Menus/MenuBackground.h"
#include "Resources.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocos_experimental;

class ArcadeMenu : public FadeScene
{
public:
	static ArcadeMenu * create();

protected:
	ArcadeMenu();
	~ArcadeMenu();

private:
	void onEnter() override;
	void initializePositions();

	void onHexusClick(MenuSprite* menuSprite);

	ScrollView* scrollView;
	MenuBackground* background;
	TextMenuSprite* hexusButton;
	Node* unknownButton1;
	Node* unknownButton2;
	Node* unknownButton3;
	Node* unknownButton4;
	Node* unknownButton5;
	Node* unknownButton6;

	static const std::string StringKeyHexus;
	static const std::string StringKeyUnknown;

	static const float titleFontSize;
	static const float menuFontSize;
	static const float menuOffset;
	static const float spacing;
};

