#pragma once
#include <functional>

#include "Engine/SmartNode.h"
#include "Engine/Events/MouseEvents.h"

class MenuSprite;

namespace cocos2d
{
	class ClippingRectangleNode;
	class Sprite;
}

class CSlider : public SmartNode
{
public:
	static CSlider * create(float progress);

	void setProgressUpdateCallback(std::function<void(float progress)> callback);

protected:
	CSlider(float progress);
	virtual ~CSlider();

	void initializePositions() override;

private:
	void onDrag(MenuSprite* sprite, MouseEvents::MouseEventArgs* args);
	void setProgress(float newProgress);

	MenuSprite* slide;
	cocos2d::Sprite* frame;
	MenuSprite* progressBar;
	cocos2d::ClippingRectangleNode* progressClip;

	float progress;

	std::function<void(float progress)> progressUpdateEvent;
};

