#pragma once
#include <functional>

#include "Engine/SmartNode.h"
#include "Engine/Events/MouseEvents.h"

class ClickableNode;

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
	typedef SmartNode super;
	void onDrag(ClickableNode* sprite, MouseEvents::MouseEventArgs* args);
	void setProgress(float newProgress);

	ClickableNode* slide;
	cocos2d::Sprite* frame;
	ClickableNode* progressBar;
	cocos2d::ClippingRectangleNode* progressClip;

	float progress;

	std::function<void(float progress)> progressUpdateEvent;
};

