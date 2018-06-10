#pragma once
#include "cocos2d.h"

#include "Resources.h"

#include "MenuSprite.h"

using namespace cocos2d;

class CProgressBar : public Node
{
public:
	static CProgressBar * create();

	void setProgress(float newProgress);
	void initializePositions();

protected:
	CProgressBar();
	~CProgressBar();

private:
	Sprite* frame;
	Sprite* progressBar;
	ClippingRectangleNode* progressClip;

	float progress;
};

