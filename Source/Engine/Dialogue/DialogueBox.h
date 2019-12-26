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
		// Left positioning and alignment
		Left,
		
		// Center positioning and alignment
		Center,

		// Right positioning, but left alignment. Cleaner for large amounts of text.
		Right,

		// Right positioning and alignment. Better for one-liner text.
		HardRight,
	};

	bool isDialogueEffectComplete();

protected:

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
	typedef SmartNode super;
	
	cocos2d::Node* containerNode;
	cocos2d::DrawNode* panel;

	bool dialogueEffectComplete;
	float textWidth;
	float speakerOffset;
	float speakerWidth;
	std::function<void()> onDialogueClose;
};
