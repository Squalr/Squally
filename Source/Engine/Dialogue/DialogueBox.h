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

	enum class DialogueAlignment
	{
		Left,
		Center,
		Right,
	};

	DialogueBox(float textWidth);
	~DialogueBox();

	void initializePositions() override;
	void initializeListeners() override;
	virtual void runDialogue(LocalizedString* localizedString, DialogueAlignment dialogueAlignment, std::function<void()> onDialogueClose);
	virtual void hideDialogue();
	virtual void onTypeWriterEffectComplete();
	bool isDialogueEffectComplete();

	cocos2d::Node* contentNode;

	static const cocos2d::Color4F PanelColor;
	static const cocos2d::Color4F PanelEdgeColor;
	static const cocos2d::Color4B PanelTextColor;
	static const float PanelBorderSize;
	static const float DialogueHeight;

private:
	cocos2d::DrawNode* panel;
	LocalizedLabel* text;

	bool dialogueEffectComplete;
	float textWidth;
	std::function<void()> onDialogueClose;
};
