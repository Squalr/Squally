#pragma once

#include "Engine/Dialogue/DialogueBox.h"

class LocalizedLabel;
class LocalizedString;
class SmartClippingNode;
 
class PlatformerDialogueBox : public DialogueBox
{
public:
	static PlatformerDialogueBox* create();

protected:
	PlatformerDialogueBox();
	virtual ~PlatformerDialogueBox();

	void initializePositions() override;
	void initializeListeners() override;
	void onTypeWriterEffectComplete() override;

	void runDialogue(LocalizedString* localizedString, DialogueBox::DialogueDock dialogueDock, DialogueBox::DialogueAlignment dialogueAlignment,
		std::function<void()> onDialogueClose, bool allowSpace, bool unhijack, bool allowHackerMode);
	void hideDialogue() override;

private:
	typedef DialogueBox super;

	bool chooseOption(int option);
	bool cancelOptionChoice();

	LocalizedLabel* spaceToContinueLabel = nullptr;
	SmartClippingNode* leftSpeakerClip = nullptr;
	SmartClippingNode* rightSpeakerClip = nullptr;
	cocos2d::DrawNode* leftSpeakerBackground = nullptr;
	cocos2d::DrawNode* rightSpeakerBackground = nullptr;
	cocos2d::Node* leftSpeakerNode = nullptr;
	cocos2d::Node* rightSpeakerNode = nullptr;

	std::vector<std::function<bool()>> inputOptions;
	std::function<bool()> inputCancel = nullptr;
	bool isDialogueFocused = false;
	bool allowSpace = false;
	bool unhijack = true;
	bool allowHackerMode = false;

	static const cocos2d::Color4F SpeakerBackgroundColor;
	static const float TextWidth;
	static const float SpeakerPanelWidth;
	static const float SpeakerPanelOffset;
};
