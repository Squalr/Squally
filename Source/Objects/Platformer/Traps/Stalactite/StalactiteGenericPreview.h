#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class StalactiteGenericPreview : public HackablePreview
{
public:
	static StalactiteGenericPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	StalactiteGenericPreview();
	virtual ~StalactiteGenericPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* previewStalactite;
};
