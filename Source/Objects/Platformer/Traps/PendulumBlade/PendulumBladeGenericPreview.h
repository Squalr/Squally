#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class PendulumBladeGenericPreview : public HackablePreview
{
public:
	static PendulumBladeGenericPreview* create();

	HackablePreview* clone() override;

protected:
	PendulumBladeGenericPreview();
	virtual ~PendulumBladeGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* previewBlade;
};
