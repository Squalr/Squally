#pragma once
#include "cocos/math/CCGeometry.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class EventCustom;
	class LayerColor;
	class Node;
}

class MouseOverPanel : public SmartNode
{
public:
	static MouseOverPanel * create(cocos2d::Node* visibleContent, cocos2d::Node* mouseOverContent,
			cocos2d::Node* panelParent, cocos2d::Size size);

private:
	MouseOverPanel(cocos2d::Node* visibleContent,
			cocos2d::Node* mouseOverContent, cocos2d::Node* panelParent, cocos2d::Size size);
	virtual ~MouseOverPanel();

	void initializeListeners();
	void onMouseMove(cocos2d::EventCustom* args);

	cocos2d::LayerColor* panelBackgroundFrame;
	cocos2d::LayerColor* panelBackground;
	cocos2d::Node* content;
	cocos2d::Node* panelContent;
	cocos2d::Node* panelParentHost;

	const int frameWidth = 4;
};
