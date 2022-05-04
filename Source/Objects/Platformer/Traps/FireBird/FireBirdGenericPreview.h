#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class SmartAnimationSequenceNode;

class FireBirdGenericPreview : public HackablePreview
{
public:
	static FireBirdGenericPreview* create();

	HackablePreview* clone() override;

protected:
	FireBirdGenericPreview();
	virtual ~FireBirdGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* previewSpikes = nullptr;
};
