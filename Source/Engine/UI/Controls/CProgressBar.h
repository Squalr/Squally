#pragma once
#include "cocos2d.h"

#include "Engine/SmartNode.h"
#include "MenuSprite.h"
#include "Resources.h"

using namespace cocos2d;

class CProgressBar : public SmartNode
{
public:
	static CProgressBar * create();

	void setProgress(float newProgress);

protected:
	CProgressBar();
	~CProgressBar();

	void initializePositions() override;

private:
	Sprite* frame;
	Sprite* progressBar;
	ClippingRectangleNode* progressClip;

	float progress;
};

