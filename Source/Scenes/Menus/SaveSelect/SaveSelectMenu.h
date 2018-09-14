#pragma once
#include <algorithm>
#include <string>

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/FadeScene.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Cutscenes/IntroCutscene/IntroCutscene.h"
#include "Scenes/Menus/MenuBackground.h"
#include "Resources.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocos_experimental;

class SaveSelectMenu : public FadeScene
{
public:
	static SaveSelectMenu * create();

protected:
	SaveSelectMenu();
	~SaveSelectMenu();

private:
	void onEnter() override;
	void initializeListeners();
	void initializePositions();

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onSaveGame1Click(MenuSprite* menuSprite);
	void onSaveGame2Click(MenuSprite* menuSprite);
	void onSaveGame3Click(MenuSprite* menuSprite);

	Node* background;
	TextMenuSprite* saveGame1;
	TextMenuSprite* saveGame2;
	TextMenuSprite* saveGame3;

	static const std::string StringKeyNewGame;
	static const std::string StringKeyContinueGame;

	static const float titleFontSize;
	static const float menuFontSize;
	static const float menuOffset;
	static const float spacing;
};

