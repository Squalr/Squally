#pragma once
#include "Engine/SmartNode.h"

namespace cocos2d
{
	class ClippingNode;
	class DrawNode;
	class Sprite;
}

class ProgressBar : public SmartNode
{
public:
	static ProgressBar* create(std::string frameResource, std::string fillResource, cocos2d::Vec2 fillOffset = cocos2d::Vec2::ZERO, bool isHorizontal = true);
	static ProgressBar* create(cocos2d::Node* frame, cocos2d::Node* fill, cocos2d::Vec2 fillOffset = cocos2d::Vec2::ZERO, bool isHorizontal = true);

	cocos2d::Sprite* getFillSprite();

	float getProgress();
	void setProgress(float newProgress);

protected:
	ProgressBar(cocos2d::Node* frame, cocos2d::Node* fill, cocos2d::Vec2 fillOffset, bool isHorizontal);
	virtual ~ProgressBar();

	void initializePositions() override;

private:
	typedef SmartNode super;
	cocos2d::Node* frame;
	cocos2d::Node* fill;
	cocos2d::DrawNode* clipStencil;
	cocos2d::ClippingNode* progressClip;

	bool isHorizontal;
	float progress;
};

