#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

class PendulumBladeSetAnglePreview : public HackablePreview
{
public:
	static PendulumBladeSetAnglePreview* create();

	HackablePreview* clone() override;

protected:
	PendulumBladeSetAnglePreview();
	virtual ~PendulumBladeSetAnglePreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* previewBlade = nullptr;
	LocalizedLabel* eax0Degrees = nullptr;
	LocalizedLabel* eax90Degrees = nullptr;
	LocalizedLabel* eax180Degrees = nullptr;
	LocalizedLabel* eax270Degrees = nullptr;
};
