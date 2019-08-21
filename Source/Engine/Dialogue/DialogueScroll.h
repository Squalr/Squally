#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class DrawNode;
}

class LocalizedLabel;
class LocalizedString;
 
class DialogueScroll : public SmartNode
{
public:
	static DialogueScroll* create();

	void runDialogue(LocalizedString* localizedString);
	void hideDialogue();

private:
	typedef SmartNode super;
	DialogueScroll();
	~DialogueScroll();

	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::DrawNode* panel;
	LocalizedLabel* text;

	static const cocos2d::Color4F PanelColor;
	static const cocos2d::Color4F PanelEdgeColor;
	static const cocos2d::Color4B PanelTextColor;
	static const float PanelBorderSize;
};
