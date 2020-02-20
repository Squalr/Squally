#pragma once

#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class Sprite;
};

class HackerModeWarningHud : public Hud
{
public:
	static HackerModeWarningHud* create();

protected:
	HackerModeWarningHud();
	virtual ~HackerModeWarningHud();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef Hud super;

	cocos2d::Sprite* radialEye;
};
