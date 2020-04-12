#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class DartLauncherGenericPreview : public HackablePreview
{
public:
	static DartLauncherGenericPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	DartLauncherGenericPreview();
	~DartLauncherGenericPreview();
	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* dartLauncher;
	cocos2d::Sprite* dart;
};
