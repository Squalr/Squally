#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantFloat;
class LocalizedLabel;

class DartLauncherUpdateTimerPreview : public HackablePreview
{
public:
	static DartLauncherUpdateTimerPreview* create();

	HackablePreview* clone() override;

protected:
	DartLauncherUpdateTimerPreview();
	virtual ~DartLauncherUpdateTimerPreview();

	void onEnter() override;
	void initializePositions() override;
	void update(float dt) override;

private:
	typedef HackablePreview super;

	bool isLaunching = false;
	float launchCountDown = 0.0f;

	cocos2d::Sprite* dartLauncher = nullptr;
	cocos2d::Sprite* dart = nullptr;
	ConstantFloat* eaxTimerStr = nullptr;
	LocalizedLabel* eaxTimer = nullptr;
};
