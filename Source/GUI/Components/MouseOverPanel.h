#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Utils/Utils.h"

using namespace cocos2d;

class MouseOverPanel : public Node
{
public:
	static MouseOverPanel * create(Node* visibleContent, Node* mouseOverContent, Vec2 size);

private:
	MouseOverPanel(Node* visibleContent, Node* mouseOverContent, Vec2 size);
	~MouseOverPanel();

	void initializeListeners();
	void onMouseSpriteMove(EventCustom* args);

	Sprite* panelBackground;
	Node* content;
	Node* panelContent;
};
