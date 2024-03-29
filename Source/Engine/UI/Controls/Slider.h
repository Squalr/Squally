#pragma once
#include <functional>

#include "cocos/base/CCInputEvents.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class ProgressBar;

class Slider : public SmartNode
{
public:
	static Slider* create(std::string frameResource, std::string fillResource, std::string slideResource, std::string slideResourceSelected, float progress, bool isHorizontal = true);
	static Slider* create(cocos2d::Node* frame, cocos2d::Node* fill, std::string slideResource, std::string slideResourceSelected, float progress, bool isHorizontal = true);

	void enableInteraction();
	void disableInteraction();
	void setProgress(float newProgress, bool callUpdateCallback = true);
	void setProgressUpdateCallback(std::function<void(float progress)> callback);

protected:
	Slider(cocos2d::Node* frame, cocos2d::Node* fill, std::string slideResource, std::string slideResourceSelected, float progress, bool isHorizontal = true);
	virtual ~Slider();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef SmartNode super;
	void updateSliderPosition();
	void onDrag(cocos2d::InputEvents::MouseEventArgs* args);

	ClickableNode* slide = nullptr;
	ProgressBar* progressBar = nullptr;
	ClickableNode* progressBarHitBox = nullptr;

	bool isHorizontal = false;
	float progress = 0.0f;

	std::function<void(float progress)> progressUpdateEvent = nullptr;
};

