#pragma once
#include <functional>
#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class ClippingNode;
	class DrawNode;
	class EventMouse;
	class LayerColor;
}

class ClickableNode;
class Slider;

class ScrollPane : public SmartNode
{
public:
	static ScrollPane* create(cocos2d::CSize paneSize, std::string sliderResource, std::string sliderResourceSelected, cocos2d::CSize paddingSize = cocos2d::CSize(0.0f, 24.0f), cocos2d::CSize marginSize = cocos2d::CSize(24.0f, 24.0f), cocos2d::Color4B initBackgroundColor = cocos2d::Color4B(0, 0, 0, 196));

	void enableInteraction();
	void disableInteraction();
	void setBackgroundColor(cocos2d::Color4B backgroundColor);
	void renderCustomBackground(std::function<void(cocos2d::DrawNode* customBackground, cocos2d::CSize paneSize, cocos2d::CSize paddingSize, cocos2d::CSize marginSize)> drawFunc);
	void setScrollPercentage(float percentage, bool updateScrollBars = true, float duration = 0.0f);
	void scrollBy(float delta, bool updateScrollBars = true, float duration = 0.0f);
	void scrollToCenter(cocos2d::Node* target, bool updateScrollBars = true, float duration = 0.0f);
	void scrollTo(float position, bool updateScrollBars = true, float duration = 0.0f);
	float getScrollPercentage();
	float getScrollDepth();
	void updateScrollBounds();
	void suspendUpdate();
	void resumeUpdate();

	cocos2d::CSize getPaneSize();
	void addChild(cocos2d::Node* child) override;
	void removeChild(cocos2d::Node* child, bool cleanup = true) override;
	void removeAllChildren() override;

protected:
	ScrollPane(cocos2d::CSize paneSize, std::string sliderResource, std::string sliderResourceSelected, cocos2d::CSize paddingSize, cocos2d::CSize marginSize, cocos2d::Color4B initBackgroundColor);
	virtual ~ScrollPane();

private:
	typedef SmartNode super;

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializeListeners() override;
	void initializePositions() override;
	float getLowestChild(cocos2d::Vector<cocos2d::Node*>& children, float lowestItem = 0.0f);

	bool updateSuspended = false;
	float initialDragDepth = 0.0f;
	float minScrollDepth = 0.0f;
	float maxScrollDepth = 0.0f;
	cocos2d::CSize paddingSize;
	cocos2d::CSize marginSize;
	cocos2d::CSize paneSize;
	cocos2d::DrawNode* customBackground = nullptr;
	cocos2d::LayerColor* background = nullptr;
	ClickableNode* dragHitbox = nullptr;
	cocos2d::DrawNode* clipStencil = nullptr;
	cocos2d::ClippingNode* contentClip = nullptr;
	cocos2d::Node* content = nullptr;
	cocos2d::DrawNode* scrollBounds = nullptr;
	Slider* scrollBar = nullptr;

	static const float DragSpeed;
	static const float ScrollSpeed;
	static const float ScrollTrackWidth;
	static const float ScrollTrackStopOffset;
	static const float ScrollTotalWidth;
};
