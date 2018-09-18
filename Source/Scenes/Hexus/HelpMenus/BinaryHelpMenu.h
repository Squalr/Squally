#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/HelpMenus/HelpMenuBase.h"

using namespace cocos2d;

class BinaryHelpMenu : public HelpMenuBase
{
public:
	static BinaryHelpMenu * create();

private:
	BinaryHelpMenu();
	~BinaryHelpMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
};
