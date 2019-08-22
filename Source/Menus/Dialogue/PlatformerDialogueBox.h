#pragma once

#include "Engine/Dialogue/DialogueBox.h"

class LocalizedLabel;
class LocalizedString;
 
class PlatformerDialogueBox : public DialogueBox
{
public:
	static PlatformerDialogueBox* create();

protected:
	void runDialogue(LocalizedString* localizedString) override;
	void hideDialogue() override;

private:
	typedef DialogueBox super;
	PlatformerDialogueBox();
	~PlatformerDialogueBox();

	void initializePositions() override;
	void initializeListeners() override;

	LocalizedLabel* spaceToContinueLabel;
};
