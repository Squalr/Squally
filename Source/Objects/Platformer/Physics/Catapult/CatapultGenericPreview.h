#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class SmartAnimationNode;

class CatapultGenericPreview : public HackablePreview
{
public:
	static CatapultGenericPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	CatapultGenericPreview();
	virtual ~CatapultGenericPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	SmartAnimationNode* previewCatapult;
};
