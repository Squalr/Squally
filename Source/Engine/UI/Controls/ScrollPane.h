#pragma once
#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class EventMouse;
	class LayerColor;
	class Node;

	namespace ui
	{
		class ScrollView;
	}
}

class ScrollPane : public SmartNode
{
public:
	static ScrollPane * create(cocos2d::Size initPaneSize, cocos2d::Color4B initBackgroundColor);

	cocos2d::Size getPaneSize();
	cocos2d::Size getContentSize();
	void fitSizeToContent(cocos2d::Rect padding = cocos2d::Rect::ZERO);
	void addChild(cocos2d::Node* child) override;
	void removeChild(cocos2d::Node* child, bool cleanup = true) override;
	void removeAllChildren() override;

private:
	ScrollPane(cocos2d::Size initPaneSize, cocos2d::Color4B initBackgroundColor);
	virtual ~ScrollPane();

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;
	void onMouseScroll(cocos2d::EventMouse* event);
	void onScrollViewMouseMove(cocos2d::EventMouse* event);

	cocos2d::Size paneSize;
	cocos2d::Color4B backgroundColor;
	cocos2d::LayerColor* background;
	cocos2d::ui::ScrollView* scrollView;
	
	static const cocos2d::Size marginSize;
	static const float scrollSpeed;
};

