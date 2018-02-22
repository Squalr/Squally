#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Utils/GameUtils.h"

using namespace cocos2d;

class MouseOverPanel : public Node
{
public:
	static MouseOverPanel * create(Node* visibleContent, Node* mouseOverContent, Node* panelParent, Size size);

private:
	MouseOverPanel(Node* visibleContent, Node* mouseOverContent, Node* panelParent, Size size);
	~MouseOverPanel();

	void initializeListeners();
	void onMouseSpriteMove(EventCustom* args);

	LayerColor* panelBackgroundFrame;
	LayerColor* panelBackground;
	Node* content;
	Node* panelContent;
	Node* panelParentHost;

	const int frameWidth = 4;
};
