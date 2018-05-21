#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "MiniGames/Hexus/HelpMenus/HelpMenuBase.h"
#include "GUI/Components/MenuSprite.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;

class BinaryHelpMenu : public HelpMenuBase
{
public:
	static BinaryHelpMenu * create();

private:
	BinaryHelpMenu();
	~BinaryHelpMenu();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
};
