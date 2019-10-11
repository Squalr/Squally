#include "DialogueOption.h"

#include "Engine/Localization/LocalizedString.h"

using namespace cocos2d;

DialogueOption* DialogueOption::create(LocalizedString* dialogueOption, std::function<void()> onDialogueChosen)
{
	DialogueOption* instance = new DialogueOption(dialogueOption, onDialogueChosen);

	instance->autorelease();

	return instance;
}

DialogueOption::DialogueOption(LocalizedString* dialogueOption, std::function<void()> onDialogueChosen)
{
	this->dialogueOption = dialogueOption;
	this->onDialogueChosen = onDialogueChosen;

	this->addChild(this->dialogueOption);
}

DialogueOption::~DialogueOption()
{
}
