#pragma once

#include "Engine/SmartNode.h"

class LocalizedString;

class DialogueOption : public SmartNode
{
public:
	static DialogueOption* create(LocalizedString* dialogueOption, std::function<void()> onDialogueChosen);
	
	LocalizedString* dialogueOption;
	std::function<void()> onDialogueChosen;

protected:
	typedef SmartNode super;

	DialogueOption(LocalizedString* dialogueOption, std::function<void()> onDialogueChosen);
	~DialogueOption();

private:
};
