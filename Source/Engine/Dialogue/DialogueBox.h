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
	};

	bool isDialogueEffectComplete();

protected:

	DialogueBox(float textWidth, float speakerOffset, float speakerWidth);
	virtual ~DialogueBox();

	void initializePositions() override;
	void initializeListeners() override;
	virtual void runDialogue(LocalizedString* localizedString, DialogueDock dialogueDock, DialogueAlignment dialogueAlignment, std::function<void()> onDialogueClose);
	virtual void hideDialogue();
	virtual void onTypeWriterEffectComplete();

	cocos2d::Node* contentNode = nullptr;
	LocalizedLabel* text = nullptr;

	static const cocos2d::Color4F PanelColor;
	static const cocos2d::Color4F PanelEdgeColor;
	static const cocos2d::Color4B PanelTextColor;
	static const float PanelBorderSize;
	static const float DialogueHeight;

private:
	typedef SmartNode super;
	
	cocos2d::Node* containerNode = nullptr;
	cocos2d::DrawNode* panel = nullptr;

	bool dialogueEffectComplete = false;
	float textWidth = 0.0f;
	float speakerOffset = 0.0f;
	float speakerWidth = 0.0f;
	std::function<void()> onDialogueClose = nullptr;
};
