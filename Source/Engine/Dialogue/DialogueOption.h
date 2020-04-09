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

	DialogueOption(LocalizedString* dialogueOption, std::function<void()> onDialogueChosen, bool showIfUnique);
	virtual ~DialogueOption();

private:
	typedef SmartNode super;
	
	bool showIfUnique;
};
