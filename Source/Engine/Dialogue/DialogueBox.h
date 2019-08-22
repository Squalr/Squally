#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class DrawNode;
}

class LocalizedLabel;
class LocalizedString;
 
class DialogueBox : public SmartNode
{
public:

protected:
	typedef SmartNode super;
	DialogueBox(float textWidth);
	~DialogueBox();

	void initializePositions() override;
	void initializeListeners() override;
	virtual void runDialogue(LocalizedString* localizedString);
	virtual void hideDialogue();

	static const cocos2d::Color4F PanelColor;
	static const cocos2d::Color4F PanelEdgeColor;
	static const cocos2d::Color4B PanelTextColor;
	static const float PanelBorderSize;

private:
	cocos2d::DrawNode* panel;
	LocalizedLabel* text;
};
