#pragma once
#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class ClippingRectangleNode;
	class DrawNode;
	class EventMouse;
	class LayerColor;
}

class ClickableNode;
class Slider;

class ScrollPane : public SmartNode
{
public:
	static ScrollPane* create(cocos2d::Size paneSize, std::string sliderResource, std::string sliderResourceSelected, cocos2d::Size paddingSize = cocos2d::Size(0.0f, 24.0f), cocos2d::Size marginSize = cocos2d::Size(24.0f, 24.0f), cocos2d::Color4B initBackgroundColor = cocos2d::Color4B(0, 0, 0, 196));

	void setScrollPercentage(float percentage, bool updateScrollBars = true);
	void scrollBy(float delta, bool updateScrollBars = true);
	void scrollTo(float position, bool updateScrollBars = true);
	float getScrollPercentage();
	float getScrollDepth();
	void updateScrollBounds();

	cocos2d::Size getPaneSize();
	void addChild(cocos2d::Node* child) override;
	void removeChild(cocos2d::Node* child, bool cleanup = true) override;
	void removeAllChildren() override;

private:
	typedef SmartNode super;
	ScrollPane(cocos2d::Size paneSize, std::string sliderResource, std::string sliderResourceSelected, cocos2d::Size paddingSize, cocos2d::Size marginSize, cocos2d::Color4B initBackgroundColor);
	virtual ~ScrollPane();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializeListeners() override;
	void initializePositions() override;

	float initialDragDepth;
	float minScrollDepth;
	float maxScrollDepth;
	cocos2d::Size paddingSize;
	cocos2d::Size marginSize;
	cocos2d::Size paneSize;
	cocos2d::LayerColor* background;
	ClickableNode* dragHitbox;
	cocos2d::ClippingRectangleNode* contentClip;
	cocos2d::Node* content;
	cocos2d::DrawNode* scrollBounds;
	Slider* scrollBar;

	static const float DragSpeed;
	static const float ScrollSpeed;
	static const float ScrollTrackWidth;
	static const float ScrollTrackStopOffset;
	static const float ScrollTotalWidth;
};
