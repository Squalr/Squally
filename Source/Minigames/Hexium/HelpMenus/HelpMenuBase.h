#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class HelpMenuBase : public Node
{
protected:
	HelpMenuBase();
	~HelpMenuBase();

	void onEnter() override;

private:

	void initializePositions();
	void initializeListeners();
};
