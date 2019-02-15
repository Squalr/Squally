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
	static CProgressBar* create(std::string frameResource, std::string fillResource, cocos2d::Vec2 fillOffset = cocos2d::Vec2::ZERO, bool isHorizontal = true);
	static CProgressBar* create(cocos2d::Node* frame, cocos2d::Node* fill, cocos2d::Vec2 fillOffset = cocos2d::Vec2::ZERO, bool isHorizontal = true);

	void setProgress(float newProgress);

protected:
	CProgressBar(cocos2d::Node* frame, cocos2d::Node* fill, cocos2d::Vec2 fillOffset, bool isHorizontal);
	virtual ~CProgressBar();

	void initializePositions() override;

private:
	typedef SmartNode super;
	cocos2d::Node* frame;
	cocos2d::Node* progressBar;
	cocos2d::ClippingRectangleNode* progressClip;

	bool isHorizontal;
	float progress;
};

