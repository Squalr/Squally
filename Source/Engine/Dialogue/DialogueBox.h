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
	virtual void runDialogue(LocalizedString* localizedString, std::function<void()> onDialogueClose);
	virtual void hideDialogue();
	virtual void onTypeWriterEffectComplete();
	bool isDialogueEffectComplete();

	static const cocos2d::Color4F PanelColor;
	static const cocos2d::Color4F PanelEdgeColor;
	static const cocos2d::Color4B PanelTextColor;
	static const float PanelBorderSize;

	cocos2d::Node* contentNode;

private:
	cocos2d::DrawNode* panel;
	LocalizedLabel* text;

	bool dialogueEffectComplete;
	std::function<void()> onDialogueClose;
};
