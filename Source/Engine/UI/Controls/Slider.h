#pragma once
#include <functional>

#include "Engine/SmartNode.h"
#include "Engine/Events/MouseEvents.h"

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

	void setProgress(float newProgress);
	void setProgressUpdateCallback(std::function<void(float progress)> callback);

protected:
	Slider(cocos2d::Node* frame, cocos2d::Node* fill, std::string slideResource, std::string slideResourceSelected, float progress, bool isHorizontal = true);
	virtual ~Slider();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef SmartNode super;
	void updateSliderPosition();
	void onDrag(ClickableNode* sprite, MouseEvents::MouseEventArgs* args);

	ClickableNode* slide;
	ProgressBar* progressBar;
	ClickableNode* progressBarHitBox;

	bool isHorizontal;
	float progress;

	std::function<void(float progress)> progressUpdateEvent;
};

