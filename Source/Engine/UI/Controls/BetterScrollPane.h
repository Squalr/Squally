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
class CSlider;

class BetterScrollPane : public SmartNode
{
public:
	static BetterScrollPane* create(cocos2d::Size paneSize, cocos2d::Size paddingSize = cocos2d::Size(0.0f, 24.0f), cocos2d::Size marginSize = cocos2d::Size(24.0f, 24.0f), cocos2d::Color4B initBackgroundColor = cocos2d::Color4B(0, 0, 0, 196));

	void setScrollPercentage(float percentage, bool updateScrollBars = true);
	void scrollBy(float delta, bool updateScrollBars = true);
	void scrollTo(float position, bool updateScrollBars = true);
	float getScrollPercentage();
	float getScrollDepth();

	cocos2d::Size getPaneSize();
	void addChild(cocos2d::Node* child) override;
	void removeChild(cocos2d::Node* child, bool cleanup = true) override;
	void removeAllChildren() override;

private:
	typedef SmartNode super;
	BetterScrollPane(cocos2d::Size paneSize, cocos2d::Size paddingSize, cocos2d::Size marginSize, cocos2d::Color4B initBackgroundColor);
	virtual ~BetterScrollPane();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializeListeners() override;
	void initializePositions() override;
	void updateScrollBounds();

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
	CSlider* scrollBar;

	static const float DragSpeed;
	static const float ScrollSpeed;
};
