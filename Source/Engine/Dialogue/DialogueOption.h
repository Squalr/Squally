#pragma once

#include "Engine/SmartNode.h"

class LocalizedString;

class DialogueOption : public SmartNode
{
public:
	static DialogueOption* create(LocalizedString* dialogueOption, std::function<void()> onDialogueChosen, bool showIfUnique = true);
	
	bool isShownIfUnique();
	LocalizedString* getDialogueOption() const { return dialogueOption; }

	std::function<void()> onDialogueChosen = nullptr;

protected:
	DialogueOption(LocalizedString* dialogueOption, std::function<void()> onDialogueChosen, bool showIfUnique);
	virtual ~DialogueOption();

private:
	typedef SmartNode super;
	
	LocalizedString* dialogueOption = nullptr;
	bool showIfUnique = false;
};
