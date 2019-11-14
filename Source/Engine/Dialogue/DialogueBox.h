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
	enum class DialogueDock
	{
		Top,
		Bottom
	};

	enum class DialogueAlignment
	{
		Left,
		Center,
		Right,
		HardRight,
	};

	bool isDialogueEffectComplete();

protected:
	typedef SmartNode super;

	DialogueBox(float textWidth, float speakerOffset, float speakerWidth);
	~DialogueBox();

	void initializePositions() override;
	void initializeListeners() override;
	virtual void runDialogue(LocalizedString* localizedString, DialogueDock dialogueDock, DialogueAlignment dialogueAlignment, std::function<void()> onDialogueClose);
	virtual void hideDialogue();
	virtual void onTypeWriterEffectComplete();

	cocos2d::Node* contentNode;
	LocalizedLabel* text;

	static const cocos2d::Color4F PanelColor;
	static const cocos2d::Color4F PanelEdgeColor;
	static const cocos2d::Color4B PanelTextColor;
	static const float PanelBorderSize;
	static const float DialogueHeight;

private:
	cocos2d::Node* containerNode;
	cocos2d::DrawNode* panel;

	bool dialogueEffectComplete;
	float textWidth;
	float speakerOffset;
	float speakerWidth;
	std::function<void()> onDialogueClose;
};
