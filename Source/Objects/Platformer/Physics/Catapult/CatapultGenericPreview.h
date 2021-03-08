#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

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

protected:
	CatapultGenericPreview();
	virtual ~CatapultGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationNode* previewCatapult;
};
