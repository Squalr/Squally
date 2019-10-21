#pragma once

#include "Engine/SmartNode.h"

class LocalizedString;

class DialogueOption : public SmartNode
{
public:
	static DialogueOption* create(LocalizedString* dialogueOption, std::function<void()> onDialogueChosen, bool showIfUnique = true);
	
	LocalizedString* dialogueOption;
	std::function<void()> onDialogueChosen;
	bool isShownIfUnique();

protected:
	typedef SmartNode super;

	DialogueOption(LocalizedString* dialogueOption, std::function<void()> onDialogueChosen, bool showIfUnique);
	~DialogueOption();

private:
	bool showIfUnique;
};
