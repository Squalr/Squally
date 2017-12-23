#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Components/MenuSprite.h"

using namespace cocos2d;

class ToggleButton : public Node
{
public:
	static ToggleButton * create();

protected:
	ToggleButton();
	~ToggleButton();

private:
	void InitializePositions();
	void InitializeListeners();

	MenuSprite* onSwitch;
	MenuSprite* offSwitch;
};

