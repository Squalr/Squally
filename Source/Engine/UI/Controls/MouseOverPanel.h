#pragma once
#include "cocos2d.h"

#include "Engine/Events/MouseEvents.h"
#include "Engine/SmartNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"

using namespace cocos2d;

class MouseOverPanel : public SmartNode
{
public:
	static MouseOverPanel * create(Node* visibleContent, Node* mouseOverContent, Node* panelParent, Size size);

private:
	MouseOverPanel(Node* visibleContent, Node* mouseOverContent, Node* panelParent, Size size);
	~MouseOverPanel();

	void initializeListeners();
	void onMouseMove(EventCustom* args);

	LayerColor* panelBackgroundFrame;
	LayerColor* panelBackground;
	Node* content;
	Node* panelContent;
	Node* panelParentHost;

	const int frameWidth = 4;
};
