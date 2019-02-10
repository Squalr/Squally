#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LaserAnimation;

class LaserGenericPreview : public HackablePreview
{
public:
	static LaserGenericPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	LaserGenericPreview();
	virtual ~LaserGenericPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	LaserAnimation* previewLaser;
};
