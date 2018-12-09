#pragma once
#include "Engine/SmartNode.h"

namespace cocos2d
{
	class ClippingRectangleNode;
	class Sprite;
}

class CProgressBar : public SmartNode
{
public:
	static CProgressBar * create();

	void setProgress(float newProgress);

protected:
	CProgressBar();
	virtual ~CProgressBar();

	void initializePositions() override;

private:
	cocos2d::Sprite* frame;
	cocos2d::Sprite* progressBar;
	cocos2d::ClippingRectangleNode* progressClip;

	float progress;
};

