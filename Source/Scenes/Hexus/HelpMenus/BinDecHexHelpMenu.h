#pragma once

#include "Scenes/Hexus/HelpMenus/HelpMenuBase.h"

class BinDecHexHelpMenu : public HelpMenuBase
{
public:
	static BinDecHexHelpMenu* create();

private:
	BinDecHexHelpMenu();
	~BinDecHexHelpMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
};
