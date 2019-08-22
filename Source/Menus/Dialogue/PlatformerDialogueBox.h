#pragma once

#include "Engine/Dialogue/DialogueBox.h"

class LocalizedLabel;
class LocalizedString;
 
class PlatformerDialogueBox : public DialogueBox
{
public:
	static PlatformerDialogueBox* create();

protected:
	void runDialogue(LocalizedString* localizedString, DialogueAlignment dialogueAlignment, std::function<void()> onDialogueClose) override;
	void hideDialogue() override;
	void onTypeWriterEffectComplete() override;

private:
	typedef DialogueBox super;
	PlatformerDialogueBox();
	~PlatformerDialogueBox();

	void initializePositions() override;
	void initializeListeners() override;

	LocalizedLabel* spaceToContinueLabel;
	cocos2d::Node* leftSpeakerNode;
	cocos2d::Node* rightSpeakerNode;

	bool isDialogueFocused;
};
