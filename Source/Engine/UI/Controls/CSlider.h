#pragma once
#include "cocos2d.h"

#include "Engine/SmartNode.h"
#include "MenuSprite.h"

using namespace cocos2d;

class CSlider : public SmartNode
{
public:
	static CSlider * create(float progress);

	void setProgressUpdateCallback(std::function<void(float progress)> callback);

protected:
	CSlider(float progress);
	~CSlider();

	void initializePositions() override;

private:
	void onDrag(MenuSprite* sprite, MouseEvents::MouseEventArgs* args);
	void setProgress(float newProgress);

	MenuSprite* slide;
	Sprite* frame;
	MenuSprite* progressBar;
	ClippingRectangleNode* progressClip;

	float progress;

	std::function<void(float progress)> progressUpdateEvent;
};

