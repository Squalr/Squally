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
	static CProgressBar* create(cocos2d::Sprite* frame, cocos2d::Sprite* fill, cocos2d::Vec2 fillOffset = cocos2d::Vec2::ZERO);

	void setProgress(float newProgress);

protected:
	CProgressBar(cocos2d::Sprite* frame, cocos2d::Sprite* fill, cocos2d::Vec2 fillOffset);
	virtual ~CProgressBar();

	void initializePositions() override;

private:
	typedef SmartNode super;
	cocos2d::Sprite* frame;
	cocos2d::Sprite* progressBar;
	cocos2d::ClippingRectangleNode* progressClip;

	float progress;
};

