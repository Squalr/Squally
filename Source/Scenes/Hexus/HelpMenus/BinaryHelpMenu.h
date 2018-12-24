#pragma once

#include "Scenes/Hexus/HelpMenus/HelpMenuBase.h"

class BinaryHelpMenu : public HelpMenuBase
{
public:
	static BinaryHelpMenu* create();

private:
	BinaryHelpMenu();
	~BinaryHelpMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
};
