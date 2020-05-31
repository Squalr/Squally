#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

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

protected:
	LaserGenericPreview();
	virtual ~LaserGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	LaserAnimation* previewLaser;
};
