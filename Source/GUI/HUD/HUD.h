#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class HUD : public Node
{
public:
	static HUD * create();

private:
	HUD();
	~HUD();

	void onEnter() override;
	void InitializePositions();

	Sprite* heart;
	Sprite* healthBarFrame;
};

