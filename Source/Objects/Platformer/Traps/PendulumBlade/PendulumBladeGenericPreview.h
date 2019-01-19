#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class PendulumBladeGenericPreview : public HackablePreview
{
public:
	static PendulumBladeGenericPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	PendulumBladeGenericPreview();
	~PendulumBladeGenericPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* previewBlade;
};
