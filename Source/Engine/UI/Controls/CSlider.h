#pragma once
#include "cocos2d.h"

#include "Resources.h"

#include "MenuSprite.h"

using namespace cocos2d;

class CSlider : public Node
{
public:
	static CSlider * create(float progress);

	void setProgressUpdateCallback(std::function<void(float progress)> callback);
	void initializePositions();

protected:
	CSlider(float progress);
	~CSlider();

private:
	void onDrag(MenuSprite* sprite, EventMouse* args);
	void setProgress(float newProgress);

	MenuSprite* slide;
	Sprite* frame;
	MenuSprite* progressBar;
	ClippingRectangleNode* progressClip;

	float progress;

	std::function<void(float progress)> progressUpdateEvent;
};

