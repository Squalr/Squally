#include "DialogueSet.h"

#include "Engine/Localization/LocalizedString.h"
#include "Engine/Dialogue/DialogueOption.h"

using namespace cocos2d;

DialogueSet* DialogueSet::create(DialogueEvents::DialogueVisualArgs args)
{
	DialogueSet* instance = new DialogueSet(args);

	instance->autorelease();

	return instance;
}

DialogueSet::DialogueSet(DialogueEvents::DialogueVisualArgs args)
{
	this->args = args;
	this->optionsNode = Node::create();

	this->addChild(this->optionsNode);
}

DialogueSet::~DialogueSet()
{
}

void DialogueSet::dockToTop()
{
	this->args.dialogueDock = DialogueBox::DialogueDock::Top;
}

DialogueOption* DialogueSet::addDialogueOption(DialogueOption* dialogueOption, float priority)
{
	if (dialogueOption != nullptr)
	{
		this->dialogueOptions.push_back({ dialogueOption, priority});
		this->optionsNode->addChild(dialogueOption);

		std::sort(this->dialogueOptions.begin(), this->dialogueOptions.end(), 
			[](const std::tuple<DialogueOption*, float>& a, const std::tuple<DialogueOption*, float>& b)
		{ 
			return std::get<1>(a) > std::get<1>(b); 
		});
	}

	// Return given option for convienence
	return dialogueOption;
}

void DialogueSet::removeAllDialogueOptions()
{
	this->optionsNode->removeAllChildren();
	this->dialogueOptions.clear();
}

void DialogueSet::removeDialogueOption(DialogueOption* dialogueOption)
{
	if (dialogueOption != nullptr)
	{
		this->optionsNode->removeChild(dialogueOption);

		this->dialogueOptions.erase(std::remove_if(this->dialogueOptions.begin(), this->dialogueOptions.end(),
			[=](const std::tuple<DialogueOption*, float>& entry)
		{
			return std::get<0>(entry) == dialogueOption; 
		}), this->dialogueOptions.end());
	}
}

std::vector<std::tuple<DialogueOption*, float>> DialogueSet::getDialogueOptions()
{
	return this->dialogueOptions;
}

DialogueEvents::DialogueVisualArgs DialogueSet::getArgs()
{
	return this->args;
}
