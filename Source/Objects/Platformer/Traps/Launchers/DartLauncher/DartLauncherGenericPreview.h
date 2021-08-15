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

protected:
	DartLauncherGenericPreview();
	virtual ~DartLauncherGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* dartLauncher = nullptr;
	cocos2d::Sprite* dart = nullptr;
};
