#pragma once
#include <functional>

#include "Engine/SmartNode.h"
#include "Engine/Events/MouseEvents.h"

namespace cocos2d
{
	class ClippingRectangleNode;
	class Sprite;
}

class ClickableNode;
class CProgressBar;

class CSlider : public SmartNode
{
public:
	static CSlider* create(std::string frameResource, std::string fillResource, std::string slideResource, std::string slideResourceSelected, float progress, bool isHorizontal = true);
	static CSlider* create(cocos2d::Node* frame, cocos2d::Node* fill, std::string slideResource, std::string slideResourceSelected, float progress, bool isHorizontal = true);

	void setProgress(float newProgress);
	void setProgressUpdateCallback(std::function<void(float progress)> callback);

protected:
	CSlider(cocos2d::Node* frame, cocos2d::Node* fill, std::string slideResource, std::string slideResourceSelected, float progress, bool isHorizontal = true);
	virtual ~CSlider();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef SmartNode super;
	void updateSliderPosition();
	void onDrag(ClickableNode* sprite, MouseEvents::MouseEventArgs* args);

	ClickableNode* slide;
	CProgressBar* progressBar;
	ClickableNode* progressBarHitBox;

	bool isHorizontal;
	float progress;

	std::function<void(float progress)> progressUpdateEvent;
};

