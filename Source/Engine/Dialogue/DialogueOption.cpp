#include "DialogueOption.h"

#include "Engine/Localization/LocalizedString.h"

using namespace cocos2d;

DialogueOption* DialogueOption::create(LocalizedString* dialogueOption, std::function<void()> onDialogueChosen, bool showIfUnique)
{
	DialogueOption* instance = new DialogueOption(dialogueOption, onDialogueChosen, showIfUnique);

	instance->autorelease();

	return instance;
}

DialogueOption::DialogueOption(LocalizedString* dialogueOption, std::function<void()> onDialogueChosen, bool showIfUnique)
{
	this->dialogueOption = dialogueOption;
	this->onDialogueChosen = onDialogueChosen;
	this->showIfUnique = showIfUnique;

	this->addChild(this->dialogueOption);
}

DialogueOption::~DialogueOption()
{
}

bool DialogueOption::isShownIfUnique()
{
	return this->showIfUnique;
}
