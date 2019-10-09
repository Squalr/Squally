#include "DialogueSet.h"

#include "Engine/Localization/LocalizedString.h"

using namespace cocos2d;

DialogueSet* DialogueSet::create()
{
	DialogueSet* instance = new DialogueSet();

	instance->autorelease();

	return instance;
}

DialogueSet::DialogueSet()
{
	this->stringNode = Node::create();
	this->dialogueOptions = std::vector<std::tuple<DialogueOption, float>>();

	this->addChild(this->stringNode);
}

DialogueSet::~DialogueSet()
{
}

void DialogueSet::initializePositions()
{
	super::initializePositions();
}

void DialogueSet::initializeListeners()
{
	super::initializeListeners();
}

void DialogueSet::addDialogueOption(DialogueOption dialogueOption, float priority)
{
	this->dialogueOptions.push_back({ dialogueOption, priority});

	if (dialogueOption.dialogueOption != nullptr)
	{
		this->stringNode->addChild(dialogueOption.dialogueOption);
	}
}
